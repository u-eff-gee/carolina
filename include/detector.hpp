#pragma once

#include <limits>

using std::numeric_limits;

#include <string>

using std::string;

#include <vector>

using std::vector;

#include "channel.hpp"
#include "detector_group.hpp"

struct Detector {
    Detector(const string name, const vector<Channel> channels,
             const DetectorGroup group);
    Detector(
        const string name, const vector<Channel> channels,
        const DetectorGroup group,
        const vector<vector<pair<double, double>>> addback_coincidence_windows);

    const string name;
    vector<Channel> channels;
    const DetectorGroup group;
    vector<vector<pair<double, double>>> addback_coincidence_windows;

    vector<bool> skip_channel;
    vector<double> addback_energies;
    vector<double> addback_times;

    double addback_energy;
    double addback_time;

    void addback();
    void activate_branches(TTree *tree);
    void create_branches(TTree *tree);
    void register_branches(TTree *tree);
    void reset();
};