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
        "first", po::value<long long>()->default_value(0),
        "First entry to be processed.")("input", po::value<vector<string>>(),
                                        "Input file names.")(
        "last", po::value<long long>()->default_value(-1),
        "Last entry to be processed.")(
        "output", po::value<string>()->default_value("output.root"),
        "Output file name (default: 'output.root').")(
        "tree", po::value<string>()->default_value(""),
        "TTree name [default: \"\" (empty string), i.e. take the first TTree "
        "in the file]");
    p.add("input", -1);
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
    } else if (!vm.count("input")) {
        cout << "No input file given. Aborting ..." << endl;
        status = 1;
    }
}

TChain *CommandLineParser::set_up_tree(long long &first,
                                       long long &last) const {
    TChain *tree =
        new TChain(find_tree_in_file(vm["input"].as<vector<string>>()[0],
                                     vm["tree"].as<string>())
                       .c_str());
    vector<string> input_files = vm["input"].as<vector<string>>();
    for (auto input_file : input_files) {
        cout << "Adding '" << input_file.c_str() << "' to TChain." << endl;
        tree->Add(input_file.c_str());
    }

    first = vm["first"].as<long long>();
    last = vm["last"].as<long long>() == -1 ? tree->GetEntries()
                                            : vm["last"].as<long long>();

    if (first > last) {
        cout << "Error: first entry (" << first
             << ") is larger or equal to last entry (" << last
             << "). Aborting ..." << endl;
        abort();
    }

    return tree;
};
