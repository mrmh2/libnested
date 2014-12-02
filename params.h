#define PI 3.1415927

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

class ParamSet
{
public:
    ParamSet(int n_params, string filename);
    vector<Pinfer> pinfers;
    DataSet *data;
     double LogLikelihood();
  double LogLikelihood(vector<double> &uparams);
  double sigma = 0.5;
  //  function<void (
};
