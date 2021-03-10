#pragma once

#include <cmath>

using std::isnan;

#include <functional>

using std::function;

#include <string>

using std::string;

struct HistogramProperties{
	const unsigned int n_bins;
	const double minimum;
	const double maximum;
};

struct Channel{
    const string name;

    double &energy_branch;
    const HistogramProperties energy_histogram_properties;
    const function<double(const double)> energy_calibration;
    double calibrate() const {
        
        if(!isnan(energy_branch)){
            return energy_calibration(energy_branch);
        }

        return 0.;
    }

    double &time_branch;
    const function<double(const double)> time_calibration;
};
