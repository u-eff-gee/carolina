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

#include <string>

using std::string;
using std::to_string;

#include <vector>

using std::vector;

#include <boost/program_options.hpp>

namespace po = boost::program_options;

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"

#include "command_line_parser.hpp"
#include "progress_printer.hpp"
#include "split_tree.hpp"
#include "tfile_utilities.hpp"

int main(int argc, char **argv) {
    CommandLineParser command_line_parser;
    command_line_parser.desc.add_options()(
        "log",
        "Create a text file ('log file') that contains the names of the "
        "generated "
        "output files (default: create no log file). The log file will have "
        "the same prefix as the ROOT output files, but a '.log' suffix.")(
        "n", po::value<unsigned int>()->default_value(0),
        "Number of output files (default: 0, which means split the input files "
        "into the same number of output files which all have the same size).");
    int command_line_parser_status;
    command_line_parser(argc, argv, command_line_parser_status);
    if (command_line_parser_status) {
        return 0;
    }
    po::variables_map vm = command_line_parser.get_variables_map();

    long long first, last;
    TChain *tree =
        command_line_parser.set_up_tree(first, last, vm.count("list"));

    unsigned int n_output_files;
    if (vm["n"].as<unsigned int>() == 0) {
        n_output_files = vm["input_file"].as<vector<string>>().size();
    } else {
        n_output_files = vm["n"].as<unsigned int>();
    }

    const long long n_entries = tree->GetEntries();
    const long long block_size =
        (long long)ceil((double)n_entries / (double)n_output_files);

    vector<pair<long long, long long>> blocks =
        divide_into_blocks(first, last, block_size);

    analysis.set_up_raw_branches_for_reading(tree);

    ProgressPrinter progress_printer(first, last);

    vector<string> output_file_names;
    TFile *new_file;
    TTree *new_tree;

    for (unsigned int n_block = 0; n_block < blocks.size(); ++n_block) {
        output_file_names.push_back(vm["output"].as<string>() + "_" +
                                    to_string(n_block) + ".root");
        new_file = new TFile(output_file_names[n_block].c_str(), "RECREATE");
        new_tree = tree->CloneTree(0);

        for (int n_entry = blocks[n_block].first;
             n_entry <= blocks[n_block].second; ++n_entry) {
            progress_printer(n_entry);
            tree->GetEntry(n_entry);
            new_tree->Fill();
        }
        new_tree->Write();
        new_file->Close();

        cout << "Wrote part " << (n_block + 1) << "/" << n_output_files
             << " of the data to '" << output_file_names[n_block] << "'."
             << endl;
    }

    if (vm.count("log")) {
        write_list_of_output_files(vm["output"].as<string>() + ".log",
                                   output_file_names);
    }
}