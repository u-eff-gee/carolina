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
             const vector<DetectorGroup> detector_groups,
             vector<shared_ptr<Detector>> detectors,
             const vector<CoincidenceMatrix> coincidence_matrices);

    vector<shared_ptr<Module>> modules;
    const vector<DetectorGroup> detector_groups;
    vector<shared_ptr<Detector>> detectors;
    const vector<CoincidenceMatrix> coincidence_matrices;

    void calibrate(const long long n_entry);
    double get_amplitude(const size_t n_detector, const size_t n_channel) const;
    long long get_counts(const size_t n_detector, const size_t n_channel) const;
    long long get_previous_counts(const size_t n_detector,
                                  const size_t n_channel) const;
    DetectorGroup get_group(const size_t n_detector) const;
    double get_tdc_resolution(const size_t n_detector,
                              const size_t n_channel) const;
    double get_time(const size_t n_detector, const size_t n_channel) const;
    double get_time_RF(const size_t n_detector, const size_t n_channel) const;
    double get_timestamp(const size_t n_detector, const size_t n_channel) const;

    void activate_and_register_branches(TTree *tree);
    void activate_branches(TTree *tree);
    void activate_calibrated_branches(TTree *tree);
    void calibrate(const int n_entry);
    void create_branches(TTree *tree);
    void register_branches(TTree *tree);
    void register_calibrated_branches(TTree *tree);
    void reset();
};