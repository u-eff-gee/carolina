#pragma once

#include <vector>

using std::vector;

#include "channel.hpp"

struct Detector {
    Detector(const string name, const vector<Channel> channels);

    const string name;
    vector<Channel> channels;

    virtual void activate_branches(TTree *tree) = 0;
    virtual void create_branches(TTree *tree) = 0;
    virtual void register_branches(TTree *tree) = 0;
    virtual void reset() = 0;
};