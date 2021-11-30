#include "detector_setup.hpp"

void DetectorSetup::calibrate(const int n_entry) {
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

void DetectorSetup::activate_branches(TTree *tree) {
    for (size_t n_detector = 0; n_detector < detectors.size(); ++n_detector) {
        detectors[n_detector].activate_branches(tree);
    }
}

void DetectorSetup::create_branches(TTree *tree) {
    for (size_t n_detector = 0; n_detector < detectors.size(); ++n_detector) {
        detectors[n_detector].create_branches(tree);
    }
}

void DetectorSetup::register_branches(TTree *tree) {
    for (size_t n_detector = 0; n_detector < detectors.size(); ++n_detector) {
        detectors[n_detector].register_branches(tree);
    }
}

void DetectorSetup::reset() {
    for (size_t n_detector = 0; n_detector < detectors.size(); ++n_detector) {
        detectors[n_detector].reset();
    }
}