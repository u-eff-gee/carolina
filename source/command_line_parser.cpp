#include <iostream>

using std::cout;
using std::endl;

#include <string>

using std::string;

#include <vector>

using std::vector;

#include "command_line_parser.hpp"

CommandLineParser::CommandLineParser(){
    desc.add_options()
        ("help", "Produce help message.")
        ("first", po::value<int>()->default_value(1), "First entry to be processed.")
        ("input_file", po::value<vector<string>>(), "Input file name.") 
        ("last", po::value<int>()->default_value(0), "Last entry to be processed.")
        ("output_file", po::value<string>()->default_value("output.root"), "Output file name (default: 'output.root').");
    p.add("input_file", -1);
}

void CommandLineParser::operator()(int argc, char* argv[]){
    po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
    po::notify(vm);

    if(vm.count("help")){
        cout << desc << endl;
        abort();
    }

    if(!vm.count("input_file")){
        cout << "No input file given. Aborting ..." << endl;
        abort();
    }

    const int first = vm["first"].as<int>();
    const int last = vm["last"].as<int>();
}
