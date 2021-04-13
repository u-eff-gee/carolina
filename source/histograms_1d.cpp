#include <iostream>

using std::cout;
using std::endl;

#include "TChain.h"
#include "TFile.h"
#include "TH1D.h"

#include "command_line_parser.hpp"
#include "histograms_1d.hpp"
#include "progress_printer.hpp"

int main(int argc, char** argv){
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
	    return 0;
    }

    ProgressPrinter progress_printer(last-first+1, 0.001);

    for(size_t i = 0; i < modules.size(); ++i){
        modules[i].register_branches(tree);
    }

    vector<TH1D*> addback_histograms;
    vector<vector<TH1D*>> energy_histograms;
    string histogram_name;

    for(size_t n_d = 0; n_d < detectors.size(); ++n_d){
        if(detectors[n_d].channels.size() > 1){
            histogram_name = detectors[n_d].name + "_addback";
            addback_histograms.push_back(new TH1D(histogram_name.c_str(), histogram_name.c_str(), detectors[n_d].group.energy_histogram_properties.n_bins, detectors[n_d].group.energy_histogram_properties.minimum, detectors[n_d].group.energy_histogram_properties.maximum));
        } else {
            addback_histograms.push_back(nullptr);
        }
        energy_histograms.push_back(vector<TH1D*>());
        for(size_t n_c = 0; n_c < detectors[n_d].channels.size(); ++n_c){
            histogram_name = detectors[n_d].name + "_" + detectors[n_d].channels[n_c].name;
            energy_histograms[n_d].push_back(new TH1D(histogram_name.c_str(), histogram_name.c_str(), detectors[n_d].group.energy_histogram_properties.n_bins, detectors[n_d].group.energy_histogram_properties.minimum, detectors[n_d].group.energy_histogram_properties.maximum));
        }
    }

    size_t histogram_index = 0;

    for(int i = first; i <= last; ++i){
        progress_printer(i - first);

        tree->GetEntry(i);

        for(size_t n_d = 0; n_d < detectors.size(); ++n_d){
            for(size_t n_c = 0; n_c < detectors[n_d].channels.size(); ++n_c){
                detectors[n_d].channels[n_c].calibrate();
                if(detectors[n_d].channels[n_c].energy_calibrated != 0.){
                    energy_histograms[n_d][n_c]->Fill(detectors[n_d].channels[n_c].energy_calibrated);
                }
            }
            if(detectors[n_d].channels.size() > 1){
                detectors[n_d].addback();
                for(size_t n_c = 0; n_c < detectors[n_d].channels.size(); ++n_c){
                    if(detectors[n_d].addback_energies[n_c] != 0.){
                        addback_histograms[n_d]->Fill(detectors[n_d].addback_energies[n_c]);
                    }
                }
            }
        }
    }

    TFile output_file(vm["output_file"].as<string>().c_str(), "RECREATE");

    for(size_t n_d = 0; n_d < detectors.size(); ++n_d){
        if(detectors[n_d].channels.size() > 1){
            addback_histograms[n_d]->Write();
        }
        for(size_t n_c = 0; n_c < detectors[n_d].channels.size(); ++n_c){
            energy_histograms[n_d][n_c]->Write();
        }
    }

    output_file.Close();
    cout << "Created output file '" << vm["output_file"].as<string>() << "'." << endl;
}