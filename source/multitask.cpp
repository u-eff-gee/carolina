#include <fstream>

using std::ofstream;

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

int main(int argc, char* argv[]){

    po::options_description desc("Create a shell script to run an analysis script on a ROOT TTree in multitasked mode, using screen or slurm. As compared to true multithreading, multitasking means that the same analysis script will be launched multiple times to work on subsets of the TTree's entries. In particular, each instance of the analysis script will use its own memory.");
    desc.add_options()
        ("help", "Produce help message.")
        ("tool", po::value<string>()->default_value("screen"), "Tool for multitasking [options: 'screen' (default), slurm].")
        ("input_file", po::value<vector<string>>(), "Input file name.")
        ("n_tasks", po::value<unsigned int>()->default_value(1), "Number of tasks (default: 1).")
        ("script", po::value<string>()->default_value("histograms_1d"), "Name of the script to be run in multitasking mode (default: 'histograms_1d').")
        ("output_file", po::value<string>()->default_value("default"), "Output file name (default: 'multitask_SCRIPT_TOOL.sh', where SCRIPT is the name of the analysis script and TOOL is the multitasking tool).")
        ("tree", po::value<string>()->default_value("clover_array"), "TTree name (default: 'clover_array')");
        ;
    po::positional_options_description p;
    p.add("input_file", -1);

    po::variables_map vm;

    po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
    po::notify(vm);

    if(vm.count("help")){
        cout << desc << endl;
        return 0;
    }

    if(!vm.count("input_file")){
        cout << "No input file given. Aborting ..." << endl;
        return 1;
    }

    string tool;
    if(vm["tool"].as<string>() == "screen"){
        tool = "screen";
    } else if(vm["tool"].as<string>() == "slurm"){
        tool = "slurm";
    } else {
        cout << "Unrecognized tool '" << vm["tool"].as<string>() << "'. The available options are 'screen' or 'slurm'. Aborting ..." << endl;
        return 1;
    }

    const unsigned int n_tasks = vm["n_tasks"].as<unsigned int>();

    TChain *chain = new TChain(vm["tree"].as<string>().c_str());
    vector<string> input_files = vm["input_file"].as<vector<string>>();
    for(auto input_file: input_files){
        cout << "Adding '" << input_file.c_str() << "' to TChain." << endl;
        chain->Add(input_file.c_str());
    }

    const int entries = chain->GetEntries();
    const int increment = entries / n_tasks;
    const int modulo = entries % n_tasks;

    string output_file_name = vm["output_file"].as<string>();
    if(output_file_name == "default"){
        output_file_name = "multitask_" + vm["script"].as<string>() + "_" + tool + ".sh";
    }

    if(tool == "screen"){
	    ofstream output_file(output_file_name);
	    output_file << "#!/bin/bash\n";
	    for(unsigned int i = 0; i < n_tasks; ++i){
		output_file << "screen -dm ./";
		output_file << vm["script"].as<string>() << " ";
		for(auto input_file: input_files){
		    output_file << input_file << " ";
		}

		output_file << "--tree " << vm["tree"].as<string>() << " "
        << "--first " << i*increment + 1 << " "
		<< "--last " << (i == n_tasks - 1 ? (i+1)*increment + modulo : (i+1)*increment) << " "
		<< "--output_file output_" << i << ".root"
		<< "\n";
	    }

	    cout << "Generated shell script '" << output_file_name << "' which runs '" << vm["script"].as<string>() << "' on " << n_tasks << " tasks." << endl;
	    cout << "To execute, type:" << endl;
	    cout << "\t./" << output_file_name << endl;
	    cout << "You may have to make the shell script executable first:" << endl;
	    cout << "\tchmod +x " << vm["output_file"].as<string>() << endl;

	    output_file.close();
    } else if(tool == "slurm"){
        ofstream output_file(output_file_name);
        output_file << "#!/bin/bash\n";
        output_file << "#SBATCH -a 0-" << n_tasks-1 << "\n";
        output_file << "bash multitask_" << vm["script"].as<string>() + "_" + tool + "_${SLURM_ARRAY_TASK_ID}.sh" << "\n";
        output_file.close();
        cout << "Generated shell script '" << output_file_name << "' which runs '" << vm["script"].as<string>() << "' on " << n_tasks << " tasks." << endl;
        cout << "To execute, type:" << endl;
        cout << "\tsbatch " << output_file_name << endl;
        cout << "You may have to make the shell script executable first:" << endl;
        cout << "\tchmod +x " << output_file_name << endl;
        cout << "The shell script will run the following input files, which represent multiple calls to '" << vm["script"].as<string>() << ":" << endl;

	    for(unsigned int i = 0; i < n_tasks; ++i){
        	output_file_name = "multitask_" + vm["script"].as<string>() + "_" + tool + "_" + to_string(i) + ".sh";
            ofstream output_file(output_file_name);
            output_file << "./";
            output_file << vm["script"].as<string>() << " ";
            for(auto input_file: input_files){
                output_file << input_file << " ";
            }

            output_file << "--tree " << vm["tree"].as<string>() << " "
            << "--first " << i*increment + 1 << " "
            << "--last " << (i == n_tasks - 1 ? (i+1)*increment + modulo : (i+1)*increment) << " "
            << "--output_file output_" << i << ".root"
            << "\n";
            output_file.close();
            cout << "\t" << output_file_name << endl;
	    }
    }
}
