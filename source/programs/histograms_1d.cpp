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
        "log",
        "Indicates that the input file is a log file (probably created by the "
        "'calibrate_tree' program) that contains a list of ROOT files to read "
        "(default: assume the input file is a ROOT file).");
    int command_line_parser_status;
    command_line_parser(argc, argv, command_line_parser_status);
    if (command_line_parser_status) {
        return 0;
    }
    po::variables_map vm = command_line_parser.get_variables_map();

    long long first, last;
    TChain *tree =
        command_line_parser.set_up_tree(first, last, vm.count("log"));

    ProgressPrinter progress_printer(last - first + 1);

    analysis.set_up_calibrated_branches_for_reading(tree);

    vector<TH1D *> addback_histograms;
    vector<vector<TH1D *>> histograms;
    vector<vector<TH1D *>> time_vs_time_RF_histograms;
    vector<vector<vector<vector<TH1D *>>>> time_difference_histograms;
    vector<TDirectory *> time_difference_directories;
    string histogram_name;

    for (size_t n_detector_1 = 0; n_detector_1 < analysis.detectors.size();
         ++n_detector_1) {
        if (analysis.detectors[n_detector_1]->channels.size() > 1) {
            histogram_name =
                analysis.detectors[n_detector_1]->name + "_addback";
            addback_histograms.push_back(new TH1D(
                histogram_name.c_str(), histogram_name.c_str(),
                analysis.get_group(n_detector_1)->histogram_properties.n_bins,
                analysis.get_group(n_detector_1)->histogram_properties.minimum,
                analysis.get_group(n_detector_1)
                    ->histogram_properties.maximum));
        } else {
            addback_histograms.push_back(nullptr);
        }
        histograms.push_back(vector<TH1D *>());
        time_difference_histograms.push_back(vector<vector<vector<TH1D *>>>());
        time_vs_time_RF_histograms.push_back(vector<TH1D *>());
        for (size_t n_channel_1 = 0;
             n_channel_1 < analysis.detectors[n_detector_1]->channels.size();
             ++n_channel_1) {
            time_difference_histograms[n_detector_1].push_back(
                vector<vector<TH1D *>>());
            histogram_name =
                analysis.detectors[n_detector_1]->name + "_" +
                analysis.detectors[n_detector_1]->channels[n_channel_1]->name;
            histograms[n_detector_1].push_back(new TH1D(
                histogram_name.c_str(), histogram_name.c_str(),
                analysis.get_group(n_detector_1)->histogram_properties.n_bins,
                analysis.get_group(n_detector_1)->histogram_properties.minimum,
                analysis.get_group(n_detector_1)
                    ->histogram_properties.maximum));
            if (analysis.detectors[n_detector_1]->type == energy_sensitive) {
                histogram_name = analysis.detectors[n_detector_1]->name + "_" +
                                 analysis.detectors[n_detector_1]
                                     ->channels[n_channel_1]
                                     ->name +
                                 "_t_vs_RF";
                time_vs_time_RF_histograms[n_detector_1].push_back(
                    new TH1D(histogram_name.c_str(), histogram_name.c_str(),
                             dynamic_pointer_cast<EnergySensitiveDetectorGroup>(
                                 analysis.get_group(n_detector_1))
                                 ->time_histogram_properties.n_bins,
                             dynamic_pointer_cast<EnergySensitiveDetectorGroup>(
                                 analysis.get_group(n_detector_1))
                                 ->time_histogram_properties.minimum,
                             dynamic_pointer_cast<EnergySensitiveDetectorGroup>(
                                 analysis.get_group(n_detector_1))
                                 ->time_histogram_properties.maximum));

                time_difference_histograms[n_detector_1][n_channel_1].push_back(
                    vector<TH1D *>());
                for (size_t n_channel_2 = n_channel_1 + 1;
                     n_channel_2 <
                     analysis.detectors[n_detector_1]->channels.size();
                     ++n_channel_2) {
                    histogram_name =
                        analysis.detectors[n_detector_1]->name + "_" +
                        analysis.detectors[n_detector_1]
                            ->channels[n_channel_1]
                            ->name +
                        "_" + analysis.detectors[n_detector_1]->name + "_" +
                        analysis.detectors[n_detector_1]
                            ->channels[n_channel_2]
                            ->name +
                        "_tdiff";
                    time_difference_histograms[n_detector_1][n_channel_1][0]
                        .push_back(new TH1D(
                            histogram_name.c_str(), histogram_name.c_str(),
                            dynamic_pointer_cast<EnergySensitiveDetectorGroup>(
                                analysis.get_group(n_detector_1))
                                ->time_histogram_properties.n_bins,
                            dynamic_pointer_cast<EnergySensitiveDetectorGroup>(
                                analysis.get_group(n_detector_1))
                                ->time_histogram_properties.minimum,
                            dynamic_pointer_cast<EnergySensitiveDetectorGroup>(
                                analysis.get_group(n_detector_1))
                                ->time_histogram_properties.maximum));
                }

                for (size_t n_detector_2 = n_detector_1 + 1;
                     n_detector_2 < analysis.detectors.size(); ++n_detector_2) {
                    time_difference_histograms[n_detector_1][n_channel_1]
                        .push_back(vector<TH1D *>());
                    if (analysis.detectors[n_detector_2]->type ==
                        energy_sensitive) {
                        for (size_t n_channel_2 = 0;
                             n_channel_2 <
                             analysis.detectors[n_detector_2]->channels.size();
                             ++n_channel_2) {
                            histogram_name =
                                analysis.detectors[n_detector_1]->name + "_" +
                                analysis.detectors[n_detector_1]
                                    ->channels[n_channel_1]
                                    ->name +
                                "_" + analysis.detectors[n_detector_2]->name +
                                "_" +
                                analysis.detectors[n_detector_2]
                                    ->channels[n_channel_2]
                                    ->name +
                                "_tdiff";
                            time_difference_histograms
                                [n_detector_1][n_channel_1]
                                [n_detector_2 - n_detector_1]
                                    .push_back(new TH1D(
                                        histogram_name.c_str(),
                                        histogram_name.c_str(),
                                        max(dynamic_pointer_cast<
                                                EnergySensitiveDetectorGroup>(
                                                analysis.get_group(
                                                    n_detector_1))
                                                ->time_histogram_properties
                                                .n_bins,
                                            dynamic_pointer_cast<
                                                EnergySensitiveDetectorGroup>(
                                                analysis.get_group(
                                                    n_detector_2))
                                                ->time_histogram_properties
                                                .n_bins),
                                        min(dynamic_pointer_cast<
                                                EnergySensitiveDetectorGroup>(
                                                analysis.get_group(
                                                    n_detector_1))
                                                ->time_histogram_properties
                                                .minimum,
                                            dynamic_pointer_cast<
                                                EnergySensitiveDetectorGroup>(
                                                analysis.get_group(
                                                    n_detector_2))
                                                ->time_histogram_properties
                                                .minimum),
                                        max(dynamic_pointer_cast<
                                                EnergySensitiveDetectorGroup>(
                                                analysis.get_group(
                                                    n_detector_1))
                                                ->time_histogram_properties
                                                .maximum,
                                            dynamic_pointer_cast<
                                                EnergySensitiveDetectorGroup>(
                                                analysis.get_group(
                                                    n_detector_2))
                                                ->time_histogram_properties
                                                .maximum)));
                        }
                    }
                }
            }
        }
    }

    for (long long i = first; i < last; ++i) {
        progress_printer(i - first);

        tree->GetEntry(i);

        for (size_t n_detector_1 = 0; n_detector_1 < analysis.detectors.size();
             ++n_detector_1) {
            if (analysis.detectors[n_detector_1]->type == energy_sensitive) {
                for (size_t n_channel_1 = 0;
                     n_channel_1 <
                     analysis.detectors[n_detector_1]->channels.size();
                     ++n_channel_1) {
                    if (!isnan(dynamic_pointer_cast<
                                   EnergySensitiveDetectorChannel>(
                                   analysis.detectors[n_detector_1]
                                       ->channels[n_channel_1])
                                   ->energy_calibrated) &&
                        dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
                            analysis.detectors[n_detector_1]
                                ->channels[n_channel_1])
                            ->time_vs_time_RF_gate(
                                dynamic_pointer_cast<
                                    EnergySensitiveDetectorChannel>(
                                    analysis.detectors[n_detector_1]
                                        ->channels[n_channel_1])
                                    ->time_vs_time_RF_calibrated)) {
                        histograms[n_detector_1][n_channel_1]->Fill(
                            dynamic_pointer_cast<
                                EnergySensitiveDetectorChannel>(
                                analysis.detectors[n_detector_1]
                                    ->channels[n_channel_1])
                                ->energy_calibrated);
                        time_vs_time_RF_histograms[n_detector_1][n_channel_1]
                            ->Fill(dynamic_pointer_cast<
                                       EnergySensitiveDetectorChannel>(
                                       analysis.detectors[n_detector_1]
                                           ->channels[n_channel_1])
                                       ->time_vs_time_RF_calibrated);

                        for (size_t n_channel_2 = n_channel_1 + 1;
                             n_channel_2 <
                             analysis.detectors[n_detector_1]->channels.size();
                             ++n_channel_2) {
                            if (!isnan(dynamic_pointer_cast<
                                           EnergySensitiveDetectorChannel>(
                                           analysis.detectors[n_detector_1]
                                               ->channels[n_channel_2])
                                           ->energy_calibrated) &&
                                dynamic_pointer_cast<
                                    EnergySensitiveDetectorChannel>(
                                    analysis.detectors[n_detector_1]
                                        ->channels[n_channel_2])
                                    ->time_vs_time_RF_gate(
                                        dynamic_pointer_cast<
                                            EnergySensitiveDetectorChannel>(
                                            analysis.detectors[n_detector_1]
                                                ->channels[n_channel_2])
                                            ->time_vs_time_RF_calibrated)) {
                                time_difference_histograms
                                    [n_detector_1][n_channel_1][0]
                                    [n_channel_2 - n_channel_1 - 1]
                                        ->Fill(
                                            dynamic_pointer_cast<
                                                EnergySensitiveDetectorChannel>(
                                                analysis
                                                    .detectors[n_detector_1]
                                                    ->channels[n_channel_1])
                                                ->time_calibrated -
                                            dynamic_pointer_cast<
                                                EnergySensitiveDetectorChannel>(
                                                analysis
                                                    .detectors[n_detector_1]
                                                    ->channels[n_channel_2])
                                                ->time_calibrated);
                            }
                        }

                        for (size_t n_detector_2 = n_detector_1 + 1;
                             n_detector_2 < analysis.detectors.size();
                             ++n_detector_2) {
                            if (analysis.detectors[n_detector_2]->type ==
                                energy_sensitive) {
                                for (size_t n_channel_2 = 0;
                                     n_channel_2 <
                                     analysis.detectors[n_detector_2]
                                         ->channels.size();
                                     ++n_channel_2) {
                                    if (!isnan(
                                            dynamic_pointer_cast<
                                                EnergySensitiveDetectorChannel>(
                                                analysis
                                                    .detectors[n_detector_2]
                                                    ->channels[n_channel_2])
                                                ->energy_calibrated) &&
                                        dynamic_pointer_cast<
                                            EnergySensitiveDetectorChannel>(
                                            analysis.detectors[n_detector_2]
                                                ->channels[n_channel_2])
                                            ->time_vs_time_RF_gate(
                                                dynamic_pointer_cast<
                                                    EnergySensitiveDetectorChannel>(
                                                    analysis
                                                        .detectors[n_detector_2]
                                                        ->channels[n_channel_2])
                                                    ->time_vs_time_RF_calibrated)) {
                                        time_difference_histograms
                                            [n_detector_1][n_channel_1]
                                            [n_detector_2 - n_detector_1]
                                            [n_channel_2]
                                                ->Fill(
                                                    dynamic_pointer_cast<
                                                        EnergySensitiveDetectorChannel>(
                                                        analysis
                                                            .detectors
                                                                [n_detector_1]
                                                            ->channels
                                                                [n_channel_1])
                                                        ->time_calibrated -
                                                    dynamic_pointer_cast<
                                                        EnergySensitiveDetectorChannel>(
                                                        analysis
                                                            .detectors
                                                                [n_detector_2]
                                                            ->channels
                                                                [n_channel_2])
                                                        ->time_calibrated);
                                    }
                                }
                            }
                        }
                    }
                }
                if (analysis.detectors[n_detector_1]->channels.size() > 1 &&
                    !isnan(dynamic_pointer_cast<EnergySensitiveDetector>(
                               analysis.detectors[n_detector_1])
                               ->addback_energy)) {
                    addback_histograms[n_detector_1]->Fill(
                        dynamic_pointer_cast<EnergySensitiveDetector>(
                            analysis.detectors[n_detector_1])
                            ->addback_energy);
                }
            } else if (analysis.detectors[n_detector_1]->type == counter) {
                for (size_t n_channel = 0;
                     n_channel <
                     analysis.detectors[n_detector_1]->channels.size();
                     ++n_channel) {
                    if (!isnan(dynamic_pointer_cast<CounterDetectorChannel>(
                                   analysis.detectors[n_detector_1]
                                       ->channels[n_channel])
                                   ->count_rate)) {
                        histograms[n_detector_1][n_channel]->Fill(
                            dynamic_pointer_cast<CounterDetectorChannel>(
                                analysis.detectors[n_detector_1]
                                    ->channels[n_channel])
                                ->count_rate);
                    }
                }
            }
        }
    }

    TFile output_file(vm["output"].as<string>().c_str(), "RECREATE");
    TDirectory *directory;

    for (size_t n_detector_1 = 0; n_detector_1 < analysis.detectors.size();
         ++n_detector_1) {
        if (analysis.detectors[n_detector_1]->type == energy_sensitive) {
            directory = output_file.mkdir(
                (analysis.detectors[n_detector_1]->name + "_tdiff").c_str());
        }
        if (analysis.detectors[n_detector_1]->channels.size() > 1) {
            addback_histograms[n_detector_1]->Write();
        }
        for (size_t n_channel_1 = 0;
             n_channel_1 < analysis.detectors[n_detector_1]->channels.size();
             ++n_channel_1) {
            histograms[n_detector_1][n_channel_1]->Write();
            if (analysis.detectors[n_detector_1]->type == energy_sensitive) {
                directory->cd();
                time_vs_time_RF_histograms[n_detector_1][n_channel_1]->Write();

                for (size_t n_channel_2 = n_channel_1 + 1;
                     n_channel_2 <
                     analysis.detectors[n_detector_1]->channels.size();
                     ++n_channel_2) {
                    time_difference_histograms[n_detector_1][n_channel_1][0]
                                              [n_channel_2 - n_channel_1 - 1]
                                                  ->Write();
                }

                for (size_t n_detector_2 = n_detector_1 + 1;
                     n_detector_2 < analysis.detectors.size(); ++n_detector_2) {
                    if (analysis.detectors[n_detector_2]->type ==
                        energy_sensitive) {
                        for (size_t n_channel_2 = 0;
                             n_channel_2 <
                             analysis.detectors[n_detector_2]->channels.size();
                             ++n_channel_2) {
                            time_difference_histograms
                                [n_detector_1][n_channel_1]
                                [n_detector_2 - n_detector_1][n_channel_2]
                                    ->Write();
                        }
                    }
                }
                output_file.cd();
            }
        }
    }

    output_file.Close();
    cout << "Created output file '" << vm["output"].as<string>() << "'."
         << endl;
}