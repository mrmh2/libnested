#include <iostream>
#include <random>

#ifndef RANDPROV_H
#define RANDPROV_H

using namespace std;

class RandProvider
{
public:
  RandProvider(double lowerBound, double upperBound);
  double randUniformDouble();
    default_random_engine generator;    
    uniform_real_distribution<double> *distribution;//(lowerBound, upperBound);
};

#endif
