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

#include "counter_detector_channel.hpp"

#include <limits>

using std::numeric_limits;

CounterDetectorChannel::CounterDetectorChannel(const string name,
                                               const size_t module,
                                               const size_t channel)
    : Channel(name, module, channel), previous_counts(0) {}

void CounterDetectorChannel::reset_calibrated_leaves() {
    // Do not reset previous_counts here.
    // This function is only used to reset values that are actually written to
    // file. previous_counts is just an auxiliary quantity to calculate the
    // rate.
    count_rate = numeric_limits<double>::quiet_NaN();
}