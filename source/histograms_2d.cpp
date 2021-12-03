#include <algorithm>

using std::max;
using std::min;

#include <iostream>

using std::cout;
using std::endl;

#include "TChain.h"
#include "TFile.h"
#include "TH2D.h"

#include "command_line_parser.hpp"
#include "histograms_1d.hpp"
#include "progress_printer.hpp"
#include "tfile_utilities.hpp"

int main(int argc, char **argv) {
    CommandLineParser command_line_parser;
    int command_line_parser_status;
    command_line_parser(argc, argv, command_line_parser_status);
    if (command_line_parser_status) {
        return 0;
    }
    po::variables_map vm = command_line_parser.get_variables_map();

    long long first, last;
    TChain *tree = command_line_parser.set_up_tree(first, last);

    ProgressPrinter progress_printer(last - first + 1, 0.001);

    detector_setup.activate_branches(tree);
    detector_setup.register_branches(tree);

    vector<TH2D *> coincidence_histograms;
    string histogram_name;

    for (size_t n_matrix = 0; n_matrix < coincidence_matrices.size();
         ++n_matrix) {
        coincidence_histograms.push_back(
            new TH2D(coincidence_matrices[n_matrix].name.c_str(),
                     coincidence_matrices[n_matrix].name.c_str(),
                     coincidence_matrices[n_matrix].x_axis.n_bins,
                     coincidence_matrices[n_matrix].x_axis.minimum,
                     coincidence_matrices[n_matrix].x_axis.maximum,
                     coincidence_matrices[n_matrix].y_axis.n_bins,
                     coincidence_matrices[n_matrix].y_axis.minimum,
                     coincidence_matrices[n_matrix].y_axis.maximum));
    }

    for (long long i = first; i <= last; ++i) {
        progress_printer(i - first);

        tree->GetEntry(i);

        for (size_t n_matrix = 0; n_matrix < coincidence_matrices.size();
             ++n_matrix) {
            if (!coincidence_matrices[n_matrix].detectors_y.size()) {
                for (size_t n_detector_1 = 0;
                     n_detector_1 <
                     coincidence_matrices[n_matrix].detectors_x.size();
                     ++n_detector_1) {
                    for (size_t n_channel_1 = 0;
                         n_channel_1 <
                         detector_setup.detectors[n_detector_1].channels.size();
                         ++n_channel_1) {
                        if (!isnan(
                                detector_setup
                                    .detectors[coincidence_matrices[n_matrix]
                                                   .detectors_x[n_detector_1]]
                                    .channels[n_channel_1]
                                    .energy_calibrated) &&
                            detector_setup
                                .detectors[coincidence_matrices[n_matrix]
                                               .detectors_x[n_detector_1]]
                                .channels[n_channel_1]
                                .time_vs_time_RF_gate(
                                    detector_setup
                                        .detectors
                                            [coincidence_matrices[n_matrix]
                                                 .detectors_x[n_detector_1]]
                                        .channels[n_channel_1]
                                        .time_vs_time_RF_calibrated)) {
                            for (size_t n_detector_2 = n_detector_1 + 1;
                                 n_detector_2 < coincidence_matrices[n_matrix]
                                                    .detectors_x.size();
                                 ++n_detector_2) {
                                for (size_t n_channel_2 = 0;
                                     n_channel_2 <
                                     detector_setup.detectors[n_detector_2]
                                         .channels.size();
                                     ++n_channel_2) {
                                    if (!isnan(
                                            detector_setup
                                                .detectors
                                                    [coincidence_matrices
                                                         [n_matrix]
                                                             .detectors_x
                                                                 [n_detector_2]]
                                                .channels[n_channel_2]
                                                .energy_calibrated) &&
                                        detector_setup
                                            .detectors
                                                [coincidence_matrices[n_matrix]
                                                     .detectors_x[n_detector_2]]
                                            .channels[n_channel_2]
                                            .time_vs_time_RF_gate(
                                                detector_setup
                                                    .detectors
                                                        [coincidence_matrices
                                                             [n_matrix]
                                                                 .detectors_x
                                                                     [n_detector_2]]
                                                    .channels[n_channel_2]
                                                    .time_vs_time_RF_calibrated)) {
                                        coincidence_histograms[n_matrix]->Fill(
                                            detector_setup
                                                .detectors
                                                    [coincidence_matrices
                                                         [n_matrix]
                                                             .detectors_x
                                                                 [n_detector_1]]
                                                .channels[n_channel_1]
                                                .energy_calibrated,
                                            detector_setup
                                                .detectors
                                                    [coincidence_matrices
                                                         [n_matrix]
                                                             .detectors_x
                                                                 [n_detector_2]]
                                                .channels[n_channel_2]
                                                .energy_calibrated);
                                        coincidence_histograms[n_matrix]->Fill(
                                            detector_setup
                                                .detectors
                                                    [coincidence_matrices
                                                         [n_matrix]
                                                             .detectors_x
                                                                 [n_detector_2]]
                                                .channels[n_channel_2]
                                                .energy_calibrated,
                                            detector_setup
                                                .detectors
                                                    [coincidence_matrices
                                                         [n_matrix]
                                                             .detectors_x
                                                                 [n_detector_1]]
                                                .channels[n_channel_1]
                                                .energy_calibrated);
                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                for (size_t n_detector_x = 0;
                     n_detector_x <
                     coincidence_matrices[n_matrix].detectors_x.size();
                     ++n_detector_x) {
                    for (size_t n_channel_x = 0;
                         n_channel_x <
                         detector_setup.detectors[n_detector_x].channels.size();
                         ++n_channel_x) {
                        if (!isnan(
                                detector_setup
                                    .detectors[coincidence_matrices[n_matrix]
                                                   .detectors_x[n_detector_x]]
                                    .channels[n_channel_x]
                                    .energy_calibrated)) {
                            for (size_t n_detector_y = 0;
                                 n_detector_y < coincidence_matrices[n_matrix]
                                                    .detectors_y.size();
                                 ++n_detector_y) {
                                for (size_t n_channel_y = 0;
                                     n_channel_y <
                                     detector_setup.detectors[n_detector_y]
                                         .channels.size();
                                     ++n_channel_y) {
                                    if (!isnan(
                                            detector_setup
                                                .detectors
                                                    [coincidence_matrices
                                                         [n_matrix]
                                                             .detectors_y
                                                                 [n_detector_y]]
                                                .channels[n_channel_y]
                                                .energy_calibrated)) {
                                        coincidence_histograms[n_matrix]->Fill(
                                            detector_setup
                                                .detectors
                                                    [coincidence_matrices
                                                         [n_matrix]
                                                             .detectors_x
                                                                 [n_detector_x]]
                                                .channels[n_channel_x]
                                                .energy_calibrated,
                                            detector_setup
                                                .detectors
                                                    [coincidence_matrices
                                                         [n_matrix]
                                                             .detectors_y
                                                                 [n_detector_y]]
                                                .channels[n_channel_y]
                                                .energy_calibrated);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    TFile output_file(vm["output_file"].as<string>().c_str(), "RECREATE");

    for (size_t n_histogram = 0; n_histogram < coincidence_histograms.size();
         ++n_histogram) {
        coincidence_histograms[n_histogram]->Write();
    }

    output_file.Close();
    cout << "Created output file '" << vm["output_file"].as<string>() << "'."
         << endl;
}