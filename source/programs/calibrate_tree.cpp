#include <fstream>

using std::ofstream;

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
        "block", po::value<long long>()->default_value(1000000),
        "Number of data entries that are processed before the data are written "
        "to file (default: 10^6).")(
        "log",
        "Create a text file ('log file') that contains the names of the "
        "generated "
        "output files (default: create no log file). The log file will have "
        "the same prefix as the ROOT output file, but a '.log' suffix.");
    int command_line_parser_status;
    command_line_parser(argc, argv, command_line_parser_status);
    if (command_line_parser_status) {
        return 0;
    }
    po::variables_map vm = command_line_parser.get_variables_map();

    long long first, last;
    TChain *t = command_line_parser.set_up_tree(first, last, vm.count("list"));

    vector<pair<long long, long long>> blocks =
        divide_into_blocks(first, last, vm["block"].as<long long>());
    const string tree_calibrated_name = t->GetName();

    ProgressPrinter progress_printer(first, last);
    vector<string> output_file_names;

    for (size_t n_block = 0; n_block < blocks.size(); ++n_block) {
        TChain *tree = command_line_parser.set_up_tree(first, last);
        analysis.set_up_raw_branches_for_reading(tree);
        TTree *tree_calibrated = new TTree(tree_calibrated_name.c_str(),
                                           tree_calibrated_name.c_str());

        analysis.set_up_calibrated_branches_for_writing(tree_calibrated);

        for (long long i = blocks[n_block].first; i <= blocks[n_block].second;
             ++i) {
            tree->GetEntry(i);
            analysis.calibrate(i);
            tree_calibrated->Fill();
            analysis.reset_calibrated_leaves();
            progress_printer(i);
        }

        output_file_names.push_back(
            add_index_to_file_name(vm["output"].as<string>(), n_block));
        TFile output_file(output_file_names[n_block].c_str(), "RECREATE");
        tree_calibrated->Write();
        output_file.Close();
        cout << "Wrote block [" << blocks[n_block].first << ", "
             << blocks[n_block].second << "] to output file '"
             << output_file_names[n_block] << "'." << endl;

        delete tree_calibrated;
        delete tree;
    }
    if (vm.count("log")) {
        const string log_file_name =
            add_or_change_file_name_suffix(vm["output"].as<string>(), ".log");
        ofstream log_file(log_file_name);
        for (auto file : output_file_names) {
            log_file << file;
            log_file << "\n";
        }
        log_file.close();

        cout << "Wrote list of generated output files to '" << log_file_name
             << "'." << endl;
    }
}