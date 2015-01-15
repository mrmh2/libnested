/*********************************
* nestest - testing for libnested
**********************************/

#include <iostream>
#include <iterator>
#include <random>
#include <functional>

#include <math.h>

#include "libnested.h"
#include "models.h"
#include "dataset.h"
#include "params.h"
#include "randprov.h"

using namespace std;


RandProvider *masterRand;


void Pinfer::makeStep()
{
    /* Make a step in parameter space. If we go outside the unit hypercube,
    instead replace parameter by value between 0 and 1 */

  double rU = masterRand->randUniformDouble();

    //cout << rU << endl;

    double attempt = value + rU * step_size;

    if (attempt < 0 || attempt > 1) {
        // FIXME - proper random
        value = 0.5 * (1 + masterRand->randUniformDouble());
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
    double rU = masterRand->randUniformDouble();

    cout << "rU: " << rU << endl;
}


double llFunc(
    vector<double> (modelFunc)(const vector<double>& t, const vector<double>& params), 
    DataSet mydata,
    const vector<double>& params)
{
  vector<double> mParams(params.size());

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
//    ParamSet pset,
    vector<double> (modelFunc)(const vector<double>& t, const vector<double>& params), 
    double minLL,
    DataSet data)
{

  //Pinfer pi = Pinfer(0.5, 0.1);

  //cout << pi.value << endl;

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
  // DataSet mydata("data/B092_1.csv");
  DataSet ftdata("data/ftdata.csv");

  //ParamSet ps(3);

      vector<double> params(2);
    params = {0.5, 0.5};

    double ll = llFunc(logisticModel, ftdata, params);

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

void testpset()
{

  ParamSet ps(2, "data/ftdata.csv", 10);

  ps.dump();

  PGroup *pgw = ps.find_worst();

  ps.Explore(pgw);

  //cout << pg->ll << endl;

  //pg->pvals[0] = 0.55555;

  //vector<double> testparams = {0.5, 0.5};
  //double ll = ps.LogLikelihood(testparams);
  //ps.Explore(testparams, ll);

  

}

int main(int argc, char *argv[])
{
    //testParams();
    //testRand();

  masterRand = new RandProvider(-1, 1);
    testpset();
 
    return 0;
}
