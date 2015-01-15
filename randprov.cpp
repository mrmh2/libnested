#include "randprov.h"

RandProvider::RandProvider(double lowerBound, double upperBound) {
    distribution = new uniform_real_distribution<double>(lowerBound, upperBound);
//    distribution =
}

double RandProvider::randUniformDouble() {
    /* Generate a double uniformly distributed in the range (lowerBound, upperBound) */
    return (*distribution)(generator);
}
