#include <vector>
#include <string>

#include "dataset.h"
#include "models.h"
#include "randprov.h"

#define PI 3.1415927

using namespace std;

typedef vector<double> pvector;

class Parameter {
public:
    Parameter(string name, double lower_bound, double upper_bound);
    string name;
    double current_value;
    double lower_bound;
    double upper_bound;
};

class Pinfer {
public:
    Pinfer(double initial_val, double start_step);
    Pinfer();
    void makeStep();
    double value;
    double step_size;
    double lower_bound;
    double upper_bound;
    double transform();
};

class PGroup
{
  vector<double> pvals;
  double ll;
};

class ParamSet
{
public:
    ParamSet(int n_params, string filename);
    vector<Pinfer> pinfers;
    vector<PGroup> pgroups;
    DataSet *data;
    double LogLikelihood();
    double LogLikelihood(vector<double> &uparams);
    double sigma = 0.5;
    void Explore(vector<double> &uparams, double llMin);
    RandProvider *randprov;
  //  function<void (
};


