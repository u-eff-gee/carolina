#pragma once

#include <vector>

using std::vector;

#include "coincidence_matrix.hpp"
#include "detector.hpp"
#include "detector_group.hpp"
#include "digitizer_module.hpp"
#include "scaler_module.hpp"

struct Analysis {
    Analysis(vector<shared_ptr<Module>> modules,
             const vector<shared_ptr<DetectorGroup>> detector_groups,
             vector<shared_ptr<Detector>> detectors,
             const vector<CoincidenceMatrix> coincidence_matrices);

    vector<shared_ptr<Module>> modules;
    const vector<shared_ptr<DetectorGroup>> detector_groups;
    vector<shared_ptr<Detector>> detectors;
    const vector<CoincidenceMatrix> coincidence_matrices;

    void calibrate(const long long n_entry);
    double get_amplitude(const size_t n_detector, const size_t n_channel) const;
    long long get_counts(const size_t n_detector, const size_t n_channel) const;
    shared_ptr<DetectorGroup> get_group(const size_t n_detector) const;
    double get_tdc_resolution(const size_t n_detector,
                              const size_t n_channel) const;
    double get_time(const size_t n_detector, const size_t n_channel) const;
    double get_time_RF(const size_t n_detector, const size_t n_channel) const;
    double get_timestamp(const size_t n_detector, const size_t n_channel) const;

    void set_amplitude(const size_t n_detector, const size_t n_channel,
                       const double amplitude);

    void calibrate(const int n_entry);
    void calibrate_counter_detector(const int n_entry, const size_t n_detector,
                                    const size_t n_channel);
    void calibrate_energy_sensitive_detector(const int n_entry,
                                             const size_t n_detector,
                                             const size_t n_channel);
    void reset_calibrated_leaves();
    void set_up_calibrated_branches_for_reading(TTree *tree);
    void set_up_calibrated_branches_for_writing(TTree *tree);
    void set_up_raw_branches_for_reading(TTree *tree);
    void set_up_raw_branches_for_writing(TTree *tree);
};