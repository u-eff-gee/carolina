#include <fstream>

using std::ifstream;
using std::ofstream;

#include <iostream>

using std::cout;
using std::endl;

using std::to_string;

#include "configure_histograms_1d.hpp"

int main(){

    ifstream ifile(code_generation_dir + "/histograms_1d.cpp.in");
    ofstream ofile(code_generation_output_dir + "histograms_1d.cpp");

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
                    ofile << "\tdouble previous_" << branch.name << "[" << branch.n_leaves << "];\n";
                }
                ofile << "\ttree->SetBranchAddress(\"" << branch.name << "\", " << branch.name << ");\n";
            }
        } else if(line.find("@CREATE_HISTOGRAMS@") != std::string::npos){
            for(auto detector: detectors){
                if(detector.channels.size() > 1){
                    ofile << "\tdouble " << detector.name << "_energies[" << detector.channels.size() << "];\n";
                    histogram_name = detector.name + "_addback";
                    ofile << "\tTH1F* " << histogram_name << " = new TH1F(\"" << histogram_name << "\", \"" << histogram_name << "\", " << detector.energy_histogram_properties.n_bins << ", " << detector.energy_histogram_properties.minimum << ", " << detector.energy_histogram_properties.maximum << ");\n";
                    histogram_names.push_back(histogram_name);
                }
                for(auto channel: detector.channels){
                    histogram_name = detector.name + "_" + channel.name;
                    ofile << "\tTH1F* " << histogram_name << " = new TH1F(\"" << histogram_name << "\", \"" << histogram_name << "\", " << detector.energy_histogram_properties.n_bins << ", " << detector.energy_histogram_properties.minimum << ", " << detector.energy_histogram_properties.maximum << ");\n";
                    histogram_names.push_back(histogram_name);

                    histogram_name = detector.name + "_" + channel.name + "_raw";
                    ofile << "\tTH1F* " << histogram_name << " = new TH1F(\"" << histogram_name << "\", \"" << histogram_name << "\", " << channel.energy_raw_histogram_properties.n_bins << ", " << channel.energy_raw_histogram_properties.minimum << ", " << channel.energy_raw_histogram_properties.maximum << ");\n";
                    histogram_names.push_back(histogram_name);

                    histogram_name = "timestamp_" + detector.name + "_" + channel.name;
                    ofile << "\tTH1F* " << histogram_name << " = new TH1F(\"" << histogram_name << "\", \"" << histogram_name << "\", " << detector.timestamp_difference_histogram_properties.n_bins << ", " << detector.timestamp_difference_histogram_properties.minimum << ", " << detector.timestamp_difference_histogram_properties.maximum << ");\n";
                    histogram_names.push_back(histogram_name);
                }
            }
        } else if(line.find("@TREE_LOOP@") != std::string::npos){
            for(auto detector: detectors){
                size_t n_channel = 0;
                string energy_variable_name;
                string addback_expression = "";

                if(detector.channels.size() > 1){
                    for(auto channel: detector.channels){
                        energy_variable_name = detector.name + "_energies[" + to_string(n_channel) + "]";
                        ofile << "\tif( !isnan(" << channel.energy_branch_name << "[" << channel.energy_branch_index << "])){\n";
                        ofile << "\t\t" << energy_variable_name << " = " << channel.energy_calibration_parameters[0] << " + " << channel.energy_calibration_parameters[1] << " * " << channel.energy_branch_name << "[" << channel.energy_branch_index << "];\n";

                        histogram_name = detector.name + "_" + channel.name;
                        ofile << "\t\t" << histogram_name << "->Fill(" << energy_variable_name << ");\n";

                        histogram_name = detector.name + "_" + channel.name + "_raw";
                        ofile << "\t\t" << histogram_name << "->Fill(" << channel.energy_branch_name << "[" << channel.energy_branch_index << "]);\n";

                        histogram_name = "timestamp_" + detector.name + "_" + channel.name;
                        ofile << "\t\t" << histogram_name << "->Fill(" << channel.timestamp_calibration_parameters[1] << " * (" << channel.timestamp_branch_name << "[0] - previous_" << channel.timestamp_branch_name << "[0]));\n";
                        ofile << "\t\tprevious_" << channel.timestamp_branch_name << "[0] = " << channel.timestamp_branch_name << "[0];\n";

                        ofile << "\t}\n\telse{ " << energy_variable_name << " = 0.; };\n";

                        if(n_channel > 0){
                            addback_expression = addback_expression + " + ";
                        }
                        addback_expression = addback_expression + energy_variable_name;
                        ++n_channel;
                    }
                    ofile << "\t" << detector.name << "_addback->Fill(" << addback_expression << ");\n";
                } else{
                    for(auto channel: detector.channels){
                        ofile << "\tif( !isnan(" << channel.energy_branch_name << "[" << channel.energy_branch_index << "])){\n";
                        histogram_name = detector.name + "_" + channel.name;
                        ofile << "\t\t" << histogram_name << "->Fill(" << channel.energy_calibration_parameters[0] << " + " << channel.energy_calibration_parameters[1] << " * " << channel.energy_branch_name << "[" << channel.energy_branch_index << "]);\n";

                        histogram_name = detector.name + "_" + channel.name + "_raw";
                        ofile << "\t\t" << histogram_name << "->Fill(" << channel.energy_branch_name << "[" << channel.energy_branch_index << "]);\n";

                        histogram_name = "timestamp_" + detector.name + "_" + channel.name;
                        ofile << "\t\t" << histogram_name << "->Fill(" << channel.timestamp_calibration_parameters[1] << " * (" << channel.timestamp_branch_name << "[0] - previous_" << channel.timestamp_branch_name << "[0]));\n";
                        ofile << "\t\tprevious_" << channel.timestamp_branch_name << "[0] = " << channel.timestamp_branch_name << "[0];\n";

                        ofile << "\t}\n";
                    }
                }
            }
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

}