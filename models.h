#include <vector>
#include <iostream>


using namespace std;

vector<double> logisticModel(const vector<double>& t, const vector<double>& params);
vector<double> linearModel(const vector<double>& t, const vector<double>& params);

double uniformPrior(double u, double lower_bound, double upper_bound);
