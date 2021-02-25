#include <iostream>

using std::cout;
using std::endl;

#include <string>

using std::string;
using std::to_string;

#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "TTree.h"

#include "command_line_parser.hpp"
#include "detectors.hpp"
#include "progress_printer.hpp"

int main(int argc, char* argv[]){

    CommandLineParser command_line_parser;
    command_line_parser(argc, argv);
    po::variables_map vm = command_line_parser.get_variables_map();

    TChain *tree = new TChain("clover_array");
    vector<string> input_files = vm["input_file"].as<vector<string>>();
    for(auto input_file: input_files){
        cout << "Adding '" << input_file.c_str() << "' to TChain." << endl;
        tree->Add(input_file.c_str());
    }

    const int first = vm["first"].as<int>();
    const int last = vm["last"].as<int>() == 0 ? tree->GetEntries() : vm["last"].as<int>();
    ProgressPrinter progress_printer(last-first+1, 0.001);

    tree->SetBranchAddress("amplitude_clover_90", amplitude_clover_90);
    tree->SetBranchAddress("amplitude_clover_135", amplitude_clover_135);

    vector<TH1D> channel_histograms;
    vector<TH1D> addback_histograms;

    string histogram_name;
    for(auto detector: detectors){
        for(auto channel: detector.channels){
            histogram_name = detector.name + "_" + channel.name;
            channel_histograms.push_back(
                TH1D(histogram_name.c_str(), histogram_name.c_str(), 10000, 0.5, 10000.5)
            );
            histogram_name = "addback_" + detector.name + "_" + channel.name;
        }
        addback_histograms.push_back(
            TH1D(histogram_name.c_str(), histogram_name.c_str(), 10000, 0.5, 10000.5)
        );
    }

    double energy;
    double energy_addback;
    int channel_index, detector_index;

    for(int i = first; i <= last; ++i){
        progress_printer(i - first);
        tree->GetEntry(i);

        channel_index = 0;
        detector_index = 0;

        for(auto detector: detectors){
            energy_addback = 0.;
            for(auto channel: detector.channels){
                energy = channel.calibrate();
                energy_addback += energy;
                channel_histograms[channel_index].Fill(energy);
                ++channel_index;
            }
            addback_histograms[detector_index].Fill(energy_addback);
            ++detector_index;
        }
    }

    TFile output_file(vm["output_file"].as<string>().c_str(), "RECREATE");

    for(auto hist: channel_histograms){
        hist.Write();
    }
    for(auto hist: addback_histograms){
        hist.Write();
    }

    output_file.Close();
}
