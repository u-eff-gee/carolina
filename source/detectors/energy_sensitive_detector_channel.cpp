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

void EnergySensitiveDetectorChannel::reset_calibrated_leaves() {
    energy_calibrated = numeric_limits<double>::quiet_NaN();
    time_calibrated = numeric_limits<double>::quiet_NaN();
    timestamp_calibrated = numeric_limits<double>::quiet_NaN();
    time_vs_reference_time_calibrated = numeric_limits<double>::quiet_NaN();
}