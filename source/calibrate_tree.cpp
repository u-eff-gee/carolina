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

    const string tree_name = find_tree_in_file(
        vm["input_file"].as<vector<string>>()[0], vm["tree"].as<string>());
    TChain *tree = new TChain(tree_name.c_str());
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

    const string tree_calibrated_name = tree_name;
    TTree *tree_calibrated =
        new TTree(tree_calibrated_name.c_str(), tree_calibrated_name.c_str());

    ProgressPrinter progress_printer(last - first + 1, 0.001);

    for (size_t i = 0; i < modules.size(); ++i) {
        modules[i]->activate_branches(tree);
        modules[i]->register_branches(tree);
    }

    detector_setup.create_branches(tree_calibrated);

    for (int i = first; i <= last; ++i) {
        progress_printer(i - first);

        tree->GetEntry(i);
        detector_setup.calibrate(i);
        tree_calibrated->Fill();
        detector_setup.reset();
    }

    TFile output_file(vm["output_file"].as<string>().c_str(), "RECREATE");
    tree_calibrated->Write();
    output_file.Close();
    cout << "Created output file '" << vm["output_file"].as<string>() << "'."
         << endl;
}