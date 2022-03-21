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

#include <iostream>

using std::cout;
using std::endl;

#include <memory>

using std::dynamic_pointer_cast;

#include "TChain.h"
#include "TFile.h"
#include "TH2I.h"

#include "command_line_parser.hpp"
#include "energy_sensitive_detector.hpp"
#include "energy_sensitive_detector_channel.hpp"
#include "histograms_2d.hpp"
#include "progress_printer.hpp"
#include "tfile_utilities.hpp"

void fill(TH2I *histogram, const CoincidenceMatrix matrix,
          const double energy_1, const double energy_2) {
    histogram->Fill(energy_1, energy_2);
    if (!matrix.detectors_y.size()) {
        histogram->Fill(energy_2, energy_1);
    }
}

int main(int argc, char **argv) {
    CommandLineParser command_line_parser;
    int command_line_parser_status;
    command_line_parser(argc, argv, command_line_parser_status);
    if (command_line_parser_status) {
        return 0;
    }
    const po::variables_map vm = command_line_parser.get_variables_map();

    long long first, last;
    TChain *tree =
        command_line_parser.set_up_tree(first, last, vm.count("list"));

    ProgressPrinter progress_printer(first, last);

    tree->SetBranchStatus("*", 0);
    analysis.set_up_calibrated_counter_detector_branches_for_reading(tree);
    analysis.set_up_calibrated_energy_sensitive_detector_branches_for_reading(
        tree);

    vector<vector<pair<size_t, size_t>>> coincidence_pairs;
    vector<TH2I *> coincidence_histograms;
    string histogram_name;

    for (auto matrix : analysis.coincidence_matrices) {
        coincidence_pairs.push_back(matrix.get_coincidence_pairs());
        coincidence_histograms.push_back(new TH2I(
            matrix.name.c_str(), matrix.name.c_str(), matrix.x_axis.n_bins,
            matrix.x_axis.lower_edge_of_first_bin,
            matrix.x_axis.upper_edge_of_last_bin, matrix.y_axis.n_bins,
            matrix.y_axis.lower_edge_of_first_bin,
            matrix.y_axis.upper_edge_of_last_bin));
    }

    for (long long i = first; i <= last; ++i) {
        tree->GetEntry(i);

        for (size_t n_matrix = 0;
             n_matrix < analysis.coincidence_matrices.size(); ++n_matrix) {
            for (auto detector_pair : coincidence_pairs[n_matrix]) {
                if (!isnan(dynamic_pointer_cast<EnergySensitiveDetector>(
                               analysis.detectors[detector_pair.first])
                               ->get_calibrated_and_RF_gated_energy()) &&
                    !isnan(dynamic_pointer_cast<EnergySensitiveDetector>(
                               analysis.detectors[detector_pair.second])
                               ->get_calibrated_and_RF_gated_energy())) {
                    fill(coincidence_histograms[n_matrix],
                         analysis.coincidence_matrices[n_matrix],
                         dynamic_pointer_cast<EnergySensitiveDetector>(
                             analysis.detectors[detector_pair.first])
                             ->get_calibrated_and_RF_gated_energy(),
                         dynamic_pointer_cast<EnergySensitiveDetector>(
                             analysis.detectors[detector_pair.second])
                             ->get_calibrated_and_RF_gated_energy());
                }
            }
        }

        progress_printer(i);
    }

    TFile output_file(vm["output"].as<string>().c_str(), "RECREATE");

    for (size_t n_histogram = 0; n_histogram < coincidence_histograms.size();
         ++n_histogram) {
        coincidence_histograms[n_histogram]->Write();
    }

    output_file.Close();
    cout << "Created output file '" << vm["output"].as<string>() << "'."
         << endl;
}