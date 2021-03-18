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

    const string energy_branch_name;
    const unsigned int energy_branch_index;
    const HistogramProperties energy_raw_histogram_properties;
    const vector<double> energy_calibration_parameters;

    const string time_branch_name;
    const unsigned int time_branch_index;
    const vector<double> time_calibration_parameters;

    const string timestamp_branch_name;
    const unsigned int timestamp_branch_index;
    const vector<double> timestamp_calibration_parameters;
};
