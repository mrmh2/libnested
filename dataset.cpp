#include "dataset.h"

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