#pragma once

#include <limits>

using std::numeric_limits;

#include <string>

using std::string;

#include <vector>

using std::vector;

#include "channel.hpp"
#include "detector.hpp"
#include "detector_group.hpp"

struct EnergySensitiveDetector final : public Detector {
    EnergySensitiveDetector(const string name, const vector<Channel> channels);
    EnergySensitiveDetector(const string name, const vector<Channel> channels,
                            const vector<double> addback_energy_thresholds);
    EnergySensitiveDetector(
        const string name, const vector<Channel> channels,
        const vector<double> addback_energy_thresholds,
        const vector<vector<pair<double, double>>> addback_coincidence_windows);

    vector<double> addback_energy_thresholds;
    vector<vector<pair<double, double>>> addback_coincidence_windows;

    vector<bool> skip_channel;
    vector<double> addback_energies;
    vector<double> addback_times;

    double addback_energy;
    double addback_time;

    void addback();
    void activate_branches(TTree *tree) override final;
    void create_branches(TTree *tree) override final;
    void register_branches(TTree *tree) override final;
    void reset() override final;
};