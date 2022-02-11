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

#include "energy_sensitive_detector_channel.hpp"
#include "polynomial.hpp"

EnergySensitiveDetectorChannel::EnergySensitiveDetectorChannel(
    const string name, const size_t module, const size_t channel,
    const function<double(const double, const long long)> energy_calibration,
    const function<double(const double)> time_calibration,
    const function<bool(const double)> time_vs_reference_time_gate)
    : Channel(name, module, channel), energy_calibration(energy_calibration),
      time_calibration(time_calibration),
      time_vs_reference_time_gate(time_vs_reference_time_gate),
      energy_calibrated(numeric_limits<double>::quiet_NaN()),
      time_calibrated(numeric_limits<double>::quiet_NaN()),
      timestamp_calibrated(numeric_limits<double>::quiet_NaN()),
      time_vs_reference_time_calibrated(numeric_limits<double>::quiet_NaN()) {}

EnergySensitiveDetectorChannel::EnergySensitiveDetectorChannel(
    const string name, const size_t module, const size_t channel,
    const vector<double> energy_calibration_parameters,
    const function<double(const double)> time_calibration,
    const function<bool(const double)> time_vs_reference_time_gate)
    : Channel(name, module, channel),
      energy_calibration(Polynomial(energy_calibration_parameters)),
      time_calibration(time_calibration),
      time_vs_reference_time_gate(time_vs_reference_time_gate),
      energy_calibrated(numeric_limits<double>::quiet_NaN()),
      time_calibrated(numeric_limits<double>::quiet_NaN()),
      timestamp_calibrated(numeric_limits<double>::quiet_NaN()),
      time_vs_reference_time_calibrated(numeric_limits<double>::quiet_NaN()) {}

EnergySensitiveDetectorChannel::EnergySensitiveDetectorChannel(
    const string name, const size_t module, const size_t channel,
    const string energy_calibration_parameters,
    const function<double(const double)> time_calibration,
    const function<bool(const double)> time_vs_reference_time_gate)
    : Channel(name, module, channel),
      energy_calibration(Polynomial(energy_calibration_parameters)),
      time_calibration(time_calibration),
      time_vs_reference_time_gate(time_vs_reference_time_gate),
      energy_calibrated(numeric_limits<double>::quiet_NaN()),
      time_calibrated(numeric_limits<double>::quiet_NaN()),
      timestamp_calibrated(numeric_limits<double>::quiet_NaN()),
      time_vs_reference_time_calibrated(numeric_limits<double>::quiet_NaN()) {}

void EnergySensitiveDetectorChannel::reset_calibrated_leaves() {
    energy_calibrated = numeric_limits<double>::quiet_NaN();
    time_calibrated = numeric_limits<double>::quiet_NaN();
    timestamp_calibrated = numeric_limits<double>::quiet_NaN();
    time_vs_reference_time_calibrated = numeric_limits<double>::quiet_NaN();
}