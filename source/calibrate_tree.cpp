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

    const string tree_calibrated_name = tree->GetName();
    TTree *tree_calibrated =
        new TTree(tree_calibrated_name.c_str(), tree_calibrated_name.c_str());

    ProgressPrinter progress_printer(last - first + 1, 0.001);

    for (size_t i = 0; i < modules.size(); ++i) {
        modules[i]->activate_branches(tree);
        modules[i]->register_branches(tree);
    }

    detector_setup.create_branches(tree_calibrated);

    for (long long i = first; i <= last; ++i) {
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