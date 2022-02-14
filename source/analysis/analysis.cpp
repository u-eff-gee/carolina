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

#include <cmath>

using std::isnan;

#include <memory>

using std::dynamic_pointer_cast;

#include "analysis.hpp"
#include "counter_detector_channel.hpp"
#include "energy_sensitive_detector_channel.hpp"
#include "vme.hpp"

Analysis::Analysis(vector<shared_ptr<Module>> modules,
                   const vector<shared_ptr<DetectorGroup>> detector_groups,
                   vector<shared_ptr<Detector>> detectors,
                   const vector<CoincidenceMatrix> coincidence_matrices)
    : modules(modules), detector_groups(detector_groups), detectors(detectors),
      coincidence_matrices(coincidence_matrices) {
    for (auto detector : detectors) {
        if (dynamic_pointer_cast<EnergySensitiveDetector>(detector)) {
            energy_sensitive_detectors.push_back(
                dynamic_pointer_cast<EnergySensitiveDetector>(detector));
        }
        if (dynamic_pointer_cast<CounterDetector>(detector)) {
            counter_detectors.push_back(
                dynamic_pointer_cast<CounterDetector>(detector));
        }
    }
    for (auto module : modules) {
        if (dynamic_pointer_cast<DigitizerModule>(module)) {
            digitizer_modules.push_back(
                dynamic_pointer_cast<DigitizerModule>(module));
        }
        if (dynamic_pointer_cast<ScalerModule>(module)) {
            scaler_modules.push_back(
                dynamic_pointer_cast<ScalerModule>(module));
        }
    }
}

void Analysis::set_up_raw_branches_for_reading(TTree *tree) {
    tree->SetBranchStatus("*", 0);
    for (size_t i = 0; i < modules.size(); ++i) {
        modules[i]->set_up_raw_branches_for_reading(tree);
    }
}

void Analysis::set_up_raw_branches_for_writing(TTree *tree) {
    for (size_t i = 0; i < modules.size(); ++i) {
        modules[i]->set_up_raw_branches_for_writing(tree);
    }
}

void Analysis::set_up_calibrated_branches_for_reading(TTree *tree) {
    for (size_t n_detector = 0; n_detector < detectors.size(); ++n_detector) {
        detectors[n_detector]->set_up_calibrated_branches_for_reading(tree);
    }
}

void Analysis::set_up_calibrated_branches_for_writing(TTree *tree) {
    for (size_t n_detector = 0; n_detector < detectors.size(); ++n_detector) {
        detectors[n_detector]->set_up_calibrated_branches_for_writing(tree);
    }
}

double Analysis::get_amplitude(const size_t n_detector,
                               const size_t n_channel) const {
    return digitizer_modules[detectors[n_detector]->channels[n_channel]->module]
        ->get_amplitude(detectors[n_detector]->channels[n_channel]->channel);
}

long long Analysis::get_counts(const size_t n_detector,
                               const size_t n_channel) const {
    return scaler_modules[detectors[n_detector]->channels[n_channel]->module]
        ->get_counts(detectors[n_detector]->channels[n_channel]->channel);
}

shared_ptr<DetectorGroup> Analysis::get_group(const size_t n_detector) const {
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

double Analysis::get_reference_time(const size_t n_detector,
                                    const size_t n_channel) const {
    return dynamic_pointer_cast<DigitizerModule>(
               modules[detectors[n_detector]->channels[n_channel]->module])
        ->get_reference_time();
}

double Analysis::get_timestamp(const size_t n_detector,
                               const size_t n_channel) const {
    return dynamic_pointer_cast<DigitizerModule>(
               modules[detectors[n_detector]->channels[n_channel]->module])
        ->get_timestamp();
}

void Analysis::calibrate(const long long n_entry) {
    for (size_t n_detector = 0; n_detector < detectors.size(); ++n_detector) {
        for (size_t n_channel = 0;
             n_channel < detectors[n_detector]->channels.size(); ++n_channel) {
            if (dynamic_pointer_cast<EnergySensitiveDetector>(
                    detectors[n_detector])) {
                calibrate_energy_sensitive_detector(n_entry, n_detector,
                                                    n_channel);
            } else {
                calibrate_counter_detector(n_entry, n_detector, n_channel);
            }
        }
        if (dynamic_pointer_cast<EnergySensitiveDetector>(
                detectors[n_detector]) &&
            detectors[n_detector]->channels.size() > 1) {
            dynamic_pointer_cast<EnergySensitiveDetector>(detectors[n_detector])
                ->addback();
        }
    }
}

void Analysis::calibrate_counter_detector(const int n_entry,
                                          const size_t n_detector,
                                          const size_t n_channel) {
    if (n_entry > 1 && !isnan(get_counts(n_detector, n_channel)) &&
        get_counts(n_detector, n_channel) > 0 &&
        get_counts(n_detector, n_channel) !=
            dynamic_pointer_cast<CounterDetectorChannel>(
                detectors[n_detector]->channels[n_channel])
                ->previous_counts) {
        dynamic_pointer_cast<CounterDetectorChannel>(
            detectors[n_detector]->channels[n_channel])
            ->count_rate =
            (get_counts(n_detector, n_channel) -
             dynamic_pointer_cast<CounterDetectorChannel>(
                 detectors[n_detector]->channels[n_channel])
                 ->previous_counts) *
            dynamic_pointer_cast<ScalerModule>(
                modules[detectors[n_detector]->channels[n_channel]->module])
                ->trigger_frequency;
        dynamic_pointer_cast<CounterDetectorChannel>(
            detectors[n_detector]->channels[n_channel])
            ->previous_counts = get_counts(n_detector, n_channel);
    } else {
        dynamic_pointer_cast<CounterDetectorChannel>(
            detectors[n_detector]->channels[n_channel])
            ->reset_calibrated_leaves();
    }
}

void Analysis::calibrate_energy_sensitive_detector(const int n_entry,
                                                   const size_t n_detector,
                                                   const size_t n_channel) {
    bool reset = false;
    if (!isnan(get_amplitude(n_detector, n_channel))) {
        dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
            detectors[n_detector]->channels[n_channel])
            ->time_calibrated =
            dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                detectors[n_detector]->channels[n_channel])
                ->time_calibration(
                    dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                        detectors[n_detector]->channels[n_channel])
                        ->energy_calibrated) *
            get_time(n_detector, n_channel) *
            get_tdc_resolution(n_detector, n_channel);
        dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
            detectors[n_detector]->channels[n_channel])
            ->time_vs_reference_time_calibrated =
            dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                detectors[n_detector]->channels[n_channel])
                ->time_calibrated -
            get_reference_time(n_detector, n_channel) *
                get_tdc_resolution(n_detector, n_channel);
        if (dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                detectors[n_detector]->channels[n_channel])
                ->apply_RF_gate()) {
            dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                detectors[n_detector]->channels[n_channel])
                ->energy_calibrated =
                dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                    detectors[n_detector]->channels[n_channel])
                    ->energy_calibration(get_amplitude(n_detector, n_channel),
                                         n_entry);
        } else {
            reset = true;
        }
        dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
            detectors[n_detector]->channels[n_channel])
            ->timestamp_calibrated =
            get_timestamp(n_detector, n_channel) * INVERSE_VME_CLOCK_FREQUENCY;
    } else {
        reset = true;
    }

    if (reset) {
        dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
            detectors[n_detector]->channels[n_channel])
            ->reset_calibrated_leaves();
    }
}

void Analysis::reset_calibrated_leaves() {
    for (size_t n_detector = 0; n_detector < detectors.size(); ++n_detector) {
        detectors[n_detector]->reset_calibrated_leaves();
    }
}

void Analysis::reset_raw_leaves() {
    for (auto module : modules) {
        module->reset_raw_leaves();
    }
}

void Analysis::add_counts(const size_t n_detector, const size_t n_channel,
                          const long long counts) {
    dynamic_pointer_cast<ScalerModule>(
        modules[detectors[n_detector]->channels[n_channel]->module])
        ->add_counts(detectors[n_detector]->channels[n_channel]->channel,
                     counts);
}

void Analysis::set_amplitude(const size_t n_detector, const size_t n_channel,
                             const double amplitude) {
    dynamic_pointer_cast<DigitizerModule>(
        modules[detectors[n_detector]->channels[n_channel]->module])
        ->set_amplitude(detectors[n_detector]->channels[n_channel]->channel,
                        amplitude);
}

void Analysis::set_reference_time(const size_t n_module,
                                  const double reference_time) {
    dynamic_pointer_cast<DigitizerModule>(modules[n_module])
        ->set_reference_time(reference_time);
}

void Analysis::set_time(const size_t n_detector, const size_t n_channel,
                        const double time) {
    dynamic_pointer_cast<DigitizerModule>(
        modules[detectors[n_detector]->channels[n_channel]->module])
        ->set_time(detectors[n_detector]->channels[n_channel]->channel, time);
}

void Analysis::set_timestamp(const size_t n_module, const double timestamp) {
    dynamic_pointer_cast<DigitizerModule>(modules[n_module])
        ->set_timestamp(timestamp);
}