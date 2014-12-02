#include <iostream>
#include <string>
#include <vector>

#include "csv.h"

#ifndef DATASET_H
#define DATASET_H

using namespace std;

class DataSet {
    public:
        DataSet(string filename);
        void dumpData();
        vector<double> t, y;
        int length;

};

#endif
