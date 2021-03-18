#include <fstream>

using std::ofstream;

#include <iostream>

using std::cout;
using std::endl;

#include <string>

using std::string;

#include <vector>

using std::vector;

#include <boost/program_options.hpp>

namespace po = boost::program_options;

#include "TChain.h"

int main(int argc, char* argv[]){

    po::options_description desc;
    desc.add_options()
        ("help", "Produce help message.")
        ("input_file", po::value<vector<string>>(), "Input file name.")
        ("n_threads", po::value<unsigned int>()->default_value(1), "Number of threads (default: 1).")
        ("script", po::value<string>()->default_value("histograms_1d"), "Name of the script to be run in multithreaded mode (default: 'histograms_1d').")
        ("output_file", po::value<string>()->default_value("histograms_1d_multithread_screen.sh"), "Output file name (default: 'histograms_1d_multithread_screen.sh')")
        ;
    po::positional_options_description p;
    p.add("input_file", -1);

    po::variables_map vm;

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

    const unsigned int n_threads = vm["n_threads"].as<unsigned int>();

    TChain *chain = new TChain("clover_array");
    vector<string> input_files = vm["input_file"].as<vector<string>>();
    for(auto input_file: input_files){
        cout << "Adding '" << input_file.c_str() << "' to TChain." << endl;
        chain->Add(input_file.c_str());
    }

    const int entries = chain->GetEntries();
    const int increment = entries / n_threads;
    const int modulo = entries % n_threads;

    ofstream output_file(vm["output_file"].as<string>());
    for(unsigned int i = 0; i < n_threads; ++i){
        output_file << "screen -dm ./"
            << vm["script"].as<string>()
            << " ";
        for(auto input_file: input_files){
            output_file << input_file << " ";
        }

        output_file << "--first " << i*increment + 1 << " "
        << "--last " << (i == n_threads - 1 ? (i+1)*increment + modulo : (i+1)*increment) << " "
        << "--output_file output_" << i << ".root"
        << "\n";
    }

    cout << "Generated shell script '" << vm["output_file"].as<string>() << "' which runs '" << vm["script"].as<string>() << "' on " << n_threads << " threads." << endl;
    cout << "To execute, type:" << endl;
    cout << "\t./" << vm["output_file"].as<string>() << endl;
    cout << "You may have to make the shell script executable first:" << endl;
    cout << "\tchmod +x " << vm["output_file"].as<string>() << endl;

    output_file.close();
}