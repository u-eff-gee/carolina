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
#include "counter_detector.hpp"
#include "detector.hpp"
#include "detector_group.hpp"
#include "digitizer_module.hpp"
#include "energy_sensitive_detector.hpp"
#include "scaler_module.hpp"

struct Analysis {
    Analysis(vector<shared_ptr<Module>> modules,
             const vector<shared_ptr<DetectorGroup>> detector_groups,
             vector<shared_ptr<Detector>> detectors,
             const vector<CoincidenceMatrix> coincidence_matrices);

    vector<shared_ptr<Module>> modules;
    vector<shared_ptr<DigitizerModule>> digitizer_modules;
    const vector<shared_ptr<DetectorGroup>> detector_groups;
    vector<shared_ptr<Detector>> detectors;
    vector<shared_ptr<CounterDetector>> counter_detectors;
    vector<shared_ptr<EnergySensitiveDetector>> energy_sensitive_detectors;
    const vector<CoincidenceMatrix> coincidence_matrices;
    vector<shared_ptr<ScalerModule>> scaler_modules;
    vector<size_t> module_index;

    void calibrate(const long long n_entry);
    double get_amplitude(const size_t n_detector, const size_t n_channel) const;
    long long get_counts(const size_t n_detector, const size_t n_channel) const;
    size_t get_n_energy_sensitive_detector_channels() const;
    double get_time(const size_t n_detector, const size_t n_channel) const;
    double get_reference_time(const size_t n_detector,
                              const size_t n_channel) const;
    double get_timestamp(const size_t n_detector, const size_t n_channel) const;

    void add_counts(const size_t n_detector, const size_t n_channel,
                    const long long counts);
    void set_amplitude(const size_t n_detector, const size_t n_channel,
                       const double amplitude);
    void set_reference_time(const size_t n_module,
                            const double time_vs_reference_time);
    void set_time(const size_t n_detector, const size_t n_channel,
                  const double time);
    void set_timestamp(const size_t n_module, const double timestamp);

    void calibrate(const int n_entry);
    void calibrate_counter_detector(const int n_entry, const size_t n_detector,
                                    const size_t n_channel);
    void calibrate_energy_sensitive_detector(const int n_entry,
                                             const size_t n_detector,
                                             const size_t n_channel);
    void reset_calibrated_leaves();
    void reset_raw_energy_sensitive_detector_leaves(
        const vector<bool> amp_t_tref_ts = {false, false, false, false});
    void set_up_calibrated_energy_sensitive_detector_branches_for_reading(
        TTree *tree);
    void set_up_calibrated_energy_sensitive_detector_branches_for_writing(
        TTree *tree);
    void set_up_raw_energy_sensitive_detector_branches_for_reading(
        TTree *tree,
        const vector<bool> amp_t_tref_ts = {false, false, false, false});
    void set_up_raw_energy_sensitive_detector_branches_for_writing(
        TTree *tree,
        const vector<bool> amp_t_tref_ts = {false, false, false, false});

    void reset_raw_counter_detector_leaves(const vector<bool> amp_t_tref_ts = {
                                               false, false, false, false});
    void set_up_calibrated_counter_detector_branches_for_reading(TTree *tree);
    void set_up_calibrated_counter_detector_branches_for_writing(TTree *tree);
    void set_up_raw_counter_detector_branches_for_reading(
        TTree *tree,
        const vector<bool> amp_t_tref_ts = {false, false, false, false});
    void set_up_raw_counter_detector_branches_for_writing(
        TTree *tree,
        const vector<bool> amp_t_tref_ts = {false, false, false, false});
};