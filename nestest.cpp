/*********************************
* nestest - testing for libnested
**********************************/

#include <iostream>

#include "libnested.h"
#include "models.h"

#include "csv.h"

using namespace std;

class DataSet {
    public:
        DataSet(string filename);
        void dumpData();
        vector<double> t, y;
        int length;

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

int main(int argc, char *argv[])
{


    DataSet mydata("data/B092_1.csv");

    mydata.dumpData();

    vector<double> data(5);
    data = {0.1, 0.2, 0.3, 0.4, 0.5, 0.5};

    vector<double> params(3);
    params = {1, 100, 1};

    logisticModel(data, params);

    return 0;
}