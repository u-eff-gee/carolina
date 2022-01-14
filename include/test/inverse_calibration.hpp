/*
     This file is part of carolina.

    carolina is free software: you can redistribute it and/or modify it under the terms of 
    the GNU General Public License as published by the Free Software Foundation, 
    either version 3 of the License, or (at your option) any later version.

    carolina is distributed in the hope that it will be useful, but WITHOUT ANY 
    WARRANTY; without even the implied warranty of MERCHANTABILITY or 
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for 
    more details.

    You should have received a copy of the GNU General Public License along with 
    carolina. If not, see <https://www.gnu.org/licenses/>. 
*/

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