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
             const DetectorGroup group,
             const double addback_coincidence_window =
                 numeric_limits<double>::max());

    const string name;
    vector<Channel> channels;
    const DetectorGroup group;
    const double addback_coincidence_window;

    vector<bool> added_back;
    vector<double> addback_energies;
    vector<double> addback_times;

    void addback();
    void activate_branches(TTree *tree);
    void create_branches(TTree *tree);
    void register_branches(TTree *tree);
    void reset();
};