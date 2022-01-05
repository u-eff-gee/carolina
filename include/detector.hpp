#pragma once

#include <memory>

using std::shared_ptr;

#include <vector>

using std::vector;

#include "channel.hpp"

#include "TTree.h"

struct Detector {
    Detector(const string name, const vector<shared_ptr<Channel>> channels);

    const string name;
    vector<shared_ptr<Channel>> channels;

    virtual void activate_branches(TTree *tree) = 0;
    virtual void create_branches(TTree *tree) = 0;
    virtual void register_branches(TTree *tree) = 0;
    virtual void reset() = 0;
};