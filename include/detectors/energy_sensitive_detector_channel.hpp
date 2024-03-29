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

#include <vector>

using std::vector;

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
        const function<double(const double, const double)> time_calibration =
            [](const double raw_time, [[maybe_unused]] const double energy) {
                return raw_time;
            },
        const function<bool(const double)> time_vs_reference_time_gate =
            []([[maybe_unused]] const double time_vs_reference_time) {
                return true;
            });

    const function<double(const double, const long long)> energy_calibration;
    const function<double(const double, const double)> time_calibration;
    const function<bool(const double)> time_vs_reference_time_gate;

    double energy_calibrated, time_calibrated, timestamp_calibrated,
        time_vs_reference_time_calibrated;

    void reset_calibrated_leaves() override final;
};
