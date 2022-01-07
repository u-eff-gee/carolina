#pragma once

#include <string>

using std::string;

#include <utility>

using std::pair;

#include <vector>

using std::vector;

#include "detector.hpp"

struct EnergySensitiveDetector final : public Detector {
    EnergySensitiveDetector(const string name,
                            const vector<shared_ptr<Channel>> channels);
    EnergySensitiveDetector(const string name,
                            const vector<shared_ptr<Channel>> channels,
                            const vector<double> addback_energy_thresholds);
    EnergySensitiveDetector(
        const string name, const vector<shared_ptr<Channel>> channels,
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
    double get_calibrated_and_RF_gated_energy() const;
    void reset_calibrated_leaves() override final;
    void set_up_calibrated_branches_for_reading(TTree *tree) override final;
    void set_up_calibrated_branches_for_writing(TTree *tree) override final;
};