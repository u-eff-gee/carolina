#pragma once

#include <vector>

using std::vector;

#include "detector.hpp"
#include "detector_group.hpp"
#include "module.hpp"

struct DetectorSetup {
    DetectorSetup(vector<shared_ptr<Module>> modules,
                  const vector<DetectorGroup> detector_groups,
                  vector<Detector> detectors)
        : modules(modules), detector_groups(detector_groups),
          detectors(detectors) {}

    vector<shared_ptr<Module>> modules;
    const vector<DetectorGroup> detector_groups;
    vector<Detector> detectors;

    void activate_branches(TTree *tree);
    void calibrate(const int n_entry);
    void create_branches(TTree *tree);
    vector<string> get_branch_names();
    void register_branches(TTree *tree);
    void reset();
};