/*********************************
* nestest - testing for libnested
**********************************/

#include <iostream>
#include <iterator>
#include <random>

#include "libnested.h"
#include "models.h"

#include "csv.h"

using namespace std;

class RandProvider
{
public:
    RandProvider();
    double randUniformDouble(double lowerBound, double upperBound);
    default_random_engine generator;    
    uniform_real_distribution<double> *distribution;//(lowerBound, upperBound);
};

// default_random_engine generator;

// void initRandom(double lowerBound, double upperBound)
// {
//     uniform_real_distribution<double> distribution(lowerBound, upperBound);

// }

RandProvider::RandProvider() {
    cout << "Hmmit" << endl;
    distribution = new uniform_real_distribution<double>(-1, 1);
//    distribution =
}

double RandProvider::randUniformDouble(double lowerBound, double upperBound) {
    /* Generate a double uniformly distributed in the range (lowerBound, upperBound) */
    return (*distribution)(generator);
}

RandProvider *masterRand;

typedef vector<double> pvector;

class DataSet {
    public:
        DataSet(string filename);
        void dumpData();
        vector<double> t, y;
        int length;

};

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
};

Pinfer::Pinfer(double initial_val, double start_step)
{
    value = initial_val;
    step_size  = start_step;
}

Pinfer::Pinfer()
{
    value = 0.5;
    step_size = 0.1;
}

class ParamSet
{
public:
  vector<Pinfer> pinfers;
};

void Pinfer::makeStep()
{
    /* Make a step in parameter space. If we go outside the unit hypercube,
    instead replace parameter by value between 0 and 1 */

    double rU = masterRand->randUniformDouble(-1, 1);

    //cout << rU << endl;

    double attempt = value + rU * step_size;

    if (attempt < 0 || attempt > 1) {
        // FIXME - proper random
        value = 0.5 * (1 + masterRand->randUniformDouble(0, 1));
    } else {
        value = attempt;
    }
}

Parameter::Parameter(string in_name, double in_lower_bound, double in_upper_bound) 
{
    /* FIXME - better way to do this */

    name = in_name;
    lower_bound = in_lower_bound;
    upper_bound = in_upper_bound;
}

class Explorer {

};

DataSet::DataSet(string filename)
{
    io::CSVReader<2> in(filename);

    try {
    in.read_header(io::ignore_no_column, "t", "y");

    double t_in, y_in;

    while(in.read_row(t_in, y_in)) {
        t.push_back(t_in);
        y.push_back(y_in);
    }

    length = t.size();
    } catch(exception const& e) {
      cout << "Error loading data: " << e.what() << endl;
    }

}

void DataSet::dumpData()
{
    cout << "t" << "\t" << "y" << endl;

    for(int i=0; i<length; i++) {
        cout << t[i] << "\t" << y[i] << endl;
    }
}


//double transformParams

void testStuff()
{
    DataSet mydata("data/B092_1.csv");

    //mydata.dumpData();

    vector<double> data(5);
    data = {0.1, 0.2, 0.3, 0.4, 0.5, 0.5};

    vector<double> params(3);
    params = {1, 100, 1};

    vector<double> results = logisticModel(mydata.t, params);

    copy(results.begin(), results.end(), ostream_iterator<double>(cout, "\n"));

}

void testRand()
{
    double rU = masterRand->randUniformDouble(0.5, 3.5);

    cout << "rU: " << rU << endl;
}

double llFunc(
    vector<double> (modelFunc)(const vector<double>& t, const vector<double>& params), 
    DataSet mydata,
    const vector<double>& params)
{

    vector<double> results = modelFunc(mydata.t, params);

    double sigma = 1;

    int n = mydata.t.size();

    float rsum = 0;
    for (int i=0; i<n; i++) {
        rsum += pow((results[i] - mydata.y[i]) / sigma, 2);
    }

    float llhood = log(rsum / M_PI);

    return llhood;
}

void testParams()
{
    Parameter p1("param1", 1.5, 6.5);
    p1.current_value = 3;

    cout << p1.upper_bound << endl;
}

void explorer(
    ParamSet pset,
    vector<double> (modelFunc)(const vector<double>& t, const vector<double>& params), 
    double minLL,
    DataSet data)
{

    Pinfer pi = Pinfer(0.5, 0.1);

    cout << pi.value << endl;

    int accepted, rejected;

    accepted = 0;
    rejected = 0;

 //    for (int i=0; i<20; i++) {
 //        pi.makeStep();
 // //       cout << pi.value << endl;
 // 	//        params[0] = pi.value;

 // 	        double newLL = llFunc(modelFunc, data, params);

 // 	        int accept = newLL > minLL;

 //        if (accept) {
 //            accepted++;
 //        } else {
 //            rejected++;
 //        }

 // 	        cout << "oldLL: " << minLL << " newLL: " << newLL << " " << accept << endl;
 //    }

    //cout << "Candidate: " << candidate << endl;

}

void testll()
{
    DataSet mydata("data/B092_1.csv");

    vector<double> params(3);
    params = {0.5, 0.5, 0.5};


    double ll = llFunc(logisticModel, mydata, params);

    cout << "Ll: " << ll << endl;

    vector<Pinfer> pis(3);
    //    explorer(params, logisticModel, ll, mydata);

}

void testexplorer()
{
   DataSet ftdata("data/ftdata.csv");

    vector<double> params(2);
    params = {0.1, 0.1};

    double ll = llFunc(linearModel, ftdata, params);

    cout << ll << endl;

    //explorer(params, linearModel, ll, ftdata);

}

int main(int argc, char *argv[])
{
    //testParams();
    //testRand();

    masterRand = new RandProvider();
    //testll();

    testexplorer();
 
    return 0;
}
