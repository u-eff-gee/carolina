#pragma once

#include <vector>

using std::vector;

#include "coincidence_matrix.hpp"
#include "detector.hpp"
#include "detector_group.hpp"
#include "digitizer_module.hpp"
#include "scaler_module.hpp"

struct Analysis {
    Analysis(vector<shared_ptr<DigitizerModule>> digitizer_modules,
             vector<shared_ptr<ScalerModule>> scaler_modules,
             const vector<DetectorGroup> detector_groups,
             vector<Detector> detectors,
             const vector<CoincidenceMatrix> coincidence_matrices);

    vector<shared_ptr<DigitizerModule>> digitizer_modules;
    vector<shared_ptr<ScalerModule>> scaler_modules;
    const vector<DetectorGroup> detector_groups;
    vector<Detector> detectors;
    const vector<CoincidenceMatrix> coincidence_matrices;

    void activate_branches(TTree *tree);
    void activate_calibrated_branches(TTree *tree);
    void calibrate(const int n_entry);
    void create_branches(TTree *tree);
    void register_branches(TTree *tree);
    void register_calibrated_branches(TTree *tree);
    void reset();
};