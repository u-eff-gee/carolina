#include <fstream>

using std::ifstream;
using std::ofstream;

#include <iostream>

using std::cout;
using std::endl;

using std::to_string;

#include "code_generation.hpp"
#include "configure_histograms_2d.hpp"

int main(){

    ifstream ifile(code_generation_dir + "/histograms_2d.cpp.in");
    ofstream ofile(code_generation_output_dir + "histograms_2d.cpp");

    unsigned int n_channels = 0;
    for(auto detector: detectors){
        for(auto channel: detector.channels){
            ++n_channels;
        }
    }

    string histogram_name, line;
    vector<string> histogram_names;

    while(getline(ifile, line)){
        if(line.find("@REGISTER_BRANCHES@") != std::string::npos){
            for(auto branch: branches){
                ofile << "\tdouble " << branch.name << "[" << branch.n_leaves << "];\n";
                if(branch.keep_previous){
                    ofile << "\tdouble previous_" << branch.name << "[" << branch.n_dependent_leaves << "];\n";
                }
                ofile << "\ttree->SetBranchAddress(\"" << branch.name << "\", " << branch.name << ");\n";
            }
        } else if(line.find("@CREATE_HISTOGRAMS@") != std::string::npos){
            for(size_t i = 0; i < detector_groups.size(); ++i){
                histogram_name = "coincidence_" + detector_groups[i].name + "_" + detector_groups[i].name;
                ofile << "\tTH2F* " << histogram_name << " = new TH2F(\"" << histogram_name << "\", \"" << histogram_name << "\", " << detector_groups[i].energy_histogram_properties.n_bins << ", " << detector_groups[i].energy_histogram_properties.minimum << ", " << detector_groups[i].energy_histogram_properties.maximum << ", " << detector_groups[i].energy_histogram_properties.n_bins << ", " << detector_groups[i].energy_histogram_properties.minimum << ", " << detector_groups[i].energy_histogram_properties.maximum << ");\n";
                histogram_names.push_back(histogram_name);

                histogram_name = "time_difference_" + detector_groups[i].name + "_" + detector_groups[i].name;
                ofile << "\tTH1F* " << histogram_name << " = new TH1F(\"" << histogram_name << "\", \"" << histogram_name << "\", " << detector_groups[i].time_difference_histogram_properties.n_bins << ", " << detector_groups[i].time_difference_histogram_properties.minimum << ", " << detector_groups[i].time_difference_histogram_properties.maximum << ");\n";
                histogram_names.push_back(histogram_name);

                for(size_t j = i+1; j < detector_groups.size(); ++j){
                    histogram_name = "coincidence_" + detector_groups[i].name + "_" + detector_groups[j].name;
                    ofile << "\tTH2F* " << histogram_name << " = new TH2F(\"" << histogram_name << "\", \"" << histogram_name << "\", " << detector_groups[i].energy_histogram_properties.n_bins << ", " << detector_groups[i].energy_histogram_properties.minimum << ", " << detector_groups[i].energy_histogram_properties.maximum << ", " << detector_groups[j].energy_histogram_properties.n_bins << ", " << detector_groups[j].energy_histogram_properties.minimum << ", " << detector_groups[j].energy_histogram_properties.maximum << ");\n";
                    histogram_names.push_back(histogram_name);

                    histogram_name = "time_difference_" + detector_groups[i].name + "_" + detector_groups[j].name;
                    ofile << "\tTH1F* " << histogram_name << " = new TH1F(\"" << histogram_name << "\", \"" << histogram_name << "\", " << detector_groups[i].time_difference_histogram_properties.n_bins << ", " << detector_groups[i].time_difference_histogram_properties.minimum << ", " << detector_groups[i].time_difference_histogram_properties.maximum << ");\n";
                    histogram_names.push_back(histogram_name);
                }
            }
        } else if(line.find("@TREE_LOOP@") != std::string::npos){
            for(auto detector: detectors){
                size_t n_channel = 0;
                string energy_variable_name;
                string addback_expression = "";


        } else if(line.find("@WRITE_HISTOGRAMS@") != std::string::npos){
            for(auto histogram: histogram_names){
                ofile << "\t" << histogram << "->Write();\n";
            }
        }
        else {
            ofile << line << "\n";
        }
    }

    ifile.close();
    ofile.close();

    cout << "Configured '" << code_generation_dir << "histograms_2d.cpp'." << endl;

}