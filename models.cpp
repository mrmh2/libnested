/*****************
* models.cpp
**************/

#include <math.h>

#include "models.h"

vector<double> logisticModel(const vector<double>& t, const vector<double>& params) {

    // cout << "Running logisticModel" << endl;
    // cout << "P: " << params[0] << endl;

    int n = t.size();

    vector<double> model_out(n);

    double par1 = params[0];
    double par2 = params[1];
    double par3 = params[2];

    for (int i=0; i<n; i++) {
        model_out[i] = par1 + (par3 * t[i] - log(1 + (exp(par3 * t[i]) - 1)/exp(par2 - par1)));
    }

    return model_out;
}

vector<double> linearModel(const vector<double>& t, const vector<double>& params)
{
    int n = t.size();

    vector<double> model_out(n);

    double m = params[0];
    double c = params[1];

    //cout << "M = " << m << ", C = " << c << endl;

    for (int i=0; i<n; i++) {
        model_out[i] = m * t[i] + c;
    }

    return model_out;
}

vector<double> Bar4Par(const vector<double>& t, const vector<double>& params) {
    double par1 = params[0];
    double par2 = params[1];
    double par3 = params[2];
    double par4 = params[3];

    int n = t.size();

    vector<double> model_out(n);

    double a1 = 1;
    double a2 = 1;
    double a3 = 1;

    double A;
    for (int i=0; i<n; i++) {
        A = a2 * (t[i] - par4/par3 +
            log(1 - a2 * (exp(-par3 * t[i]) + a3 * exp(-(par3 * t[i] - par4))))/par3);

    }

    return model_out;
}

double uniformPrior(double u, double lower_bound, double upper_bound)
{
  return lower_bound + u * (upper_bound - lower_bound);
}
