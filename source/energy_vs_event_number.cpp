#include <iostream>

using std::cout;
using std::endl;

#include "TChain.h"
#include "TFile.h"
#include "TH2D.h"

#include "command_line_parser.hpp"
#include "energy_vs_event_number.hpp"
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

    vector<vector<TH2D *>> energy_vs_event_number_histograms;
    string histogram_name;

    for (size_t n_detector = 0; n_detector < detector_setup.detectors.size();
         ++n_detector) {
        energy_vs_event_number_histograms.push_back(vector<TH2D *>());
        for (auto channel : detector_setup.detectors[n_detector].channels) {
            histogram_name =
                detector_setup.detectors[n_detector].name + "_" + channel.name;
            energy_vs_event_number_histograms[n_detector].push_back(
                new TH2D(histogram_name.c_str(), histogram_name.c_str(), 256,
                         first, last,
                         detector_setup.detectors[n_detector]
                             .group.energy_histogram_properties.n_bins,
                         detector_setup.detectors[n_detector]
                             .group.energy_histogram_properties.minimum,
                         detector_setup.detectors[n_detector]
                             .group.energy_histogram_properties.maximum));
        }
    }

    for (long long i = first; i <= last; ++i) {
        progress_printer(i - first);

        tree->GetEntry(i);

        for (size_t n_detector = 0;
             n_detector < detector_setup.detectors.size(); ++n_detector) {
            for (size_t n_channel = 0;
                 n_channel <
                 detector_setup.detectors[n_detector].channels.size();
                 ++n_channel) {
                if (!isnan(detector_setup.detectors[n_detector]
                               .channels[n_channel]
                               .energy_calibrated)) {
                    energy_vs_event_number_histograms[n_detector][n_channel]
                        ->Fill(i, detector_setup.detectors[n_detector]
                                      .channels[n_channel]
                                      .energy_calibrated);
                }
            }
        }
    }

    TFile output_file(vm["output_file"].as<string>().c_str(), "RECREATE");

    for (size_t n_detector = 0; n_detector < detector_setup.detectors.size();
         ++n_detector) {
        for (size_t n_channel = 0;
             n_channel < detector_setup.detectors[n_detector].channels.size();
             ++n_channel) {
            energy_vs_event_number_histograms[n_detector][n_channel]->Write();
        }
    }

    output_file.Close();
    cout << "Created output file '" << vm["output_file"].as<string>() << "'."
         << endl;
}