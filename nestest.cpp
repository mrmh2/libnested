#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include <iterator>

#include "dataset.h"
#include "libnested.h"
#include "models.h"

#include "csv.h"

TEST_CASE( "Linear model correct", "[Linear model]") {
  vector<double> params {0.5, 0.5};
  vector<double> data {0, 1, 2, 3, 4, 5};

  vector<double> results = linearModel(data, params);
  vector<double> expected_results {0.5, 1, 1.5, 2, 2.5, 3};

  REQUIRE( results == expected_results );
}

TEST_CASE( "Uniform prior correct", "[Uniform prior]") {
  double r = uniformPrior(1.5, 0, 2);

  REQUIRE( r == 3 );
}

TEST_CASE ( "DataSet load correct", "[DataSet]") {
  DataSet ftdata("data/ftdata.csv");

  REQUIRE ( ftdata.t[0] == 0.923884 );
  REQUIRE ( abs(ftdata.y[3] - 0.298496) < 0.000001 );
  REQUIRE ( ftdata.y.size() == 14 );
}

