#pragma once

#include <cmath>

using std::isnan;

#include <functional>

using std::function;

#include <limits>

using std::numeric_limits;

#include <memory>

using std::shared_ptr;

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
        const string name, const shared_ptr<Module> module, const size_t leaf,
        const vector<pair<int, vector<double>>> energy_calibration_parameters,
        const function<double(double)> time_calibration,
        const function<bool(double)> time_vs_time_RF_gate,
        const double amplitude_threshold = 0.)
        : name(name), module(module), leaf(leaf),
          energy_calibration_parameters(energy_calibration_parameters),
          time_calibration(time_calibration),
          time_vs_time_RF_gate(time_vs_time_RF_gate),
          energy_calibrated(numeric_limits<double>::quiet_NaN()),
          time_calibrated(numeric_limits<double>::quiet_NaN()),
          timestamp_calibrated(numeric_limits<double>::quiet_NaN()),
          time_vs_time_RF_calibrated(numeric_limits<double>::quiet_NaN()),
          amplitude_threshold(amplitude_threshold) {}

    const string name;
    const shared_ptr<Module> module;
    const size_t leaf;
    vector<pair<int, vector<double>>> energy_calibration_parameters;
    const function<double(const double)> time_calibration;
    const function<bool(const double)> time_vs_time_RF_gate;

    double energy_calibrated, time_calibrated, timestamp_calibrated,
        time_vs_time_RF_calibrated;
    const double amplitude_threshold;

    void calibrate(const int n_entry);
    double get_amplitude() const { return module->get_amplitude(leaf); }
    double get_time() const { return module->get_time(leaf); }
    double get_timestamp() const { return module->get_timestamp(leaf); }
    double get_time_RF() const { return module->get_time_RF(leaf); }

    double polynomial_calibration(double uncalibrated,
                                  vector<double> calibration_parameters) const;
    void reset();
};
