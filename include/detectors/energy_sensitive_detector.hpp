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

#include <string>

using std::string;

#include <utility>

using std::pair;

#include <vector>

using std::vector;

#include "detector.hpp"
#include "energy_sensitive_detector_channel.hpp"

struct EnergySensitiveDetector final : public Detector {
    EnergySensitiveDetector(
        const string name,
        const vector<EnergySensitiveDetectorChannel> channels,
        const size_t group,
        const vector<vector<function<bool(const double)>>>
            addback_coincidence_gates = {});

    vector<EnergySensitiveDetectorChannel> channels;

    vector<vector<function<bool(const double)>>> addback_coincidence_gates;

    vector<bool> skip_channel;
    vector<double> addback_energies;
    vector<double> addback_times;

    double addback_energy;
    double addback_time;
    double addback_time_vs_reference_time;

    void addback();
    void filter_addback();
    double get_calibrated_and_RF_gated_energy() const;
    void reset_calibrated_leaves() override final;
    void set_up_calibrated_branches_for_reading(TTree *tree) override final;
    void set_up_calibrated_branches_for_writing(TTree *tree) override final;
};