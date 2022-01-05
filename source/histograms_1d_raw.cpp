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
    int command_line_parser_status;
    command_line_parser(argc, argv, command_line_parser_status);
    if (command_line_parser_status) {
        return 0;
    }
    po::variables_map vm = command_line_parser.get_variables_map();

    long long first, last;
    TChain *tree = command_line_parser.set_up_tree(first, last);

    ProgressPrinter progress_printer(last - first + 1, 0.001);

    analysis.activate_and_register_branches(tree);

    vector<vector<TH1D *>> energy_raw_histograms;
    vector<vector<TH1D *>> scaler_raw_histograms;
    string histogram_name;

    for (size_t n_detector = 0; n_detector < analysis.detectors.size();
         ++n_detector) {
        energy_raw_histograms.push_back(vector<TH1D *>());
        scaler_raw_histograms.push_back(vector<TH1D *>());
        for (size_t n_channel = 0;
             n_channel < analysis.detectors[n_detector]->channels.size();
             ++n_channel) {

            histogram_name =
                analysis.detectors[n_detector]->name + "_" +
                analysis.detectors[n_detector]->channels[n_channel].name;
            energy_raw_histograms[n_detector].push_back(
                new TH1D(histogram_name.c_str(), histogram_name.c_str(),
                         analysis.get_group(n_detector)
                             .energy_raw_histogram_properties.n_bins,
                         analysis.get_group(n_detector)
                             .energy_raw_histogram_properties.minimum,
                         analysis.get_group(n_detector)
                             .energy_raw_histogram_properties.maximum));

            histogram_name =
                analysis.detectors[n_detector]->name + "_" +
                analysis.detectors[n_detector]->channels[n_channel].name +
                "_scaler";
            scaler_raw_histograms[n_detector].push_back(
                new TH1D(histogram_name.c_str(), histogram_name.c_str(), 65536,
                         0., 2147483648.));
        }
    }

    for (long long i = first; i <= last; ++i) {
        progress_printer(i - first);

        tree->GetEntry(i);

        for (size_t n_detector = 0; n_detector < analysis.detectors.size();
             ++n_detector) {
            for (size_t n_channel = 0;
                 n_channel < analysis.detectors[n_detector]->channels.size();
                 ++n_channel) {
                if (analysis.get_amplitude(n_detector, n_channel) >
                        analysis.detectors[n_detector]
                            ->channels[n_channel]
                            .amplitude_threshold &&
                    analysis.get_time(n_detector, n_channel) > 0.) {
                    energy_raw_histograms[n_detector][n_channel]->Fill(
                        analysis.get_amplitude(n_detector, n_channel));
                }

                scaler_raw_histograms[n_detector][n_channel]->Fill(
                    analysis.get_counts(n_detector, n_channel));
            }
        }
    }

    TFile output_file(vm["output"].as<string>().c_str(), "RECREATE");

    for (size_t n_detector = 0; n_detector < analysis.detectors.size();
         ++n_detector) {
        for (size_t n_channel = 0;
             n_channel < analysis.detectors[n_detector]->channels.size();
             ++n_channel) {
            energy_raw_histograms[n_detector][n_channel]->Write();
            scaler_raw_histograms[n_detector][n_channel]->Write();
        }
    }

    output_file.Close();
    cout << "Created output file '" << vm["output"].as<string>() << "'."
         << endl;
}