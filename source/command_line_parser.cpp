#include <iostream>

using std::cout;
using std::endl;

#include <string>

using std::string;

#include <vector>

using std::vector;

#include "command_line_parser.hpp"
#include "tfile_utilities.hpp"

CommandLineParser::CommandLineParser() {
    desc.add_options()("help", "Produce help message.")(
        "first", po::value<int>()->default_value(1),
        "First entry to be processed.")(
        "input_file", po::value<vector<string>>(),
        "Input file names.")("last", po::value<int>()->default_value(0),
                             "Last entry to be processed.")(
        "output_file", po::value<string>()->default_value("output.root"),
        "Output file name (default: 'output.root').")(
        "tree", po::value<string>()->default_value(""),
        "TTree name [default: \"\" (empty string), i.e. take the first TTree "
        "in the file]");
    p.add("input_file", -1);
}

void CommandLineParser::operator()(int argc, char *argv[], int &status) {
    po::store(
        po::command_line_parser(argc, argv).options(desc).positional(p).run(),
        vm);
    po::notify(vm);

    status = 0;

    if (vm.count("help")) {
        cout << desc << endl;
        status = 1;
    } else if (!vm.count("input_file")) {
        cout << "No input file given. Aborting ..." << endl;
        status = 1;
    }
}

TChain* CommandLineParser::set_up_tree(long long &first, long long &last) const {
    TChain *tree =
        new TChain(find_tree_in_file(vm["input_file"].as<vector<string>>()[0],
                                     vm["tree"].as<string>())
                       .c_str());
    cout << tree->GetName() << endl;
    vector<string> input_files = vm["input_file"].as<vector<string>>();
    for (auto input_file : input_files) {
        cout << "Adding '" << input_file.c_str() << "' to TChain." << endl;
        tree->Add(input_file.c_str());
    }
    cout << tree->GetName() << endl;

    first = vm["first"].as<int>();
    last =
        vm["last"].as<int>() == 0 ? tree->GetEntries() : vm["last"].as<int>();

    if (first > last) {
        cout << "Error: first entry (" << first
             << ") is larger or equal to last entry (" << last
             << "). Aborting ..." << endl;
        abort();
    }

    return tree;
};
