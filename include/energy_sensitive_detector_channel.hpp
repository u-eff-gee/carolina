#pragma once

#include <functional>

using std::function;

#include <limits>

using std::numeric_limits;

#include <string>

using std::string;

#include "channel.hpp"
#include "digitizer_module.hpp"
#include "vme.hpp"

struct EnergySensitiveDetectorChannel final : public Channel {
    EnergySensitiveDetectorChannel(
        const string name, const size_t module, const size_t channel,
        const function<double(const double, const long long)>
            energy_calibration =
                [](const double amplitude,
                   [[maybe_unused]] const long long n_entry) {
                    return amplitude;
                },
        const function<double(const double, const double)> time_calibration =
            [](const double time, [[maybe_unused]] const double energy) {
                return time;
            },
        const function<bool(const double)> time_vs_time_RF_gate =
            []([[maybe_unused]] const double time_vs_time_RF) { return true; },
        const double amplitude_threshold = 0.)
        : Channel(name, module, channel),
          energy_calibration(energy_calibration),
          time_calibration(time_calibration),
          time_vs_time_RF_gate(time_vs_time_RF_gate),
          energy_calibrated(numeric_limits<double>::quiet_NaN()),
          time_calibrated(numeric_limits<double>::quiet_NaN()),
          timestamp_calibrated(numeric_limits<double>::quiet_NaN()),
          time_vs_time_RF_calibrated(numeric_limits<double>::quiet_NaN()),
          amplitude_threshold(amplitude_threshold) {}

    const function<double(const int, const double)> energy_calibration;
    const function<double(const double, const double)> time_calibration;
    const function<bool(const double)> time_vs_time_RF_gate;

    double energy_calibrated, time_calibrated, timestamp_calibrated,
        time_vs_time_RF_calibrated;
    const double amplitude_threshold;

    void reset() override final;
};
