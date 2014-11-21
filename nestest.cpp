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

    in.read_header(io::ignore_no_column, "t", "y");

    double t_in, y_in;

    while(in.read_row(t_in, y_in)) {
        t.push_back(t_in);
        y.push_back(y_in);
    }

    length = t.size();

}

void DataSet::dumpData()
{
    cout << "t" << "\t" << "y" << endl;

    for(int i=0; i<length; i++) {
        cout << t[i] << "\t" << y[i] << endl;
    }
}

double randUniformDouble(double lowerBound, double upperBound) {
    /* Generate a double uniformly distributed in the range (lowerBound, upperBound) */

    default_random_engine generator;
    uniform_real_distribution<double> distribution(lowerBound, upperBound);

    return distribution(generator);
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
    double rU = randUniformDouble(0.5, 3.5);

    cout << "rU: " << rU << endl;
}

double llFunc(
    vector<double> (modelFunc)(const vector<double>& t, const vector<double>& params), 
    DataSet mydata,
    const vector<double>& params)
{

    vector<double> results = modelFunc(mydata.t, params);

    double sigma = 0.1;

    int n = mydata.t.size();

    float rsum = 0;
    for (int i=0; i<n; i++) {
        rsum += pow((results[i] - mydata.y[i]) / sigma, 2);
    }

    float llhood = log(1 / M_PI);
    //copy(results.begin(), results.end(), ostream_iterator<double>(cout, "\n"));

    return llhood;
}

void testParams()
{
    Parameter p1("param1", 1.5, 6.5);
    p1.current_value = 3;

    cout << p1.upper_bound << endl;
}

void explorer(
    pvector params, 
    vector<double> (modelFunc)(const vector<double>& t, const vector<double>& params), 
    double llMax)
{
  double stepsize;
    cout << "Dora!" << endl;

    cout << params[0] << endl;
}

void testll()
{
    DataSet mydata("data/B092_1.csv");

    vector<double> params(3);
    params = {1, 100, 1};


    double ll = llFunc(logisticModel, mydata, params);

    cout << "Ll: " << ll << endl;

    explorer(params, logisticModel, ll);

}
int main(int argc, char *argv[])
{
    //testParams();
    //testRand();
    testll();
    return 0;
}
