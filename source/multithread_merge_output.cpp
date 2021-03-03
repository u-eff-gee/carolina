#include <fstream>

using std::ofstream;

#include <iostream>

using std::cout;
using std::endl;

#include <sstream>

using std::stringstream;

#include <string>

using std::string;

#include <vector>

using std::vector;

#include <boost/program_options.hpp>

namespace po = boost::program_options;

#include "TCollection.h"
#include "TH1.h"
#include "TFile.h"
#include "TKey.h"
#include "TList.h"

/**
 * This script is strongly inspired by the 'hadd' example of ROOT.
 */

int main(int argc, char* argv[]){

    po::options_description desc;
    desc.add_options()
        ("help", "Produce help message.")
        ("input_file", po::value<vector<string>>(), "Input file name.")
        ("output_file", po::value<string>()->default_value("output.root"), "Output file name (default: 'output.root')")
        ;
    po::positional_options_description p;
    p.add("input_file", -1);

    po::variables_map vm;

    po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
    po::notify(vm);

    if(vm.count("help") || !vm.count("input_file")){
        cout << desc << endl;
        abort();
    }

    vector<string> input_files = vm["input_file"].as<vector<string>>();
    if(input_files.size() < 2){
        cout << "Only one or less input files given. Aborting ..." << endl;
        abort();
    }

    TFile *output_file = TFile::Open(vm["output_file"].as<string>().c_str(), "RECREATE");

    TFile *first_input_file = TFile::Open(input_files[0].c_str());
    TIter next_key(gDirectory->GetListOfKeys());
    TKey *key;

    /**
     * The following is a loop over all keys that were found in the first ROOT file.
     * If the key is a TH1 histogram, the code will look for TH1 histograms with the same name
     * in all other input files, and them to the first file, and store the sum spectrum in the 
     * output file.
     */
    while((key=(TKey*) next_key())){
        first_input_file->cd();
        TObject *obj = key->ReadObj();
        if(obj->IsA()->InheritsFrom(TH1::Class())){
            cout << "Trying to find TH1 histograms with the name '" << obj->GetName() << "' in all input files and merge them ..." << endl;
            TH1 *first_histogram = (TH1*) obj;

            for(size_t i = 1; i < input_files.size(); ++i){
                TFile* next_input_file = TFile::Open(input_files[i].c_str());
                TKey* key2 = (TKey*) gDirectory->GetListOfKeys()->FindObject(first_histogram->GetName());
                if(key2){
                    TH1 *h2 = (TH1*) key2->ReadObj();
                    first_histogram->Add(h2);
                    delete h2;
                } else {
                    cout << "Warning: Could not find a histogram with the name '" << first_histogram->GetName() << "' in input file '" << next_input_file->GetName() << "'." << endl;
                }
            }
        }

        if(obj){
            output_file->cd();
            obj->Write(key->GetName());
        }
    }

    output_file->Close();
    cout << "Wrote output file '" << vm["output_file"].as<string>() << "'." << endl;

}