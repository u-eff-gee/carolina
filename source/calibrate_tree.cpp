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
    command_line_parser.desc.add_options()(
        "block_size", po::value<long long>()->default_value(1000000),
        "Number of data entries that are processed before the data are written "
        "to file (default: 10^5).");
    int command_line_parser_status;
    command_line_parser(argc, argv, command_line_parser_status);
    if (command_line_parser_status) {
        return 0;
    }
    po::variables_map vm = command_line_parser.get_variables_map();

    long long first, last;
    TChain *t = command_line_parser.set_up_tree(first, last);

    vector<pair<long long, long long>> blocks =
        divide_into_blocks(first, last, vm["block_size"].as<long long>());
    const string tree_calibrated_name = t->GetName();

    ProgressPrinter progress_printer(last - first + 1, 0.001);
    string output_file_name;

    for (size_t n_block = 0; n_block < blocks.size(); ++n_block) {
        TChain *tree = command_line_parser.set_up_tree(first, last);
        for (size_t i = 0; i < modules.size(); ++i) {
            modules[i]->activate_branches(tree);
            modules[i]->register_branches(tree);
        }
        TTree *tree_calibrated = new TTree(tree_calibrated_name.c_str(),
                                           tree_calibrated_name.c_str());

        analysis.create_branches(tree_calibrated);

        for (long long i = blocks[n_block].first; i <= blocks[n_block].second;
             ++i) {
            progress_printer(i - first);

            tree->GetEntry(i);
            analysis.calibrate(i);
            tree_calibrated->Fill();
            analysis.reset();
        }

        output_file_name =
            add_index_to_file_name(vm["output"].as<string>(), n_block);
        TFile output_file(output_file_name.c_str(), "RECREATE");
        tree_calibrated->Write();
        output_file.Close();
        cout << "Wrote block [" << blocks[n_block].first << ", "
             << blocks[n_block].second - 1 << "] to output file '"
             << output_file_name << "'." << endl;

        delete tree_calibrated;
        delete tree;
    }
}