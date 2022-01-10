#pragma once

#include <functional>

using std::function;

#include "TGraph.h"

template<unsigned int n_points>
TGraph invert_calibration(function<double(const double)> calibration,
                          const double x_min, const double x_max) {

    const double x_increment = (x_max-x_min)/n_points;
    double x[n_points], y[n_points]; 

    for(unsigned int i = 0; i < n_points; ++i){
        x[i] = x_min + i*x_increment;
        y[i] = calibration(x[i]);
    }

    return TGraph(n_points, y, x);
}