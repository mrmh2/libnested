
Pinfer::Pinfer(double initial_val, double start_step)
{
    value = initial_val;
    step_size  = start_step;
}

Pinfer::Pinfer()
{
    value = 0.5;
    step_size = 0.1;
    lower_bound = 0;
    upper_bound = 2;
}

double Pinfer::transform()
{
    return uniformPrior(value, lower_bound, upper_bound);
}


ParamSet::ParamSet(int n_params, string filename)
{
    //pinfers.push_back(new Pinfer(0.5, 0.1));
    //pinfers = new vector<Pinfer>;
    pinfers.reserve(n_params);

    for (int i=0; i<n_params; i++) {
        pinfers[i].value = 0.5;
        pinfers[i].step_size = 0.1;
        pinfers[i].lower_bound = 0;
        pinfers[i].upper_bound = 2;
    }

    data = new DataSet(filename);

}

double ParamSet::LogLikelihood()
{
    cout << "PLLH" << endl;

    int n = data->t.size();

    vector<double> params(2);

    for (int i=0; i<2; i++) {
        params[i] = pinfers[i].transform();
    }

    vector<double> results = linearModel(data->t, params);

    double sum_sq_diff = 0;
    for (int i=0; i<n; i++) {
        cout << results[i] << endl;
	sum_sq_diff += (results[i] - data->y[i]) * (results[i] - data->y[i]);
    }


    double H = (double) n * log(sigma * sqrt(2 * PI)) - sum_sq_diff / (2 * pow(sigma, 2));

    return H;

}

double ParamSet::LogLikelihood(vector<double> &uparams)
{
    int n = data->t.size();

    vector<double> params(2);

    for (int i=0; i<2; i++) {
      params[i] = uparams[i] * 2;
    }

    vector<double> results = linearModel(data->t, params);

    double sum_sq_diff = 0;
    for (int i=0; i<n; i++) {
      //cout << results[i] << endl;
	sum_sq_diff += (results[i] - data->y[i]) * (results[i] - data->y[i]);
    }

    //cout << "ssd: " << sum_sq_diff << endl;
    double nssd = sum_sq_diff / (2 * pow(sigma, 2));
    double ncomp = -1 * (double) n * log(sigma * sqrt(2 * PI));
    // cout << "nssd: " << nssd << endl;
    // cout << "ncomp: " << ncomp << endl;

    //double H = (double) -n * log(sigma * sqrt(2 * PI)) - sum_sq_diff / (2 * pow(sigma, 2));
    double H = ncomp - nssd;

    return H;
  
}
