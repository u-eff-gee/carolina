/*
     This file is part of carolina.

    carolina is free software: you can redistribute it and/or modify it under
   the terms of the GNU General Public License as published by the Free Software
   Foundation, either version 3 of the License, or (at your option) any later
   version.

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

#include <limits>

using std::numeric_limits;

#include <string>

using std::string;

#include "channel.hpp"

struct EnergySensitiveDetectorChannel final : public Channel {
    EnergySensitiveDetectorChannel(
        const string name, const size_t module, const size_t channel,
        const function<double(const double, const long long)>
            energy_calibration =
                [](const double amplitude,
                   [[maybe_unused]] const long long n_entry) {
                    return amplitude;
                },
        const function<double(const double)> time_calibration =
            []([[maybe_unused]] const double energy) { return 1.; },
        const function<bool(const double)> time_vs_time_RF_gate =
            []([[maybe_unused]] const double time_vs_time_RF) { return true; })
        : Channel(name, module, channel),
          energy_calibration(energy_calibration),
          time_calibration(time_calibration),
          time_vs_time_RF_gate(time_vs_time_RF_gate),
          energy_calibrated(numeric_limits<double>::quiet_NaN()),
          time_calibrated(numeric_limits<double>::quiet_NaN()),
          timestamp_calibrated(numeric_limits<double>::quiet_NaN()),
          time_vs_time_RF_calibrated(numeric_limits<double>::quiet_NaN()) {}

    const function<double(const int, const double)> energy_calibration;
    const function<double(const double)> time_calibration;
    const function<bool(const double)> time_vs_time_RF_gate;

    double energy_calibrated, time_calibrated, timestamp_calibrated,
        time_vs_time_RF_calibrated;

    bool apply_RF_gate() { return time_vs_time_RF_gate(time_calibrated); };
    void reset_calibrated_leaves() override final;
};
