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

#include <cmath>

using std::isnan;

#include <memory>

using std::dynamic_pointer_cast;

#include <stdexcept>

using std::invalid_argument;

#include <string>

using std::to_string;

#include "energy_sensitive_detector.hpp"
#include "energy_sensitive_detector_channel.hpp"

EnergySensitiveDetector::EnergySensitiveDetector(
    const string name, const vector<shared_ptr<Channel>> channels,
    const shared_ptr<EnergySensitiveDetectorGroup> group)
    : Detector(name, channels, group),
      addback_energy(numeric_limits<double>::quiet_NaN()),
      addback_time(numeric_limits<double>::quiet_NaN()) {

    for (size_t n_c_0 = 0; n_c_0 < channels.size(); ++n_c_0) {
        addback_coincidence_windows.push_back(vector<pair<double, double>>());
        for (size_t n_c_1 = n_c_0 + 1; n_c_1 < channels.size(); n_c_1++) {
            addback_coincidence_windows[n_c_0].push_back(
                {-numeric_limits<double>::max(),
                 numeric_limits<double>::max()});
        }
    }

    skip_channel = vector<bool>(channels.size(), false);
    addback_energies =
        vector<double>(channels.size(), numeric_limits<double>::quiet_NaN());
    addback_times =
        vector<double>(channels.size(), numeric_limits<double>::quiet_NaN());
}

EnergySensitiveDetector::EnergySensitiveDetector(
    const string name, const vector<shared_ptr<Channel>> channels,
    const shared_ptr<EnergySensitiveDetectorGroup> group,
    const vector<vector<pair<double, double>>> addback_coincidence_windows)
    : Detector(name, channels, group),
      addback_coincidence_windows(addback_coincidence_windows),
      addback_energy(numeric_limits<double>::quiet_NaN()),
      addback_time(numeric_limits<double>::quiet_NaN()) {

    if (addback_coincidence_windows.size() != channels.size() - 1) {
        throw invalid_argument(
            "With " + to_string(channels.size()) +
            " channels, the matrix that contains the coincidence windows for "
            "the addback must have exactly " +
            to_string(channels.size() - 1) + " lines.");
    }

    for (size_t n_c_0 = 0; n_c_0 < channels.size() - 1; ++n_c_0) {
        if (addback_coincidence_windows[n_c_0].size() !=
            channels.size() - n_c_0 - 1) {
            throw invalid_argument(
                "Line number " + to_string(n_c_0) +
                " of the matrix that contains the coincidence windows for the "
                "addback must have exactly " +
                to_string(channels.size() - n_c_0 - 1) + " entries.");
        }
    }

    skip_channel = vector<bool>(channels.size(), false);
    addback_energies =
        vector<double>(channels.size(), numeric_limits<double>::quiet_NaN());
    addback_times =
        vector<double>(channels.size(), numeric_limits<double>::quiet_NaN());
}

bool EnergySensitiveDetector::inside_addback_coincidence_window(
    const size_t n_channel_1, const size_t n_channel_2) {
    return addback_coincidence_windows[n_channel_1]
                                      [n_channel_2 - n_channel_1 - 1]
                                          .first <=
               dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                   channels[n_channel_1])
                       ->time_calibrated -
                   dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                       channels[n_channel_2])
                       ->time_calibrated &&
           dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
               channels[n_channel_1])
                       ->time_calibrated -
                   dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                       channels[n_channel_2])
                       ->time_calibrated <=
               addback_coincidence_windows[n_channel_1]
                                          [n_channel_2 - n_channel_1 - 1]
                                              .second;
}

void EnergySensitiveDetector::filter_addback() {
    for (size_t n_channel = 0; n_channel < channels.size(); ++n_channel) {
        if (isnan(addback_energy) ||
            addback_energies[n_channel] > addback_energy) {
            addback_energy = addback_energies[n_channel];
            addback_time = addback_times[n_channel];
            addback_time_vs_reference_time =
                dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                    channels[n_channel])
                    ->time_vs_reference_time_calibrated;
        }
    }
}

void EnergySensitiveDetector::addback() {
    size_t maximum_energy_deposition_index = 0;

    for (size_t n_c_0 = 0; n_c_0 < channels.size(); ++n_c_0) {
        if (!isnan(dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                       channels[n_c_0])
                       ->energy_calibrated) &&
            !skip_channel[n_c_0]) {
            addback_energies[n_c_0] =
                dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                    channels[n_c_0])
                    ->energy_calibrated;
            addback_times[n_c_0] =
                dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                    channels[n_c_0])
                    ->time_calibrated;
            maximum_energy_deposition_index = n_c_0;

            for (size_t n_c_1 = n_c_0 + 1; n_c_1 < channels.size(); ++n_c_1) {
                if (!isnan(dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                               channels[n_c_1])
                               ->energy_calibrated) &&
                    !skip_channel[n_c_1] &&
                    inside_addback_coincidence_window(n_c_0, n_c_1)) {
                    addback_energies[n_c_0] +=
                        dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                            channels[n_c_1])
                            ->energy_calibrated;
                    skip_channel[n_c_1] = true;
                    if (dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                            channels[n_c_1])
                            ->energy_calibrated >
                        dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                            channels[n_c_0])
                            ->energy_calibrated) {
                        maximum_energy_deposition_index = n_c_1;
                    }
                } else {
                    skip_channel[n_c_1] = true;
                }
            }
            addback_times[n_c_0] =
                dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                    channels[maximum_energy_deposition_index])
                    ->time_calibrated;
            skip_channel[n_c_0] = true;
        }
    }

    filter_addback();
}

double EnergySensitiveDetector::get_calibrated_and_RF_gated_energy() const {
    if (channels.size() > 1) {
        return addback_energy;
    }
    return dynamic_pointer_cast<EnergySensitiveDetectorChannel>(channels[0])
        ->energy_calibrated;
}

void EnergySensitiveDetector::reset_calibrated_leaves() {
    for (size_t n_channel = 0; n_channel < channels.size(); ++n_channel) {
        channels[n_channel]->reset_calibrated_leaves();
        skip_channel[n_channel] = false;
        addback_energies[n_channel] = numeric_limits<double>::quiet_NaN();
        addback_times[n_channel] = numeric_limits<double>::quiet_NaN();
    }

    addback_energy = numeric_limits<double>::quiet_NaN();
    addback_time = numeric_limits<double>::quiet_NaN();
    addback_time_vs_reference_time = numeric_limits<double>::quiet_NaN();
}

void EnergySensitiveDetector::set_up_calibrated_branches_for_reading(
    TTree *tree) {
    for (size_t n_channel = 0; n_channel < channels.size(); ++n_channel) {
        tree->SetBranchStatus(
            (name + "_" +
             dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                 channels[n_channel])
                 ->name +
             "_e")
                .c_str(),
            1);
        tree->SetBranchStatus(
            (name + "_" +
             dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                 channels[n_channel])
                 ->name +
             "_t")
                .c_str(),
            1);
        tree->SetBranchStatus(
            (name + "_" +
             dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                 channels[n_channel])
                 ->name +
             "_ts")
                .c_str(),
            1);
        tree->SetBranchStatus(
            (name + "_" +
             dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                 channels[n_channel])
                 ->name +
             "_t_vs_RF")
                .c_str(),
            1);
        tree->SetBranchAddress(
            (name + "_" +
             dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                 channels[n_channel])
                 ->name +
             "_e")
                .c_str(),
            &dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                 channels[n_channel])
                 ->energy_calibrated);
        tree->SetBranchAddress(
            (name + "_" +
             dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                 channels[n_channel])
                 ->name +
             "_t")
                .c_str(),
            &dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                 channels[n_channel])
                 ->time_calibrated);
        tree->SetBranchAddress(
            (name + "_" +
             dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                 channels[n_channel])
                 ->name +
             "_ts")
                .c_str(),
            &dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                 channels[n_channel])
                 ->timestamp_calibrated);
        tree->SetBranchAddress(
            (name + "_" +
             dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                 channels[n_channel])
                 ->name +
             "_t_vs_RF")
                .c_str(),
            &dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                 channels[n_channel])
                 ->time_vs_reference_time_calibrated);
    }

    if (channels.size() > 1) {
        tree->SetBranchStatus((name + "_addback_energy").c_str(), 1);
        tree->SetBranchStatus((name + "_addback_time").c_str(), 1);
        tree->SetBranchStatus(
            (name + "_addback_time_vs_reference_time").c_str(), 1);
        tree->SetBranchAddress((name + "_addback_energy").c_str(),
                               &addback_energy);
        tree->SetBranchAddress((name + "_addback_time").c_str(), &addback_time);
        tree->SetBranchAddress(
            (name + "_addback_time_vs_reference_time").c_str(),
            &addback_time_vs_reference_time);
    }
}

void EnergySensitiveDetector::set_up_calibrated_branches_for_writing(
    TTree *tree) {
    for (size_t n_channel = 0; n_channel < channels.size(); ++n_channel) {
        tree->Branch((name + "_" +
                      dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                          channels[n_channel])
                          ->name +
                      "_e")
                         .c_str(),
                     &dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                          channels[n_channel])
                          ->energy_calibrated);
        tree->Branch((name + "_" +
                      dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                          channels[n_channel])
                          ->name +
                      "_t")
                         .c_str(),
                     &dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                          channels[n_channel])
                          ->time_calibrated);
        tree->Branch((name + "_" +
                      dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                          channels[n_channel])
                          ->name +
                      "_ts")
                         .c_str(),
                     &dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                          channels[n_channel])
                          ->timestamp_calibrated);
        tree->Branch((name + "_" +
                      dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                          channels[n_channel])
                          ->name +
                      "_t_vs_RF")
                         .c_str(),
                     &dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                          channels[n_channel])
                          ->time_vs_reference_time_calibrated);
    }

    if (channels.size() > 1) {
        tree->Branch((name + "_addback_energy").c_str(), &addback_energy);
        tree->Branch((name + "_addback_time").c_str(), &addback_time);
        tree->Branch((name + "_addback_time_vs_reference_time").c_str(),
                     &addback_time_vs_reference_time);
    }
}