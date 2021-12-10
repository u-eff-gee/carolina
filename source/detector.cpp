#include <stdexcept>

using std::invalid_argument;

#include <string>

using std::to_string;

#include "detector.hpp"

Detector::Detector(const string name, const vector<Channel> channels,
                   const DetectorGroup group)
    : name(name), channels(channels), group(group) {

    for (size_t n_c_0 = 0; n_c_0 < channels.size(); ++n_c_0) {
        addback_coincidence_windows.push_back(vector<pair<double, double>>());
        for (size_t n_c_1 = n_c_0 + 1; n_c_1 < channels.size(); n_c_1++) {
            addback_coincidence_windows[n_c_0].push_back(
                {-numeric_limits<double>::max(),
                 numeric_limits<double>::max()});
        }
    }

    skip_channel = vector<bool>(channels.size(), false);
    addback_energies = vector<double>(channels.size(), 0.);
    addback_times = vector<double>(channels.size(), 0.);
}

Detector::Detector(
    const string name, const vector<Channel> channels,
    const DetectorGroup group,
    const vector<vector<pair<double, double>>> addback_coincidence_windows)
    : name(name), channels(channels), group(group),
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
    addback_energies = vector<double>(channels.size(), 0.);
    addback_times = vector<double>(channels.size(), 0.);
}

void Detector::addback() {
    for (size_t n_c = 0; n_c < channels.size(); ++n_c) {
        skip_channel[n_c] = false;
        addback_energies[n_c] = 0.;
    }

    size_t maximum_energy_deposition_index = 0;

    for (size_t n_c_0 = 0; n_c_0 < channels.size(); ++n_c_0) {
        if (channels[n_c_0].energy_calibrated != 0. && !skip_channel[n_c_0]) {
            addback_energies[n_c_0] = channels[n_c_0].energy_calibrated;
            addback_times[n_c_0] = channels[n_c_0].time_calibrated;
            maximum_energy_deposition_index = n_c_0;

            for (size_t n_c_1 = n_c_0 + 1; n_c_1 < channels.size(); ++n_c_1) {
                if (channels[n_c_1].energy_calibrated > 0.) {
                    if (!skip_channel[n_c_1] &&
                        addback_coincidence_windows[n_c_0][n_c_1].first <=
                            channels[n_c_0].time_calibrated -
                                channels[n_c_1].time_calibrated &&
                        channels[n_c_0].time_calibrated -
                                channels[n_c_1].time_calibrated <=
                            addback_coincidence_windows[n_c_0][n_c_1].second) {
                        addback_energies[n_c_0] +=
                            channels[n_c_1].energy_calibrated;
                        skip_channel[n_c_1] = true;
                        if (channels[n_c_1].energy_calibrated >
                            channels[n_c_0].energy_calibrated) {
                            maximum_energy_deposition_index = n_c_1;
                        }
                    }
                } else {
                    skip_channel[n_c_1] = true;
                }
            }
            addback_times[n_c_0] =
                channels[maximum_energy_deposition_index].time_calibrated;
        }
        skip_channel[n_c_0] = true;
    }

    for(size_t n_channel = 0; n_channel < channels.size(); ++n_channel){
        if(addback_energies[n_channel] > 0.){
            if(isnan(addback_energy)){
                addback_energy = addback_energies[n_channel];
                addback_time = addback_times[n_channel];
            } else if(addback_energies[n_channel] > addback_energy){
                addback_energy = addback_energies[n_channel];
                addback_time = addback_times[n_channel];                
            }
        }
    }
}

void Detector::activate_branches(TTree *tree) {
    for (size_t n_channel = 0; n_channel < channels.size(); ++n_channel) {
        tree->SetBranchStatus(
            (name + "_" + channels[n_channel].name + "_e").c_str(), 1);
        tree->SetBranchStatus(
            (name + "_" + channels[n_channel].name + "_t").c_str(), 1);
        tree->SetBranchStatus(
            (name + "_" + channels[n_channel].name + "_ts").c_str(), 1);
        tree->SetBranchStatus(
            (name + "_" + channels[n_channel].name + "_t_vs_RF").c_str(), 1);
    }
    tree->SetBranchStatus((name + "_addback_energy").c_str(), 1);
    tree->SetBranchStatus((name + "_addback_time").c_str(), 1);
}

void Detector::create_branches(TTree *tree) {
    for (size_t n_channel = 0; n_channel < channels.size(); ++n_channel) {
        tree->Branch((name + "_" + channels[n_channel].name + "_e").c_str(),
                     &channels[n_channel].energy_calibrated);
        tree->Branch((name + "_" + channels[n_channel].name + "_t").c_str(),
                     &channels[n_channel].time_calibrated);
        tree->Branch((name + "_" + channels[n_channel].name + "_ts").c_str(),
                     &channels[n_channel].timestamp_calibrated);
        tree->Branch(
            (name + "_" + channels[n_channel].name + "_t_vs_RF").c_str(),
            &channels[n_channel].time_vs_time_RF_calibrated);
    }

    tree->Branch((name + "_addback_energy").c_str(), &addback_energy);
    tree->Branch((name + "_addback_time").c_str(), &addback_time);
}

void Detector::register_branches(TTree *tree) {
    for (size_t n_channel = 0; n_channel < channels.size(); ++n_channel) {
        tree->SetBranchAddress(
            (name + "_" + channels[n_channel].name + "_e").c_str(),
            &channels[n_channel].energy_calibrated);
        tree->SetBranchAddress(
            (name + "_" + channels[n_channel].name + "_t").c_str(),
            &channels[n_channel].time_calibrated);
        tree->SetBranchAddress(
            (name + "_" + channels[n_channel].name + "_ts").c_str(),
            &channels[n_channel].timestamp_calibrated);
        tree->SetBranchAddress(
            (name + "_" + channels[n_channel].name + "_t_vs_RF").c_str(),
            &channels[n_channel].time_vs_time_RF_calibrated);
    }

    tree->SetBranchAddress((name + "_addback_energy").c_str(), &addback_energy);
    tree->SetBranchAddress((name + "_addback_time").c_str(), &addback_time);
}

void Detector::reset() {
    for (size_t n_channel = 0; n_channel < channels.size(); ++n_channel) {
        channels[n_channel].reset();
    }

    addback_energy = numeric_limits<double>::quiet_NaN();
    addback_time = numeric_limits<double>::quiet_NaN();
}