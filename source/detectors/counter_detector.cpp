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

#include <memory>

using std::dynamic_pointer_cast;

#include "counter_detector.hpp"

CounterDetector::CounterDetector(const string name,
                                 const vector<CounterDetectorChannel> channels,
                                 const size_t group)
    : Detector(name, group), channels(channels) {}

void CounterDetector::set_up_calibrated_branches_for_reading(TTree *tree) {
    for (size_t n_channel = 0; n_channel < channels.size(); ++n_channel) {
        tree->SetBranchStatus((name + "_" + channels[n_channel].name).c_str(),
                              1);
        tree->SetBranchAddress((name + "_" + channels[n_channel].name).c_str(),
                               &channels[n_channel].count_rate);
    }
}

void CounterDetector::set_up_calibrated_branches_for_writing(TTree *tree) {
    for (size_t n_channel = 0; n_channel < channels.size(); ++n_channel) {
        tree->Branch((name + "_" + channels[n_channel].name).c_str(),
                     &channels[n_channel].count_rate);
    }
}

void CounterDetector::reset_calibrated_leaves() {
    for (size_t n_channel = 0; n_channel < channels.size(); ++n_channel) {
        channels[n_channel].reset_calibrated_leaves();
    }
}