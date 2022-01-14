/*
     This file is part of carolina.

    carolina is free software: you can redistribute it and/or modify it under
   the terms of the GNU General Public License as published by the Free Software
   Foundation, either version 3 of the License, or (at your option) any later
   version.

    carolina is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
    more details.

    You should have received a copy of the GNU General Public License along with
    carolina. If not, see <https://www.gnu.org/licenses/>.
*/

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
    void add_counts(const size_t n_detector, const size_t n_channel,
                    const long long counts);
    void set_time(const size_t n_detector, const size_t n_channel,
                  const double time);
    void set_time_RF(const size_t n_module, const double time_vs_time_RF);

    void calibrate(const int n_entry);
    void calibrate_counter_detector(const int n_entry, const size_t n_detector,
                                    const size_t n_channel);
    void calibrate_energy_sensitive_detector(const int n_entry,
                                             const size_t n_detector,
                                             const size_t n_channel);
    void reset_calibrated_leaves();
    void reset_raw_leaves();
    void set_up_calibrated_branches_for_reading(TTree *tree);
    void set_up_calibrated_branches_for_writing(TTree *tree);
    void set_up_raw_branches_for_reading(TTree *tree);
    void set_up_raw_branches_for_writing(TTree *tree);
};