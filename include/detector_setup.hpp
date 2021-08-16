#include <vector>

using std::vector;

#include "detector.hpp"
#include "detector_group.hpp"
#include "module.hpp"

struct DetectorSetup {
    DetectorSetup(vector<shared_ptr<Module>> modules,
                  vector<DetectorGroup> detector_groups,
                  vector<Detector> detectors)
        : modules(modules), detector_groups(detector_groups),
          detectors(detectors) {}

    vector<shared_ptr<Module>> modules;
    const vector<DetectorGroup> detector_groups;
    const vector<Detector> detectors;

    vector<string> get_branch_names();
};