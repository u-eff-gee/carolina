#pragma once

#include <cmath>

using std::isnan;

#include <string>

using std::string;

#include <utility>

using std::pair;

#include <vector>

using std::vector;

#include "module.hpp"
#include "vme.hpp"

struct Channel {
    Channel(
        const string name, Module &module, const size_t leaf,
        const vector<pair<int, vector<double>>> energy_calibration_parameters,
        const double amplitude_threshold = 0.)
        : name(name), module(module), leaf(leaf),
          energy_calibration_parameters(energy_calibration_parameters),
          amplitude_threshold(amplitude_threshold) {}

    const string name;
    Module &module;
    const size_t leaf;
    vector<pair<int, vector<double>>> energy_calibration_parameters;

    double energy_calibrated, time_calibrated, timestamp_calibrated;
    const double amplitude_threshold;

    double get_amplitude() const { return module.get_amplitude(leaf); }
    double get_time() const { return module.get_time(leaf); }
    double get_timestamp() const { return module.get_timestamp(leaf); }

    double polynomial_calibration(double uncalibrated,
                                  vector<double> calibration_parameters) const;

    void calibrate(const int n_entry);
};
