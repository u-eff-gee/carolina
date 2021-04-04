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

#include "TFile.h"
#include "TH1.h"
#include "TKey.h"

string trim_input_file_name(const string input_file_name){
    size_t root_file_suffix_position = input_file_name.find(".root");

    if(root_file_suffix_position == std::string::npos){
        return input_file_name;
    }

    return input_file_name.substr(0, root_file_suffix_position);
}

void write_histogram_single_column(TH1 *histogram, const string output_file_name){

    ofstream output_file(output_file_name);
    if(!output_file.is_open()){
        cout << "Error: File '" << output_file_name << "' could not be opened. Aborting ..." << endl;
        abort();
    }

    for(int i = 1; i <= histogram->GetNbinsX(); ++i){
        output_file << histogram->GetBinContent(i) << "\n";
    }

    output_file.close();
}

void write_histogram_two_column(TH1 *histogram, const string separator, const string output_file_name){

    ofstream output_file(output_file_name);
    if(!output_file.is_open()){
        cout << "Error: File '" << output_file_name << "' could not be opened. Aborting ..." << endl;
        abort();
    }

    for(int i = 1; i <= histogram->GetNbinsX(); ++i){
        output_file << histogram->GetBinCenter(i) << separator << histogram->GetBinContent(i) << "\n";
    }

    output_file.close();
}

int main(int argc, char* argv[]){

    po::variables_map vm;
    po::options_description desc("Write the bin centers and bin contents of all TH1 histograms in a ROOT file to separate single- or two-column text files.");
    po::positional_options_description p;
    desc.add_options()
        ("help", "Produce help message.")
        ("input_file", po::value<vector<string>>(), "Input file names.")
        ("rebin", po::value<unsigned int>()->default_value(1), "Before writing, rebin the spectrum using TH1::Rebin(). The parameter of the 'rebin' option corresponds to the 'ngroup' parameter of TH1::Rebin(). Default: 1, i.e. do not rebin.")
        ("output_directory", po::value<string>()->default_value(""), "Output directory. Default: Empty string, i.e. 'here'.")
        ("separator", po::value<string>()->default_value(""), "Separator between 'bin center' and 'bin content' columns. The default is an empty string, indicating that only the bin contents should be written.");
    p.add("input_file", -1);

    po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << desc << "\n";
        return 0;
    }

    if(!vm.count("input_file")){
        cout << "No input file given. Aborting ..." << endl;
        return 0;
    }

    const vector<string> input_files = vm["input_file"].as<vector<string>>();
    const string separator = vm["separator"].as<string>();

    string output_file_name;
    string prefix;

    for(auto input_file: input_files){
        TFile file(input_file.c_str(), "READ");
        TIter next_key(file.GetListOfKeys());
        prefix = trim_input_file_name(input_file) + "_";

        TKey* key;
        while(key = (TKey*) next_key()){
            TObject *obj = key->ReadObj();
            if(obj->IsA()->InheritsFrom(TH1::Class())){
                TH1* histogram = (TH1*) obj;
                if(vm["rebin"].as<unsigned int>() != 1){
                    histogram->Rebin(vm["rebin"].as<unsigned int>());
                }
                output_file_name = vm["output_directory"].as<string>() + prefix + key->GetName() + ".txt";
                if(separator == ""){
                    write_histogram_single_column(histogram, output_file_name);
                } else {
                    write_histogram_two_column(histogram, separator, output_file_name);
                }
                cout << "Created file '" << output_file_name << "'." << endl;
                delete histogram;
            }
        }
    }
}