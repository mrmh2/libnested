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
    double transform(double val);
};

class PGroup
{
 public:
  /* TODO - should probably take a prior generator as argument */
  PGroup(int in_n_params, RandProvider *randprov);
  int n_params;
  vector<double> pvals;
  vector<Pinfer *> pinfers;
  double ll;
  void dump();
};

class ParamSet
{
public:
    ParamSet(int in_n_params, string filename, int prior_size);
  
    vector<Pinfer> pinfers;
    vector<PGroup> pgroups;
    vector<PGroup> posterior;

    PGroup* find_worst();
    int n_params;
    DataSet *data;
    double LogLikelihood(PGroup *pg);
    double LogLikelihood(vector<double> &uparams);
    double sigma = 0.5;
    void Explore(vector<double> &uparams, double llMin);
    RandProvider *randprov;
    void dump();
  //  function<void (
};


