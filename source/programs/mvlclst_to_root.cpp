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

#include "TChain.h"
#include "TFile.h"
#include "TH1D.h"

#include "command_line_parser.hpp"
#include "counter_detector_channel.hpp"
#include "energy_sensitive_detector_channel.hpp"
#include "mvlclst_to_root.hpp"
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

    Reader reader(vm.count("list") == 0
                      ? vm["input"].as<vector<string>>()
                      : read_log_file(vm["input"].as<vector<string>>()[0]),
                  vm["first"].as<long long>(), vm["last"].as<long long>());
    reader.initialize(analysis, vm["tree"].as<string>(), {false},
                      {true, true, true, true});
    ProgressPrinter progress_printer(reader.first, reader.last);

    long long first, last;
    TFile output_file(vm["output"].as<string>().c_str(), "RECREATE");
    TTree *tree = new TTree("events", "events");
    analysis.set_up_raw_energy_sensitive_detector_branches_for_writing(tree, {true, true, true, true});

    unsigned int status;

    while (reader.read(status, analysis)) {
        if(status==1){
            tree->Fill();
            analysis.reset_raw_energy_sensitive_detector_leaves({true, true, true, true});
            progress_printer(reader.entry);
        }
    }

    tree->Write();
    output_file.Close();

    cout << "Created output file '" << vm["output"].as<string>() << "'."
         << endl;
}