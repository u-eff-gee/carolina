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

#include <algorithm>

using std::max;
using std::min;

#include <cmath>

using std::isnan;

#include <memory>

using std::dynamic_pointer_cast;

#include <iostream>

using std::cout;
using std::endl;

#include "TChain.h"
#include "TFile.h"
#include "TH1D.h"

#include "command_line_parser.hpp"
#include "histograms_1d.hpp"
#include "progress_printer.hpp"
#include "tfile_utilities.hpp"

int main(int argc, char **argv) {
    CommandLineParser command_line_parser;
    command_line_parser.desc.add_options()(
        "calibrate", "Assume that the input file contains raw data that need "
                     "to be calibrated by 'histograms_1d'."
                     "The default assumption is that the input file is "
                     "output of the 'calibrate_tree' script.");
    int command_line_parser_status;
    command_line_parser(argc, argv, command_line_parser_status);
    if (command_line_parser_status) {
        return 0;
    }
    po::variables_map vm = command_line_parser.get_variables_map();

    long long first, last;
    TChain *tree =
        command_line_parser.set_up_tree(first, last, vm.count("list"));

    ProgressPrinter progress_printer(first, last);

    tree->SetBranchStatus("*", 0);
    if (vm.count("calibrate")) {
        analysis.set_up_raw_counter_detector_branches_for_reading(tree, {true});
        analysis.set_up_raw_energy_sensitive_detector_branches_for_reading(
            tree, {true, true, true, true});
    } else {
        analysis.set_up_calibrated_counter_detector_branches_for_reading(tree);
        analysis
            .set_up_calibrated_energy_sensitive_detector_branches_for_reading(
                tree);
    }

    vector<TH1D *> addback_histograms;
    vector<vector<TH1D *>> energy_sensitive_detector_histograms;
    vector<vector<TH1D *>> counter_detector_histograms;
    vector<vector<TH1D *>> time_vs_reference_time_histograms;
    vector<vector<vector<vector<TH1D *>>>> time_difference_histograms;
    vector<TDirectory *> time_difference_directories;
    string histogram_name;

    for (size_t n_detector_1 = 0;
         n_detector_1 < analysis.energy_sensitive_detectors.size();
         ++n_detector_1) {
        if (analysis.energy_sensitive_detectors[n_detector_1]->channels.size() >
            1) {
            histogram_name =
                analysis.energy_sensitive_detectors[n_detector_1]->name +
                "_addback";
            addback_histograms.push_back(new TH1D(
                histogram_name.c_str(), histogram_name.c_str(),
                analysis.energy_sensitive_detectors[n_detector_1]
                    ->group->histogram_properties.n_bins,
                analysis.energy_sensitive_detectors[n_detector_1]
                    ->group->histogram_properties.lower_edge_of_first_bin,
                analysis.energy_sensitive_detectors[n_detector_1]
                    ->group->histogram_properties.upper_edge_of_last_bin));
        } else {
            addback_histograms.push_back(nullptr);
        }
        energy_sensitive_detector_histograms.push_back(vector<TH1D *>());
        time_difference_histograms.push_back(vector<vector<vector<TH1D *>>>());
        time_vs_reference_time_histograms.push_back(vector<TH1D *>());
        for (size_t n_channel_1 = 0;
             n_channel_1 <
             analysis.energy_sensitive_detectors[n_detector_1]->channels.size();
             ++n_channel_1) {
            time_difference_histograms[n_detector_1].push_back(
                vector<vector<TH1D *>>());
            histogram_name =
                analysis.energy_sensitive_detectors[n_detector_1]->name + "_" +
                analysis.energy_sensitive_detectors[n_detector_1]
                    ->channels[n_channel_1]
                    .name;
            energy_sensitive_detector_histograms[n_detector_1].push_back(
                new TH1D(
                    histogram_name.c_str(), histogram_name.c_str(),
                    analysis.energy_sensitive_detectors[n_detector_1]
                        ->group->histogram_properties.n_bins,
                    analysis.energy_sensitive_detectors[n_detector_1]
                        ->group->histogram_properties.lower_edge_of_first_bin,
                    analysis.energy_sensitive_detectors[n_detector_1]
                        ->group->histogram_properties.upper_edge_of_last_bin));
            histogram_name =
                analysis.energy_sensitive_detectors[n_detector_1]->name + "_" +
                analysis.energy_sensitive_detectors[n_detector_1]
                    ->channels[n_channel_1]
                    .name +
                "_t_vs_RF";
            time_vs_reference_time_histograms[n_detector_1].push_back(new TH1D(
                histogram_name.c_str(), histogram_name.c_str(),
                dynamic_pointer_cast<EnergySensitiveDetectorGroup>(
                    analysis.energy_sensitive_detectors[n_detector_1]->group)
                    ->time_histogram_properties.n_bins,
                dynamic_pointer_cast<EnergySensitiveDetectorGroup>(
                    analysis.energy_sensitive_detectors[n_detector_1]->group)
                    ->time_histogram_properties.lower_edge_of_first_bin,
                dynamic_pointer_cast<EnergySensitiveDetectorGroup>(
                    analysis.energy_sensitive_detectors[n_detector_1]->group)
                    ->time_histogram_properties.upper_edge_of_last_bin));

            time_difference_histograms[n_detector_1][n_channel_1].push_back(
                vector<TH1D *>());
            for (size_t n_channel_2 = n_channel_1 + 1;
                 n_channel_2 <
                 analysis.energy_sensitive_detectors[n_detector_1]
                     ->channels.size();
                 ++n_channel_2) {
                histogram_name =
                    analysis.energy_sensitive_detectors[n_detector_1]->name +
                    "_" +
                    analysis.energy_sensitive_detectors[n_detector_1]
                        ->channels[n_channel_1]
                        .name +
                    "_" +
                    analysis.energy_sensitive_detectors[n_detector_1]->name +
                    "_" +
                    analysis.energy_sensitive_detectors[n_detector_1]
                        ->channels[n_channel_2]
                        .name +
                    "_tdiff";
                time_difference_histograms[n_detector_1][n_channel_1][0]
                    .push_back(new TH1D(
                        histogram_name.c_str(), histogram_name.c_str(),
                        dynamic_pointer_cast<EnergySensitiveDetectorGroup>(
                            analysis.energy_sensitive_detectors[n_detector_1]
                                ->group)
                            ->time_histogram_properties.n_bins,
                        dynamic_pointer_cast<EnergySensitiveDetectorGroup>(
                            analysis.energy_sensitive_detectors[n_detector_1]
                                ->group)
                            ->time_histogram_properties.lower_edge_of_first_bin,
                        dynamic_pointer_cast<EnergySensitiveDetectorGroup>(
                            analysis.energy_sensitive_detectors[n_detector_1]
                                ->group)
                            ->time_histogram_properties
                            .upper_edge_of_last_bin));
            }

            for (size_t n_detector_2 = n_detector_1 + 1;
                 n_detector_2 < analysis.energy_sensitive_detectors.size();
                 ++n_detector_2) {
                time_difference_histograms[n_detector_1][n_channel_1].push_back(
                    vector<TH1D *>());
                for (size_t n_channel_2 = 0;
                     n_channel_2 <
                     analysis.energy_sensitive_detectors[n_detector_2]
                         ->channels.size();
                     ++n_channel_2) {
                    histogram_name =
                        analysis.energy_sensitive_detectors[n_detector_1]
                            ->name +
                        "_" +
                        analysis.energy_sensitive_detectors[n_detector_1]
                            ->channels[n_channel_1]
                            .name +
                        "_" +
                        analysis.energy_sensitive_detectors[n_detector_2]
                            ->name +
                        "_" +
                        analysis.energy_sensitive_detectors[n_detector_2]
                            ->channels[n_channel_2]
                            .name +
                        "_tdiff";
                    time_difference_histograms
                        [n_detector_1][n_channel_1][n_detector_2 - n_detector_1]
                            .push_back(new TH1D(
                                histogram_name.c_str(), histogram_name.c_str(),
                                max(dynamic_pointer_cast<
                                        EnergySensitiveDetectorGroup>(
                                        analysis
                                            .energy_sensitive_detectors
                                                [n_detector_1]
                                            ->group)
                                        ->time_histogram_properties.n_bins,
                                    dynamic_pointer_cast<
                                        EnergySensitiveDetectorGroup>(
                                        analysis
                                            .energy_sensitive_detectors
                                                [n_detector_2]
                                            ->group)
                                        ->time_histogram_properties.n_bins),
                                min(dynamic_pointer_cast<
                                        EnergySensitiveDetectorGroup>(
                                        analysis
                                            .energy_sensitive_detectors
                                                [n_detector_1]
                                            ->group)
                                        ->time_histogram_properties
                                        .lower_edge_of_first_bin,
                                    dynamic_pointer_cast<
                                        EnergySensitiveDetectorGroup>(
                                        analysis
                                            .energy_sensitive_detectors
                                                [n_detector_2]
                                            ->group)
                                        ->time_histogram_properties
                                        .lower_edge_of_first_bin),
                                max(dynamic_pointer_cast<
                                        EnergySensitiveDetectorGroup>(
                                        analysis
                                            .energy_sensitive_detectors
                                                [n_detector_1]
                                            ->group)
                                        ->time_histogram_properties
                                        .upper_edge_of_last_bin,
                                    dynamic_pointer_cast<
                                        EnergySensitiveDetectorGroup>(
                                        analysis
                                            .energy_sensitive_detectors
                                                [n_detector_2]
                                            ->group)
                                        ->time_histogram_properties
                                        .upper_edge_of_last_bin)));
                }
            }
        }
    }
    for (size_t n_detector = 0; n_detector < analysis.counter_detectors.size();
         ++n_detector) {
        counter_detector_histograms.push_back(vector<TH1D *>());
        for (auto channel : analysis.counter_detectors[n_detector]->channels) {
            histogram_name = analysis.counter_detectors[n_detector]->name +
                             "_" + channel.name;
            counter_detector_histograms[n_detector].push_back(
                new TH1D(histogram_name.c_str(), histogram_name.c_str(),
                         dynamic_pointer_cast<CounterDetectorGroup>(
                             analysis.counter_detectors[n_detector]->group)
                             ->histogram_properties.n_bins,
                         dynamic_pointer_cast<CounterDetectorGroup>(
                             analysis.counter_detectors[n_detector]->group)
                             ->histogram_properties.lower_edge_of_first_bin,
                         dynamic_pointer_cast<CounterDetectorGroup>(
                             analysis.counter_detectors[n_detector]->group)
                             ->histogram_properties.upper_edge_of_last_bin));
        }
    }

    for (long long i = first; i <= last; ++i) {
        tree->GetEntry(i);
        if (vm.count("calibrate")) {
            analysis.calibrate(i);
        }

        for (size_t n_detector_1 = 0;
             n_detector_1 < analysis.energy_sensitive_detectors.size();
             ++n_detector_1) {
            for (size_t n_channel_1 = 0;
                 n_channel_1 <
                 analysis.energy_sensitive_detectors[n_detector_1]
                     ->channels.size();
                 ++n_channel_1) {
                if (!isnan(analysis.energy_sensitive_detectors[n_detector_1]
                               ->channels[n_channel_1]
                               .energy_calibrated) &&
                    analysis.energy_sensitive_detectors[n_detector_1]
                        ->channels[n_channel_1]
                        .time_vs_reference_time_gate(
                            analysis.energy_sensitive_detectors[n_detector_1]
                                ->channels[n_channel_1]
                                .time_vs_reference_time_calibrated)) {
                    energy_sensitive_detector_histograms
                        [n_detector_1][n_channel_1]
                            ->Fill(analysis
                                       .energy_sensitive_detectors[n_detector_1]
                                       ->channels[n_channel_1]
                                       .energy_calibrated);
                    time_vs_reference_time_histograms[n_detector_1][n_channel_1]
                        ->Fill(
                            analysis.energy_sensitive_detectors[n_detector_1]
                                ->channels[n_channel_1]
                                .time_vs_reference_time_calibrated);

                    for (size_t n_channel_2 = n_channel_1 + 1;
                         n_channel_2 <
                         analysis.energy_sensitive_detectors[n_detector_1]
                             ->channels.size();
                         ++n_channel_2) {
                        if (!isnan(analysis
                                       .energy_sensitive_detectors[n_detector_1]
                                       ->channels[n_channel_2]
                                       .energy_calibrated) &&
                            analysis.energy_sensitive_detectors[n_detector_1]
                                ->channels[n_channel_2]
                                .time_vs_reference_time_gate(
                                    analysis
                                        .energy_sensitive_detectors
                                            [n_detector_1]
                                        ->channels[n_channel_2]
                                        .time_vs_reference_time_calibrated)) {
                            time_difference_histograms
                                [n_detector_1][n_channel_1][0]
                                [n_channel_2 - n_channel_1 - 1]
                                    ->Fill(analysis
                                               .energy_sensitive_detectors
                                                   [n_detector_1]
                                               ->channels[n_channel_1]
                                               .time_calibrated -
                                           analysis
                                               .energy_sensitive_detectors
                                                   [n_detector_1]
                                               ->channels[n_channel_2]
                                               .time_calibrated);
                        }
                    }

                    for (size_t n_detector_2 = n_detector_1 + 1;
                         n_detector_2 <
                         analysis.energy_sensitive_detectors.size();
                         ++n_detector_2) {
                        for (size_t n_channel_2 = 0;
                             n_channel_2 <
                             analysis.energy_sensitive_detectors[n_detector_2]
                                 ->channels.size();
                             ++n_channel_2) {
                            if (!isnan(analysis
                                           .energy_sensitive_detectors
                                               [n_detector_2]
                                           ->channels[n_channel_2]
                                           .energy_calibrated) &&
                                analysis
                                    .energy_sensitive_detectors[n_detector_2]
                                    ->channels[n_channel_2]
                                    .time_vs_reference_time_gate(
                                        analysis
                                            .energy_sensitive_detectors
                                                [n_detector_2]
                                            ->channels[n_channel_2]
                                            .time_vs_reference_time_calibrated)) {
                                time_difference_histograms
                                    [n_detector_1][n_channel_1]
                                    [n_detector_2 - n_detector_1][n_channel_2]
                                        ->Fill(analysis
                                                   .energy_sensitive_detectors
                                                       [n_detector_1]
                                                   ->channels[n_channel_1]
                                                   .time_calibrated -
                                               analysis
                                                   .energy_sensitive_detectors
                                                       [n_detector_2]
                                                   ->channels[n_channel_2]
                                                   .time_calibrated);
                            }
                        }
                    }
                }
            }
            if (analysis.energy_sensitive_detectors[n_detector_1]
                        ->channels.size() > 1 &&
                !isnan(analysis.energy_sensitive_detectors[n_detector_1]
                           ->addback_energy)) {
                addback_histograms[n_detector_1]->Fill(
                    analysis.energy_sensitive_detectors[n_detector_1]
                        ->addback_energy);
            }
        }
        for (size_t n_detector = 0;
             n_detector < analysis.counter_detectors.size(); ++n_detector) {
            for (size_t n_channel = 0;
                 n_channel <
                 analysis.counter_detectors[n_detector]->channels.size();
                 ++n_channel) {
                if (!isnan(analysis.counter_detectors[n_detector]
                               ->channels[n_channel]
                               .count_rate)) {
                    counter_detector_histograms[n_detector][n_channel]->Fill(
                        analysis.counter_detectors[n_detector]
                            ->channels[n_channel]
                            .count_rate);
                }
            }
        }
        if (vm.count("calibrate")) {
            analysis.reset_calibrated_leaves();
        }
        progress_printer(i);
    }

    TFile output_file(vm["output"].as<string>().c_str(), "RECREATE");
    TDirectory *directory = nullptr;

    for (size_t n_detector_1 = 0;
         n_detector_1 < analysis.energy_sensitive_detectors.size();
         ++n_detector_1) {
        directory = output_file.mkdir(
            (analysis.energy_sensitive_detectors[n_detector_1]->name + "_tdiff")
                .c_str());
        if (analysis.energy_sensitive_detectors[n_detector_1]->channels.size() >
            1) {
            addback_histograms[n_detector_1]->Write();
        }
        for (size_t n_channel_1 = 0;
             n_channel_1 <
             analysis.energy_sensitive_detectors[n_detector_1]->channels.size();
             ++n_channel_1) {
            energy_sensitive_detector_histograms[n_detector_1][n_channel_1]
                ->Write();
            directory->cd();
            time_vs_reference_time_histograms[n_detector_1][n_channel_1]
                ->Write();

            for (size_t n_channel_2 = n_channel_1 + 1;
                 n_channel_2 <
                 analysis.energy_sensitive_detectors[n_detector_1]
                     ->channels.size();
                 ++n_channel_2) {
                time_difference_histograms[n_detector_1][n_channel_1][0]
                                          [n_channel_2 - n_channel_1 - 1]
                                              ->Write();
            }
            for (size_t n_detector_2 = n_detector_1 + 1;
                 n_detector_2 < analysis.energy_sensitive_detectors.size();
                 ++n_detector_2) {
                for (size_t n_channel_2 = 0;
                     n_channel_2 <
                     analysis.energy_sensitive_detectors[n_detector_2]
                         ->channels.size();
                     ++n_channel_2) {
                    time_difference_histograms[n_detector_1][n_channel_1]
                                              [n_detector_2 - n_detector_1]
                                              [n_channel_2]
                                                  ->Write();
                }
            }
            output_file.cd();
        }
    }
    for (size_t n_detector = 0; n_detector < analysis.counter_detectors.size();
         ++n_detector) {
        for (size_t n_channel = 0;
             n_channel <
             analysis.counter_detectors[n_detector]->channels.size();
             ++n_channel) {
            counter_detector_histograms[n_detector][n_channel]->Write();
        }
    }

    output_file.Close();
    cout << "Created output file '" << vm["output"].as<string>() << "'."
         << endl;
}