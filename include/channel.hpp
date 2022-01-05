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

#include "digitizer_module.hpp"
#include "vme.hpp"

struct Channel {
    Channel(const string name, const size_t module,
            const size_t leaf,
            const function<double(const int, const double)> energy_calibration,
            const function<double(const double)> time_calibration,
            const function<bool(const double)> time_vs_time_RF_gate,
            const double amplitude_threshold = 0.)
        : name(name), module(module), leaf(leaf),
          energy_calibration(energy_calibration),
          time_calibration(time_calibration),
          time_vs_time_RF_gate(time_vs_time_RF_gate),
          energy_calibrated(numeric_limits<double>::quiet_NaN()),
          time_calibrated(numeric_limits<double>::quiet_NaN()),
          timestamp_calibrated(numeric_limits<double>::quiet_NaN()),
          time_vs_time_RF_calibrated(numeric_limits<double>::quiet_NaN()),
          amplitude_threshold(amplitude_threshold) {}

    const string name;
    const size_t module;
    const size_t leaf;
    const function<double(const int, const double)> energy_calibration;
    const function<double(const double)> time_calibration;
    const function<bool(const double)> time_vs_time_RF_gate;

    double energy_calibrated, time_calibrated, timestamp_calibrated,
        time_vs_time_RF_calibrated;
    const double amplitude_threshold;

    void reset();
};
