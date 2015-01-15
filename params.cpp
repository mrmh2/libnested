#include "params.h"

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

double Pinfer::transform(double val)
{
    return uniformPrior(val, lower_bound, upper_bound);
}


ParamSet::ParamSet(int in_n_params, string filename, int prior_size)
{
  n_params = in_n_params;
    //pinfers.push_back(new Pinfer(0.5, 0.1));
    //pinfers = new vector<Pinfer>;
    pinfers.reserve(n_params);
    pgroups.reserve(prior_size);

    for (int i=0; i<n_params; i++) {
      pinfers.push_back(Pinfer(0.5, 0.1));
      pinfers[i].value = 0.5;
      pinfers[i].step_size = 0.1;
      pinfers[i].lower_bound = 0;
      pinfers[i].upper_bound = 2;
    }

    data = new DataSet(filename);

    randprov = new RandProvider(0, 1);

    for (int i=0; i<prior_size; i++) {
      pgroups.push_back(PGroup(n_params, randprov));
      for (int j=0; j<n_params; j++) {
	       pgroups[i].pinfers.push_back(&pinfers[j]);
      }
      pgroups[i].ll = LogLikelihood(&pgroups[i]);
    }
}

double ParamSet::LogLikelihood(PGroup *pg)
{
//    cout << "PLLH" << endl;

    int n = data->t.size();

    vector<double> params(2);

    for (int i=0; i<2; i++) {
      params[i] = pg->pinfers[i]->transform(pg->pvals[i]);
    }

    vector<double> results = linearModel(data->t, params);

    double sum_sq_diff = 0;
    for (int i=0; i<n; i++) {
//        cout << results[i] << endl;
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

double makeBoundedStep(vector<double> &iParams, vector<double> &steps)
{
  
}

void ParamSet::Explore(PGroup *pg)
{
  double randstep;
  cout << "Explore from " << pg->ll << endl;

  // for (int i=0; i<iParams.size(); i++) {
  //    randstep = 0.1 * randprov->randUniformDouble();
  //    iParams[i] += randstep;
  // }

  // cout << LogLikelihood(iParams) << endl;
}

void ParamSet::dump()
{
  cout << pinfers.size() << " pinfers." << endl;
  cout << pgroups.size() << " objects." << endl;

  for(int i=0; i<pgroups.size(); i++) {
    pgroups[i].dump();
  }
}

PGroup::PGroup(int in_n_params, RandProvider *randprov)
{
  n_params = in_n_params;

  pvals.reserve(n_params);
  for (int i=0; i<n_params; i++) {
    pvals.push_back(randprov->randUniformDouble());
  }
  pinfers.reserve(n_params);
}

PGroup* ParamSet::find_worst()
{
  double ll_worst = pgroups[0].ll;
  int i_worst = 0;

  for (int i=0; i<pgroups.size(); i++) {
    if (pgroups[i].ll < ll_worst) {
      ll_worst = pgroups[i].ll;
      i_worst = i;
    }
  }

  cout << "Worst ll: " << ll_worst << " i_worst: " << i_worst << endl;

  return &pgroups[i_worst];

}

void PGroup::dump()
{
  cout << "In PGroup, " << n_params << " params." << endl;

  for (int i=0; i<n_params; i++) {
    cout << "  " << pvals[i];
    cout << " (" << pinfers[i]->transform(pvals[i]) << ")";
  }

  cout << endl;
  cout << "  ll: " << ll << endl;
}
