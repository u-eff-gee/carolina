#include <iostream>

using std::cout;
using std::endl;

#include <memory>

using std::make_shared;
using std::shared_ptr;

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

    if(first > last){
        cout << "Error: first entry (" << first << ") is larger or equal to last entry (" << last << "). Aborting ..." << endl;
	abort();
    }

    ProgressPrinter progress_printer(last-first+1, 0.001);

    for(auto branch: branches){
	    tree->SetBranchAddress(branch.first.c_str(), branch.second);
    }

    vector<vector<shared_ptr<Detector>>> groups;
    for(size_t i = 0; i < detector_groups.size(); ++i){
        groups.push_back(vector<shared_ptr<Detector>>());
        for(auto detector: detectors){
            if(detector.group.name == detector_groups[i].name){
                groups[i].push_back(make_shared<Detector>(detector));
            }
        }
    }

    for(size_t i = 0; i < groups.size(); ++i){
        if(groups[i].size()){
            cout << "Detector Group: " << groups[i][0]->group.name << endl;
            for(auto detector: groups[i]){
                cout << "\t" << detector->name << endl;
            }
        }
    }
    cout << endl;

    vector<TH1D> channel_histograms;
    vector<TH1D> addback_histograms;

    string histogram_name;
    for(auto detector: detectors){
        for(auto channel: detector.channels){
            histogram_name = detector.name + "_" + channel.name;
            channel_histograms.push_back(
                TH1D(histogram_name.c_str(), histogram_name.c_str(), channel.energy_histogram_properties.n_bins, channel.energy_histogram_properties.minimum, channel.energy_histogram_properties.maximum)
            );
        }
        if(detector.channels.size() > 1){
            histogram_name = "addback_" + detector.name;
            addback_histograms.push_back(
                TH1D(histogram_name.c_str(), histogram_name.c_str(), detector.channels[0].energy_histogram_properties.n_bins, detector.channels[0].energy_histogram_properties.minimum, detector.channels[0].energy_histogram_properties.maximum)
            );
        }
    }

    double energy;
    double energy_addback;
    int addback_index, channel_index, detector_index;

    for(int i = first; i <= last; ++i){
        progress_printer(i - first);
        tree->GetEntry(i);

        addback_index = 0;
        channel_index = 0;
        detector_index = 0;

        for(auto detector: detectors){
            if(detector.channels.size() > 1){
                energy_addback = 0.;
                for(auto channel: detector.channels){
                    energy = channel.calibrate();
                    energy_addback += energy;
                    channel_histograms[channel_index].Fill(energy);
                    ++channel_index;
                }
                addback_histograms[detector_index].Fill(energy_addback);
                ++addback_index;
            } else {
                energy = detector.channels[0].calibrate();
                channel_histograms[channel_index].Fill(energy);
                ++channel_index;
            }
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
    cout << "Created output file '" << vm["output_file"].as<string>() << "'." << endl;
}
