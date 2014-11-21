#include <iostream>
#include <string>
#include <vector>

#include "csv.h"

using namespace std;

class DataSet {
    public:
        DataSet(string filename);
        void dumpData();
        vector<double> t, y;
        int length;

};