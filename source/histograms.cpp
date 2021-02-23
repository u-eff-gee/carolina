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

#include "detectors.hpp"
#include "progress_printer.hpp"


int main(int argc, char* argv[]){

    if(argc < 3){
    	cout << "Usage: histograms INPUT_FILE_NAME_1 INPUT_FILE_NAME_2 ... OUTPUT_FILE_NAME" << endl;
	abort();
    }

    TChain *tree = new TChain("clover_array");
    for(int i = 1; i < argc-1; ++i){
        tree->Add(argv[i]);
    }

    const int entries = tree->GetEntries();
    ProgressPrinter progress_printer(entries, 0.001);

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

    for(int i = 1; i <= entries; ++i){
        progress_printer(i);
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

    TFile output_file(argv[argc-1], "RECREATE");

    for(auto hist: channel_histograms){
        hist.Write();
    }
    for(auto hist: addback_histograms){
        hist.Write();
    }

    output_file.Close();
}
