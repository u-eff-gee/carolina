#include "analysis.hpp"

Analysis::Analysis(vector<shared_ptr<DigitizerModule>> digitizer_modules,
                   vector<shared_ptr<ScalerModule>> scaler_modules,
                   const vector<DetectorGroup> detector_groups,
                   vector<Detector> detectors,
                   const vector<CoincidenceMatrix> coincidence_matrices)
    : digitizer_modules(digitizer_modules), scaler_modules(scaler_modules),
      detector_groups(detector_groups), detectors(detectors),
      coincidence_matrices(coincidence_matrices) {}

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

double Analysis::get_amplitude(const size_t n_detector,
                               const size_t n_channel) const {
    return digitizer_modules[detectors[n_detector].channels[n_channel].module]
        ->get_amplitude(detectors[n_detector].channels[n_channel].leaf);
}

DetectorGroup Analysis::get_group(const size_t n_detector) const {
    return detector_groups[n_detector];
}

double Analysis::get_tdc_resolution(const size_t n_detector,
                                    const size_t n_channel) const {
    return digitizer_modules[detectors[n_detector].channels[n_channel].module]
        ->tdc_resolution;
}

double Analysis::get_time(const size_t n_detector,
                          const size_t n_channel) const {
    return digitizer_modules[detectors[n_detector].channels[n_channel].module]
        ->get_time(detectors[n_detector].channels[n_channel].leaf);
}

double Analysis::get_time_RF(const size_t n_detector,
                             const size_t n_channel) const {
    return digitizer_modules[detectors[n_detector].channels[n_channel].module]
        ->get_time_RF(detectors[n_detector].channels[n_channel].leaf);
}

double Analysis::get_timestamp(const size_t n_detector,
                               const size_t n_channel) const {
    return digitizer_modules[detectors[n_detector].channels[n_channel].module]
        ->get_timestamp(detectors[n_detector].channels[n_channel].leaf);
}

void Analysis::calibrate(const size_t n_detector, const size_t n_channel,
                         const long long n_entry) {
    detectors[n_detector].channels[n_channel].energy_calibrated = 0.;
    if (!isnan(get_amplitude(n_detector, n_channel))) {
        detectors[n_detector].channels[n_channel].energy_calibrated =
            detectors[n_detector].channels[n_channel].energy_calibration(
                n_entry, get_amplitude(n_detector, n_channel));
        detectors[n_detector].channels[n_channel].time_calibrated =
            detectors[n_detector].channels[n_channel].time_calibration(
                detectors[n_detector].channels[n_channel].energy_calibrated) *
            get_time(n_detector, n_channel) *
            get_tdc_resolution(n_detector, n_channel);
        detectors[n_detector].channels[n_channel].time_vs_time_RF_calibrated =
            detectors[n_detector].channels[n_channel].time_calibrated -
            get_time_RF(n_detector, n_channel) *
                get_tdc_resolution(n_detector, n_channel);
        detectors[n_detector].channels[n_channel].timestamp_calibrated =
            get_timestamp(n_detector, n_channel) * INVERSE_VME_CLOCK_FREQUENCY;
    } else {
        detectors[n_detector].channels[n_channel].energy_calibrated =
            numeric_limits<double>::quiet_NaN();
        detectors[n_detector].channels[n_channel].time_calibrated =
            numeric_limits<double>::quiet_NaN();
        detectors[n_detector].channels[n_channel].time_vs_time_RF_calibrated =
            numeric_limits<double>::quiet_NaN();
        detectors[n_detector].channels[n_channel].timestamp_calibrated =
            numeric_limits<double>::quiet_NaN();
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