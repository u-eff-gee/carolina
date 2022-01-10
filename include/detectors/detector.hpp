#pragma once

#include <memory>

using std::shared_ptr;

#include <vector>

using std::vector;

#include "channel.hpp"

#include "TTree.h"

enum DetectorType { energy_sensitive, counter };

struct Detector {
    Detector(const string name, const DetectorType type,
             const vector<shared_ptr<Channel>> channels);

    const string name;
    const DetectorType type;
    vector<shared_ptr<Channel>> channels;

    virtual void reset_calibrated_leaves() = 0;
    virtual void set_up_calibrated_branches_for_reading(TTree *tree) = 0;
    virtual void set_up_calibrated_branches_for_writing(TTree *tree) = 0;
};