#pragma once

#include <cmath>

using std::isnan;

#include <functional>

using std::function;

#include <string>

using std::string;

struct Channel{
    const string name;

    double &energy_branch;
    const function<double(const double)> energy_calibration;
    double calibrate(){
        
        if(!isnan(energy_branch)){
            return energy_calibration(energy_branch);
        }

        return 0.;
    }

    double &time_branch;
    const function<double(const double)> time_calibration;
};