/*********************************
* nestest - testing for libnested
**********************************/

#include <iostream>

#include "libnested.h"
#include "models.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Hello nested world" << endl;

    vector<double> data(5);

    data = {0.1, 0.2, 0.3, 0.4, 0.5, 0.5};

    logisticModel(data);

    return 0;
}