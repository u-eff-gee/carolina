#include <algorithm>

using std::max;
using std::min;

#include <iostream>

using std::cout;
using std::endl;

#include "TChain.h"
#include "TFile.h"
#include "TH2D.h"

#include "command_line_parser.hpp"
#include "histograms_1d.hpp"
#include "progress_printer.hpp"

size_t coincidence_histogram_index(const DetectorGroup group_0, const DetectorGroup group_1){
    size_t index = 0;
    for(size_t n_g_0 = 0; n_g_0 < groups.size(); ++n_g_0){
        for(size_t n_g_1 = n_g_0; n_g_1 < groups.size(); ++n_g_1){
            if((group_0.name == groups[n_g_0].name && group_1.name == groups[n_g_1].name) || (group_1.name == groups[n_g_0].name && group_0.name == groups[n_g_1].name)){
                return index;
            }
            ++index;
        }
    }

    return index;
}

HistogramProperties common_time_difference_histogram(const DetectorGroup group_0, const DetectorGroup group_1){
    if(group_0.time_difference_histogram_properties.n_bins != group_1.time_difference_histogram_properties.n_bins){
        cout << "Warning: Different number of bins in time-difference histograms of detector groups '" << group_0.name << "' (" << group_0.time_difference_histogram_properties.n_bins << ") and '" << group_1.name << " (" << group_1.time_difference_histogram_properties.n_bins << "). Selecting the larger number." << endl;
    }
    if(group_0.time_difference_histogram_properties.minimum != group_1.time_difference_histogram_properties.minimum){
        cout << "Warning: Different lower limit in time-difference histograms of detector groups '" << group_0.name << "' (" << group_0.time_difference_histogram_properties.minimum << ") and '" << group_1.name << " (" << group_1.time_difference_histogram_properties.minimum << "). Selecting the lower limit." << endl;
    }
    if(group_0.time_difference_histogram_properties.maximum != group_1.time_difference_histogram_properties.maximum){
        cout << "Warning: Different upper limit in time-difference histograms of detector groups '" << group_0.name << "' (" << group_0.time_difference_histogram_properties.maximum << ") and '" << group_1.name << " (" << group_1.time_difference_histogram_properties.maximum << "). Selecting the higher limit." << endl;
    }

    return {
        max(group_0.time_difference_histogram_properties.n_bins, group_1.time_difference_histogram_properties.n_bins),
        min(group_0.time_difference_histogram_properties.minimum, group_1.time_difference_histogram_properties.minimum),
        max(group_0.time_difference_histogram_properties.maximum, group_1.time_difference_histogram_properties.maximum)
    };
}

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

    vector<TH2D*> coincidence_histograms;
    vector<TH1D*> time_difference_histograms;
    string histogram_name;

    for(size_t n_g_0 = 0; n_g_0 < groups.size(); ++n_g_0){
        for(size_t n_g_1 = n_g_0; n_g_1 < groups.size(); ++n_g_1){
            histogram_name = groups[n_g_0].name + "_" + groups[n_g_1].name;
            coincidence_histograms.push_back(
                new TH2D(
                    histogram_name.c_str(),
                    histogram_name.c_str(),
                    groups[n_g_0].energy_histogram_coincidence_properties.n_bins,
                    groups[n_g_0].energy_histogram_coincidence_properties.minimum,
                    groups[n_g_0].energy_histogram_coincidence_properties.maximum,
                    groups[n_g_1].energy_histogram_coincidence_properties.n_bins,
                    groups[n_g_1].energy_histogram_coincidence_properties.minimum,
                    groups[n_g_1].energy_histogram_coincidence_properties.maximum
                )
            );
            histogram_name = histogram_name + "_time_difference";
            HistogramProperties time_difference_histogram_properties = common_time_difference_histogram(groups[n_g_0], groups[n_g_1]);
            time_difference_histograms.push_back(
                new TH1D(
                    histogram_name.c_str(),
                    histogram_name.c_str(),
                    time_difference_histogram_properties.n_bins,
                    time_difference_histogram_properties.minimum,
                    time_difference_histogram_properties.maximum
                )
            );
        }
    }

    size_t histogram_index;

    for(int i = first; i <= last; ++i){
        progress_printer(i - first);

        tree->GetEntry(i);

        for(size_t n_d = 0; n_d < detectors.size(); ++n_d){
            for(size_t n_c = 0; n_c < detectors[n_d].channels.size(); ++n_c){
                detectors[n_d].channels[n_c].calibrate();
            }
            if(detectors[n_d].channels.size() > 1){
                detectors[n_d].addback();
            }
        }

        for(size_t n_d_0 = 0; n_d_0 < detectors.size(); ++n_d_0){
            if(detectors[n_d_0].channels.size() > 1){
                for(size_t n_c_0 = 0; n_c_0 < detectors[n_d_0].channels.size(); ++n_c_0){
                    if(detectors[n_d_0].addback_energies[n_c_0] != 0.){
                        for(size_t n_d_1 = n_d_0+1; n_d_1 < detectors.size(); ++n_d_1){
                            if(detectors[n_d_1].channels.size() > 1){
                                for(size_t n_c_1 = 0; n_c_1 < detectors[n_d_1].channels.size(); ++n_c_1){
                                    if(detectors[n_d_1].addback_energies[n_c_1] != 0. && fabs(detectors[n_d_1].addback_times[n_c_1] - detectors[n_d_0].addback_times[n_c_0]) <= max(detectors[n_d_0].group.coincidence_window_half_width, detectors[n_d_1].group.coincidence_window_half_width)){
                                        histogram_index = coincidence_histogram_index(detectors[n_d_0].group, detectors[n_d_1].group);
                                        coincidence_histograms[histogram_index]->Fill(detectors[n_d_0].addback_energies[n_c_0], detectors[n_d_1].addback_energies[n_c_1]);
                                        time_difference_histograms[histogram_index]->Fill(detectors[n_d_0].addback_times[n_c_0]- detectors[n_d_1].addback_times[n_c_1]);
                                    }
                                }
                            } else{
                                if(detectors[n_d_1].channels[0].energy_calibrated != 0. && fabs(detectors[n_d_1].channels[0].time_calibrated - detectors[n_d_0].addback_times[n_c_0]) <= max(detectors[n_d_0].group.coincidence_window_half_width, detectors[n_d_1].group.coincidence_window_half_width)){
                                    histogram_index = coincidence_histogram_index(detectors[n_d_0].group, detectors[n_d_1].group);
                                    coincidence_histograms[histogram_index]->Fill(detectors[n_d_0].addback_energies[n_c_0], detectors[n_d_1].channels[0].energy_calibrated);
                                    time_difference_histograms[histogram_index]->Fill(detectors[n_d_0].addback_times[n_c_0]- detectors[n_d_1].channels[0].time_calibrated);
                                }
                            }
                        }
                    }
                }
            } else {
                if(detectors[n_d_0].channels[0].energy_calibrated != 0.){
                    for(size_t n_d_1 = n_d_0+1; n_d_1 < detectors.size(); ++n_d_1){
                        if(detectors[n_d_1].channels.size() > 1){
                            for(size_t n_c_1 = 0; n_c_1 < detectors[n_d_1].channels.size(); ++n_c_1){
                                if(detectors[n_d_1].addback_energies[n_c_1] != 0. && fabs(detectors[n_d_1].addback_times[n_c_1] - detectors[n_d_0].channels[0].time_calibrated) <= max(detectors[n_d_0].group.coincidence_window_half_width, detectors[n_d_1].group.coincidence_window_half_width)){
                                    histogram_index = coincidence_histogram_index(detectors[n_d_0].group, detectors[n_d_1].group);
                                    coincidence_histograms[histogram_index]->Fill(detectors[n_d_0].channels[0].time_calibrated, detectors[n_d_1].addback_energies[n_c_1]);
                                    time_difference_histograms[histogram_index]->Fill(detectors[n_d_0].channels[0].time_calibrated- detectors[n_d_1].addback_times[n_c_1]);
                                }
                            }
                        } else{
                            if(detectors[n_d_1].channels[0].energy_calibrated != 0. && fabs(detectors[n_d_1].channels[0].time_calibrated - detectors[n_d_0].channels[0].time_calibrated) <= max(detectors[n_d_0].group.coincidence_window_half_width, detectors[n_d_1].group.coincidence_window_half_width)){
                                histogram_index = coincidence_histogram_index(detectors[n_d_0].group, detectors[n_d_1].group);
                                coincidence_histograms[histogram_index]->Fill(detectors[n_d_0].channels[0].energy_calibrated, detectors[n_d_1].channels[0].energy_calibrated);
                                time_difference_histograms[histogram_index]->Fill(detectors[n_d_0].channels[0].time_calibrated- detectors[n_d_1].channels[0].time_calibrated);
                            }
                        }
                    }   
                }
            }
        }
    }

    TFile output_file(vm["output_file"].as<string>().c_str(), "RECREATE");

    for(auto histogram: coincidence_histograms){
        histogram->Write();
    }
    for(auto histogram: time_difference_histograms){
        histogram->Write();
    }

    output_file.Close();
    cout << "Created output file '" << vm["output_file"].as<string>() << "'." << endl;
}