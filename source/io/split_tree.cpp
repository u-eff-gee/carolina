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

#include "progress_printer.hpp"
#include "split_tree.hpp"
#include "tfile_utilities.hpp"

int main(int argc, char **argv) {
    po::options_description desc(
        "Split a single ROOT file or a TChain of heterogeneoous ROOT files "
        "which contain the same TTree structure into n files with the same "
        "size (more precisely: number of contained events up to rounding) for "
        "easier parallel processing.");
    desc.add_options()("help", "Produce help message.")(
        "n", po::value<unsigned int>()->default_value(0),
        "Number of output files (default: 0, which means split the input files "
        "into the same number of output files, but with the same size).")(
        "input_file", po::value<vector<string>>(), "Input file name.")(
        "output_file_prefix", po::value<string>()->default_value("output"),
        "Prefix of the output file names (default: \"output\", i.e. files will "
        "be named 'output_0.root', 'output_1.root', ...).")(
        "tree", po::value<string>()->default_value(""),
        "TTree name [default: \"\" (empty string), i.e. take the "
        "first TTree in the file]");
    ;
    po::positional_options_description p;
    p.add("input_file", -1);

    po::variables_map vm;

    po::store(
        po::command_line_parser(argc, argv).options(desc).positional(p).run(),
        vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << desc << endl;
        return 0;
    } else if (!vm.count("input_file")) {
        cout << "No input file given. Aborting ..." << endl;
        return 1;
    }

    TChain *tree =
        new TChain(find_tree_in_file(vm["input_file"].as<vector<string>>()[0],
                                     vm["tree"].as<string>())
                       .c_str());
    vector<string> input_files = vm["input_file"].as<vector<string>>();
    for (auto input_file : input_files) {
        cout << "Adding '" << input_file.c_str() << "' to TChain." << endl;
        tree->Add(input_file.c_str());
    }

    unsigned int n_output_files;
    if (vm["n"].as<unsigned int>() == 0) {
        n_output_files = vm["input_file"].as<vector<string>>().size();
    } else {
        n_output_files = vm["n"].as<unsigned int>();
    }

    const int n_entries = tree->GetEntries();
    const int n_entries_per_file = n_entries / n_output_files;
    const int n_entries_remainder = n_entries % n_output_files;

    analysis.set_up_calibrated_branches_for_reading(tree);

    ProgressPrinter progress_printer(n_entries, 0.001);

    int n_entry_stop;
    string output_file_name;
    TFile *new_file;
    TTree *new_tree;

    for (unsigned int n_file = 0; n_file < n_output_files; ++n_file) {
        output_file_name = vm["output_file_prefix"].as<string>() + "_" +
                           to_string(n_file) + ".root";
        new_file = new TFile(output_file_name.c_str(), "RECREATE");
        new_tree = tree->CloneTree(0);
        if (n_file < n_output_files - 1) {
            n_entry_stop = (int)(n_file + 1) * n_entries_per_file;
        } else {
            n_entry_stop = (int)(n_file + 1) * n_entries_per_file +
                           n_entries_remainder - 1;
        }
        for (int n_entry = n_file * n_entries_per_file;
             n_entry < n_entry_stop; ++n_entry) {
            progress_printer(n_entry);
            tree->GetEntry(n_entry);
            new_tree->Fill();
        }
        new_tree->Write();
        new_file->Close();
    }
}