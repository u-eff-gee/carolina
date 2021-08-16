#include <iostream>

using std::cout;
using std::endl;

#include "TChain.h"
#include "TFile.h"
#include "TH2D.h"

#include "command_line_parser.hpp"
#include "energy_vs_time.hpp"
#include "progress_printer.hpp"

int main(int argc, char **argv) {
    CommandLineParser command_line_parser;
    command_line_parser.desc.add_options()(
        "rebin_time", po::value<unsigned int>()->default_value(1),
        "Reduce the number of bins in time histograms by this factor (default: "
        "1, i.e. no reduction).")(
        "rebin_energy", po::value<unsigned int>()->default_value(16),
        "Reduce the number of bins in energy histograms by this factor "
        "(default: 16, i.e. compress 16 bins into 1).");
    int command_line_parser_status;
    command_line_parser(argc, argv, command_line_parser_status);
    if (command_line_parser_status) {
        return 0;
    }
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
        modules[i]->register_branches(tree);
    }

    vector<vector<TH2D *>> energy_vs_time_histograms;
    string histogram_name;

    for (size_t n_detector = 0; n_detector < detectors.size(); ++n_detector) {
        energy_vs_time_histograms.push_back(vector<TH2D *>());
        for (auto channel : detectors[n_detector].channels) {
            histogram_name = detectors[n_detector].name + "_" + channel.name;
            energy_vs_time_histograms[n_detector].push_back(new TH2D(
                histogram_name.c_str(), histogram_name.c_str(),
                detectors[n_detector].group.energy_histogram_properties.n_bins /
                    8,
                detectors[n_detector].group.energy_histogram_properties.minimum,
                detectors[n_detector].group.energy_histogram_properties.maximum,
                detectors[n_detector]
                    .group.time_difference_histogram_properties.n_bins,
                detectors[n_detector]
                    .group.time_difference_histogram_properties.minimum,
                detectors[n_detector]
                    .group.time_difference_histogram_properties.maximum));
        }
    }

    for (int i = first; i <= last; ++i) {
        progress_printer(i - first);

        tree->GetEntry(i);

        for (size_t n_detector = 0; n_detector < detectors.size();
             ++n_detector) {
            for (size_t n_channel = 0;
                 n_channel < detectors[n_detector].channels.size();
                 ++n_channel) {
                detectors[n_detector].channels[n_channel].calibrate(i);
                if (detectors[n_detector]
                            .channels[n_channel]
                            .energy_calibrated > 0. &&
                    detectors[n_detector].channels[n_channel].time_calibrated >
                        0.) {
                    energy_vs_time_histograms[n_detector][n_channel]->Fill(
                        detectors[n_detector]
                            .channels[n_channel]
                            .energy_calibrated,
                        detectors[n_detector]
                            .channels[n_channel]
                            .time_calibrated);
                }
            }
        }
    }

    TFile output_file(vm["output_file"].as<string>().c_str(), "RECREATE");

    for (size_t n_detector = 0; n_detector < detectors.size(); ++n_detector) {
        for (size_t n_channel = 0;
             n_channel < detectors[n_detector].channels.size(); ++n_channel) {
            energy_vs_time_histograms[n_detector][n_channel]->Write();
        }
    }

    output_file.Close();
    cout << "Created output file '" << vm["output_file"].as<string>() << "'."
         << endl;
}