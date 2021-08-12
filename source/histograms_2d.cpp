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

int main(int argc, char **argv) {
    CommandLineParser command_line_parser;
    command_line_parser(argc, argv);
    po::variables_map vm = command_line_parser.get_variables_map();

    TChain *tree = new TChain(vm["tree"].as<string>().c_str());
    vector<string> input_files = vm["input_file"].as<vector<string>>();
    for (auto input_file : input_files) {
        cout << "Adding '" << input_file.c_str() << "' to TChain." << endl;
        tree->Add(input_file.c_str());
    }

    const int first = vm["first"].as<int>();
    const int last =
        vm["last"].as<int>() == 0 ? tree->GetEntries() : vm["last"].as<int>();

    if (first > last) {
        cout << "Error: first entry (" << first
             << ") is larger or equal to last entry (" << last
             << "). Aborting ..." << endl;
        return 0;
    }

    ProgressPrinter progress_printer(last - first + 1, 0.001);

    for (size_t i = 0; i < modules.size(); ++i) {
        modules[i].register_branches(tree);
    }

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

    for (int i = first; i <= last; ++i) {
        progress_printer(i - first);

        tree->GetEntry(i);
        for(size_t n_detector = 0; n_detector < detectors.size(); ++n_detector){
            for(size_t n_channel = 0; n_channel < detectors[n_detector].channels.size(); ++n_channel){
                detectors[n_detector].channels[n_channel].calibrate(i);
            }
        }

        for (size_t n_matrix = 0; n_matrix < coincidence_matrices.size();
             ++n_matrix) {
            if (coincidence_matrices[n_matrix].y_data.size()) {
                for (auto n_detector_1 :
                     coincidence_matrices[n_matrix].x_data) {
                    for (size_t n_channel_1 = 0;
                         n_channel_1 < detectors[n_detector_1].channels.size();
                         ++n_channel_1) {
                        for (auto n_detector_2 :
                             coincidence_matrices[n_matrix].y_data) {
                            for (size_t n_channel_2 = 0;
                                 n_channel_2 <
                                 detectors[n_detector_2].channels.size();
                                 ++n_channel_2) {
                                if (detectors[n_detector_1]
                                            .channels[n_channel_1]
                                            .energy_calibrated > 0. &&
                                    detectors[n_detector_2]
                                            .channels[n_channel_2]
                                            .energy_calibrated > 0.) {
                                    coincidence_histograms[n_matrix]->Fill(
                                        detectors[n_detector_1]
                                            .channels[n_channel_1]
                                            .energy_calibrated,
                                        detectors[n_detector_2]
                                            .channels[n_channel_2]
                                            .energy_calibrated);
                                    if (coincidence_matrices[n_matrix]
                                            .symmetrize) {
                                        coincidence_histograms[n_matrix]->Fill(
                                            detectors[n_detector_2]
                                                .channels[n_channel_2]
                                                .energy_calibrated,
                                            detectors[n_detector_1]
                                                .channels[n_channel_1]
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