#include <fstream>

using std::ifstream;
using std::ofstream;

#include <iostream>

using std::cout;
using std::endl;

using std::to_string;

#include "code_generation.hpp"
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
                    ofile << "\tdouble previous_" << branch.name << "[" << branch.n_dependent_leaves << "];\n";
                }
                ofile << "\ttree->SetBranchAddress(\"" << branch.name << "\", " << branch.name << ");\n";
            }
        } else if(line.find("@CREATE_HISTOGRAMS@") != std::string::npos){
            for(auto detector: detectors){
                if(detector.channels.size() > 1){
                    ofile << "\tdouble " << detector.name << "_energies[" << detector.channels.size() << "];\n";
                    ofile << "\tdouble " << detector.name << "_addback_energies[" << detector.channels.size() << "];\n";
                    ofile << "\tdouble " << detector.name << "_addback_skip[" << detector.channels.size() << "];\n";
                    ofile << "\tdouble " << detector.name << "_times[" << detector.channels.size() << "];\n";
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

                    histogram_name = detector.name + "_" + channel.name + "_timestamp_difference";
                    ofile << "\tTH1F* " << histogram_name << " = new TH1F(\"" << histogram_name << "\", \"" << histogram_name << "\", " << detector.timestamp_difference_histogram_properties.n_bins << ", " << detector.timestamp_difference_histogram_properties.minimum << ", " << detector.timestamp_difference_histogram_properties.maximum << ");\n";
                    histogram_names.push_back(histogram_name);
                }
            }
        } else if(line.find("@TREE_LOOP@") != std::string::npos){
            ofile << "\t\tdouble *maximum_energy_deposition;\n";

            for(auto detector: detectors){
                size_t n_channel = 0;
                string energy_variable_name, time_variable_name;
                string addback_expression = "";

                if(detector.channels.size() > 1){
                    for(auto channel: detector.channels){
                        energy_variable_name = detector.name + "_energies[" + to_string(n_channel) + "]";
                        ofile << "\t\tif( !isnan(" << channel.energy_branch_name << "[" << channel.energy_branch_index << "])){\n";
                        ofile << "\t\t\t" << energy_variable_name << " = " << channel.energy_calibration_parameters[0] << " + " << channel.energy_calibration_parameters[1] << " * " << channel.energy_branch_name << "[" << channel.energy_branch_index << "];\n";

                        histogram_name = detector.name + "_" + channel.name;
                        ofile << "\t\t\t" << histogram_name << "->Fill(" << energy_variable_name << ");\n";

                        histogram_name = detector.name + "_" + channel.name + "_raw";
                        ofile << "\t\t\t" << histogram_name << "->Fill(" << channel.energy_branch_name << "[" << channel.energy_branch_index << "]);\n";

                        histogram_name = detector.name + "_" + channel.name + "_timestamp_difference";
                        ofile << "\t\t\t" << histogram_name << "->Fill(" << channel.timestamp_calibration_parameters[1] << " * (" << channel.timestamp_branch_name << "[0] - previous_" << channel.timestamp_branch_name << "[" << channel.timestamp_branch_index << "]));\n";
                        ofile << "\t\t\tprevious_" << channel.timestamp_branch_name << "[" << channel.timestamp_branch_index << "] = " << channel.timestamp_branch_name << "[0];\n";

                        ofile << "\t\t}\n\t\telse{ " << energy_variable_name << " = 0.; };\n";

                        time_variable_name = detector.name + "_times[" + to_string(n_channel) + "]";
                        ofile << "\t\t" << time_variable_name << " = " << channel.time_calibration_parameters[1] << " * " << channel.time_branch_name << "[" << channel.time_branch_index << "];\n";

                        ++n_channel;
                    }

                    for(size_t n_c = 0; n_c < detector.channels.size(); ++n_c){
                        ofile << "\t\t" << detector.name << "_addback_energies[" << n_c << "] = 0.;\n";
                        ofile << "\t\t" << detector.name << "_addback_skip[" << n_c << "] = false;\n";
                    }

                    for(size_t n_c_0 = 0; n_c_0 < detector.channels.size(); ++n_c_0){
                        ofile << "\t\tif(!" << detector.name << "_addback_skip[" << n_c_0 << "]){\n";
                        ofile << "\t\t\t" << detector.name << "_addback_energies[" << n_c_0 << "] = " << detector.name << "_energies[" << n_c_0 << "];\n";
                        for(size_t n_c_1 = n_c_0+1; n_c_1 < detector.channels.size(); ++n_c_1){
                            ofile << "\t\t\tif(";
                            ofile << detector.channel_coincidence_window.first << " < " << detector.name + "_times[" << n_c_0 << "] - " << detector.name + "_times[" << n_c_1 << "] && " << detector.name + "_times[" << n_c_0 << "] - " << detector.name + "_times[" << n_c_1 << "] < " << detector.channel_coincidence_window.second << " && !" << detector.name << "_addback_skip[" << n_c_1 << "]";
                            ofile << "){\n";
                            ofile << "\t\t\t\t" << detector.name << "_addback_energies[" << n_c_0 << "] += " << detector.name << "_energies[" << n_c_1 << "];\n";
                            ofile << "\t\t\t\t" << detector.name << "_addback_skip[" << n_c_1 << "] = true;\n";
                            ofile << "\t\t\t}\n";
                        }
                        ofile << "\t\t}\n";
                    }

                    for(size_t n_c = 0; n_c < detector.channels.size(); ++n_c){
                        ofile << "\t\tif(" << detector.name << "_addback_energies[" << n_c << "] != 0.){\n";
                        ofile << "\t\t\t" << detector.name << "_addback->Fill(" << detector.name << "_addback_energies[" << n_c << "]);\n";
                        ofile << "\t\t}\n";
                    }
                } else{
                    for(auto channel: detector.channels){
                        ofile << "\t\tif( !isnan(" << channel.energy_branch_name << "[" << channel.energy_branch_index << "])){\n";
                        histogram_name = detector.name + "_" + channel.name;
                        ofile << "\t\t\t" << histogram_name << "->Fill(" << channel.energy_calibration_parameters[0] << " + " << channel.energy_calibration_parameters[1] << " * " << channel.energy_branch_name << "[" << channel.energy_branch_index << "]);\n";

                        histogram_name = detector.name + "_" + channel.name + "_raw";
                        ofile << "\t\t\t" << histogram_name << "->Fill(" << channel.energy_branch_name << "[" << channel.energy_branch_index << "]);\n";

                        histogram_name = detector.name + "_" + channel.name + "_timestamp_difference";
                        ofile << "\t\t\t" << histogram_name << "->Fill(" << channel.timestamp_calibration_parameters[1] << " * (" << channel.timestamp_branch_name << "[0] - previous_" << channel.timestamp_branch_name << "[" << channel.timestamp_branch_index << "]));\n";
                        ofile << "\t\t\tprevious_" << channel.timestamp_branch_name << "[" << channel.timestamp_branch_index << "] = " << channel.timestamp_branch_name << "[0];\n";

                        ofile << "\t\t}\n";
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

    cout << "Configured '" << code_generation_dir << "histograms_1d.cpp'." << endl;

}