#include <cmath>

using std::isnan;

#include <memory>

using std::dynamic_pointer_cast;

#include "analysis.hpp"
#include "energy_sensitive_detector_channel.hpp"

Analysis::Analysis(vector<shared_ptr<Module>> modules,
                   const vector<DetectorGroup> detector_groups,
                   vector<shared_ptr<Detector>> detectors,
                   const vector<CoincidenceMatrix> coincidence_matrices)
    : modules(modules), detector_groups(detector_groups), detectors(detectors),
      coincidence_matrices(coincidence_matrices) {}

void Analysis::activate_and_register_branches(TTree *tree) {
    activate_branches(tree);
    register_branches(tree);
}

void Analysis::activate_branches(TTree *tree) {
    tree->SetBranchStatus("*", 0);
    for (size_t i = 0; i < modules.size(); ++i) {
        modules[i]->activate_branches(tree);
    }
}

void Analysis::activate_calibrated_branches(TTree *tree) {
    for (size_t n_detector = 0; n_detector < detectors.size(); ++n_detector) {
        detectors[n_detector]->activate_branches(tree);
    }
}

void Analysis::create_branches(TTree *tree) {
    for (size_t n_detector = 0; n_detector < detectors.size(); ++n_detector) {
        detectors[n_detector]->create_branches(tree);
    }
}

double Analysis::get_amplitude(const size_t n_detector,
                               const size_t n_channel) const {
    return dynamic_pointer_cast<DigitizerModule>(
               modules[detectors[n_detector]->channels[n_channel]->module])
        ->get_amplitude(detectors[n_detector]->channels[n_channel]->channel);
}

long long Analysis::get_counts(const size_t n_detector,
                               const size_t n_channel) const {
    return dynamic_pointer_cast<ScalerModule>(
               modules[detectors[n_detector]->channels[n_channel]->module])
        ->get_counts(detectors[n_detector]->channels[n_channel]->channel);
}

DetectorGroup Analysis::get_group(const size_t n_detector) const {
    return detector_groups[n_detector];
}

double Analysis::get_tdc_resolution(const size_t n_detector,
                                    const size_t n_channel) const {
    return dynamic_pointer_cast<DigitizerModule>(
               modules[detectors[n_detector]->channels[n_channel]->module])
        ->tdc_resolution;
}

double Analysis::get_time(const size_t n_detector,
                          const size_t n_channel) const {
    return dynamic_pointer_cast<DigitizerModule>(
               modules[detectors[n_detector]->channels[n_channel]->module])
        ->get_time(dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                       detectors[n_detector]->channels[n_channel])
                       ->channel);
}

double Analysis::get_time_RF(const size_t n_detector,
                             const size_t n_channel) const {
    return dynamic_pointer_cast<DigitizerModule>(
               modules[detectors[n_detector]->channels[n_channel]->module])
        ->get_time_RF(dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                          detectors[n_detector]->channels[n_channel])
                          ->channel);
}

double Analysis::get_timestamp(const size_t n_detector,
                               const size_t n_channel) const {
    return dynamic_pointer_cast<DigitizerModule>(
               modules[detectors[n_detector]->channels[n_channel]->module])
        ->get_timestamp(dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                            detectors[n_detector]->channels[n_channel])
                            ->channel);
}

void Analysis::calibrate(const size_t n_detector, const size_t n_channel,
                         const long long n_entry) {
    dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
        detectors[n_detector]->channels[n_channel])
        ->energy_calibrated = 0.;
    if (!isnan(get_amplitude(n_detector, n_channel))) {
        dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
            detectors[n_detector]->channels[n_channel])
            ->energy_calibrated =
            dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                detectors[n_detector]->channels[n_channel])
                ->energy_calibration(n_entry,
                                     get_amplitude(n_detector, n_channel));
        dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
            detectors[n_detector]->channels[n_channel])
            ->time_calibrated =
            dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                detectors[n_detector]->channels[n_channel])
                ->time_calibration(
                    get_time(n_detector, n_channel),
                    dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                        detectors[n_detector]->channels[n_channel])
                        ->energy_calibrated) *
            get_tdc_resolution(n_detector, n_channel);
        dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
            detectors[n_detector]->channels[n_channel])
            ->time_vs_time_RF_calibrated =
            dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                detectors[n_detector]->channels[n_channel])
                ->time_calibrated -
            get_time_RF(n_detector, n_channel) *
                get_tdc_resolution(n_detector, n_channel);
        dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
            detectors[n_detector]->channels[n_channel])
            ->timestamp_calibrated =
            get_timestamp(n_detector, n_channel) * INVERSE_VME_CLOCK_FREQUENCY;
    } else {
        dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
            detectors[n_detector]->channels[n_channel])
            ->energy_calibrated = numeric_limits<double>::quiet_NaN();
        dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
            detectors[n_detector]->channels[n_channel])
            ->time_calibrated = numeric_limits<double>::quiet_NaN();
        dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
            detectors[n_detector]->channels[n_channel])
            ->time_vs_time_RF_calibrated = numeric_limits<double>::quiet_NaN();
        dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
            detectors[n_detector]->channels[n_channel])
            ->timestamp_calibrated = numeric_limits<double>::quiet_NaN();
    }
}

void Analysis::register_branches(TTree *tree) {

    for (size_t i = 0; i < modules.size(); ++i) {
        modules[i]->register_branches(tree);
    }
}

void Analysis::register_calibrated_branches(TTree *tree) {
    for (size_t n_detector = 0; n_detector < detectors.size(); ++n_detector) {
        detectors[n_detector]->register_branches(tree);
    }
}

void Analysis::reset() {
    for (size_t n_detector = 0; n_detector < detectors.size(); ++n_detector) {
        detectors[n_detector]->reset();
    }
}