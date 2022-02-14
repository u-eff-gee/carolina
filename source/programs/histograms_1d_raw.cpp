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

#include <iostream>

using std::cout;
using std::endl;

#include <memory>

using std::dynamic_pointer_cast;

#include "TChain.h"
#include "TFile.h"
#include "TH1D.h"

#include "command_line_parser.hpp"
#include "counter_detector_channel.hpp"
#include "energy_sensitive_detector_channel.hpp"
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
    TChain *tree =
        command_line_parser.set_up_tree(first, last, vm.count("list"));

    ProgressPrinter progress_printer(first, last);

    analysis.set_up_raw_branches_for_reading(tree);

    vector<vector<TH1D *>> energy_sensitive_detector_histograms;
    vector<vector<TH1D *>> counter_detector_histograms;
    string histogram_name;

    for (size_t n_detector = 0;
         n_detector < analysis.energy_sensitive_detectors.size();
         ++n_detector) {
        energy_sensitive_detector_histograms.push_back(vector<TH1D *>());
        for (auto channel :
             analysis.energy_sensitive_detectors[n_detector]->channels) {
            histogram_name =
                analysis.energy_sensitive_detectors[n_detector]->name + "_" +
                channel->name;
            energy_sensitive_detector_histograms[n_detector].push_back(new TH1D(
                histogram_name.c_str(), histogram_name.c_str(),
                analysis.energy_sensitive_detectors[n_detector]
                    ->group->raw_histogram_properties.n_bins,
                analysis.energy_sensitive_detectors[n_detector]
                    ->group->raw_histogram_properties.lower_edge_of_first_bin,
                analysis.energy_sensitive_detectors[n_detector]
                    ->group->raw_histogram_properties.upper_edge_of_last_bin));
        }
    }
    for (size_t n_detector = 0; n_detector < analysis.counter_detectors.size();
         ++n_detector) {
        counter_detector_histograms.push_back(vector<TH1D *>());
        for (auto channel :
             analysis.energy_sensitive_detectors[n_detector]->channels) {
            histogram_name = analysis.counter_detectors[n_detector]->name +
                             "_" + channel->name;
            counter_detector_histograms[n_detector].push_back(new TH1D(
                histogram_name.c_str(), histogram_name.c_str(),
                analysis.counter_detectors[n_detector]
                    ->group->raw_histogram_properties.n_bins,
                analysis.counter_detectors[n_detector]
                    ->group->raw_histogram_properties.lower_edge_of_first_bin,
                analysis.counter_detectors[n_detector]
                    ->group->raw_histogram_properties.upper_edge_of_last_bin));
        }
    }

    for (long long i = first; i <= last; ++i) {
        tree->GetEntry(i);

        for (size_t n_detector = 0;
             n_detector < analysis.energy_sensitive_detectors.size();
             ++n_detector) {
            for (size_t n_channel = 0;
                 n_channel < analysis.energy_sensitive_detectors[n_detector]
                                 ->channels.size();
                 ++n_channel) {
                energy_sensitive_detector_histograms[n_detector][n_channel]
                    ->Fill(analysis.get_amplitude(n_detector, n_channel));
            }
        }
        for (size_t n_detector = 0;
             n_detector < analysis.counter_detectors.size(); ++n_detector) {
            for (size_t n_channel = 0;
                 n_channel <
                 analysis.counter_detectors[n_detector]->channels.size();
                 ++n_channel) {
                counter_detector_histograms[n_detector][n_channel]->Fill(
                    analysis.get_counts(n_detector, n_channel));
            }
        }
        progress_printer(i);
    }

    TFile output_file(vm["output"].as<string>().c_str(), "RECREATE");

    for (auto histogram_list : energy_sensitive_detector_histograms) {
        for (auto histogram : histogram_list) {
            histogram->Write();
        }
    }
    for (auto histogram_list : counter_detector_histograms) {
        for (auto histogram : histogram_list) {
            histogram->Write();
        }
    }

    output_file.Close();
    cout << "Created output file '" << vm["output"].as<string>() << "'."
         << endl;
}