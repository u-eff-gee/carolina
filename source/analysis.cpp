#include "analysis.hpp"

Analysis::Analysis(vector<shared_ptr<DigitizerModule>> digitizer_modules,
                   vector<shared_ptr<ScalerModule>> scaler_modules,
                   const vector<DetectorGroup> detector_groups,
                   vector<Detector> detectors,
                   const vector<CoincidenceMatrix> coincidence_matrices)
    : digitizer_modules(digitizer_modules), scaler_modules(scaler_modules),
      detector_groups(detector_groups), detectors(detectors),
      coincidence_matrices(coincidence_matrices) {}

void Analysis::calibrate(const int n_entry) {
    for (size_t n_detector = 0; n_detector < detectors.size(); ++n_detector) {
        for (size_t n_channel = 0;
             n_channel < detectors[n_detector].channels.size(); ++n_channel) {
            if (detectors[n_detector].channels[n_channel].get_amplitude() >
                detectors[n_detector].channels[n_channel].amplitude_threshold)
                detectors[n_detector].channels[n_channel].calibrate(n_entry);
        }
        detectors[n_detector].addback();
    }
}

void Analysis::activate_branches(TTree *tree) {
    for (size_t i = 0; i < digitizer_modules.size(); ++i) {
        digitizer_modules[i]->activate_branches(tree);
    }
    for (size_t i = 0; i < scaler_modules.size(); ++i) {
        scaler_modules[i]->activate_branches(tree);
    }
}

void Analysis::activate_calibrated_branches(TTree *tree) {
    for (size_t n_detector = 0; n_detector < detectors.size(); ++n_detector) {
        detectors[n_detector].activate_branches(tree);
    }
}

void Analysis::create_branches(TTree *tree) {
    for (size_t n_detector = 0; n_detector < detectors.size(); ++n_detector) {
        detectors[n_detector].create_branches(tree);
    }
}

void Analysis::register_branches(TTree *tree) {

    for (size_t i = 0; i < digitizer_modules.size(); ++i) {
        digitizer_modules[i]->register_branches(tree);
    }
    for (size_t i = 0; i < scaler_modules.size(); ++i) {
        scaler_modules[i]->register_branches(tree);
    }
}

void Analysis::register_calibrated_branches(TTree *tree) {
    for (size_t n_detector = 0; n_detector < detectors.size(); ++n_detector) {
        detectors[n_detector].register_branches(tree);
    }
}

void Analysis::reset() {
    for (size_t n_detector = 0; n_detector < detectors.size(); ++n_detector) {
        detectors[n_detector].reset();
    }
}