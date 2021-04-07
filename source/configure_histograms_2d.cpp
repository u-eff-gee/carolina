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

    bool histogram_name_matched = false;
    string histogram_name, line;
    vector<string> histogram_names;

    while(getline(ifile, line)){
        if(line.find("@REGISTER_BRANCHES@") != std::string::npos){

            ofile << branch_registration(branches, "\t");

        } else if(line.find("@CREATE_HISTOGRAMS@") != std::string::npos){
            ofile << "\tdouble energy_0, energy_1, time_0, time_1;\n";
            ofile << "\tint maximum_energy_deposition_index;\n";
            for(auto detector: detectors){
                if(detector.channels.size() > 1){
                    ofile << "\tdouble " << detector.name << "_energies[" << detector.channels.size() << "];\n";
                }
            }
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
            for(size_t n_d_0 = 0; n_d_0 < detectors.size()-1; ++n_d_0){
                ofile << "\tif(";

                for(size_t n_c_0 = 0; n_c_0 < detectors[n_d_0].channels.size()-1; ++n_c_0){
                    ofile << "!isnan(" << detectors[n_d_0].channels[n_c_0].energy_branch_name << "[" << detectors[n_d_0].channels[n_c_0].energy_branch_index << "]) || ";
                }
                ofile << "!isnan(" << detectors[n_d_0].channels[detectors[n_d_0].channels.size()-1].energy_branch_name << "[" << detectors[n_d_0].channels[detectors[n_d_0].channels.size()-1].energy_branch_index << "])){\n";

                for(size_t n_d_1 = n_d_0 + 1; n_d_1 < detectors.size(); ++n_d_1){
                    ofile << "\t\tif(";

                    for(size_t n_c_1 = 0; n_c_1 < detectors[n_d_1].channels.size()-1; ++n_c_1){
                        ofile << "!isnan(" << detectors[n_d_1].channels[n_c_1].energy_branch_name << "[" << detectors[n_d_1].channels[n_c_1].energy_branch_index << "]) || ";
                    }
                    ofile << "!isnan(" << detectors[n_d_1].channels[detectors[n_d_1].channels.size()-1].energy_branch_name << "[" << detectors[n_d_1].channels[detectors[n_d_1].channels.size()-1].energy_branch_index << "])){\n";

                    if(detectors[n_d_0].channels.size() > 1){
                        ofile << "\t\t\ttime_0 = " << detectors[n_d_0].channels[0].time_branch_name << "[" << detectors[n_d_0].channels[0].time_branch_index << "];\n";
                        ofile << "\t\t\tmaximum_energy_deposition_index = 0;\n";
                        for(size_t n_c_0 = 0; n_c_0 < detectors[n_d_0].channels.size(); ++n_c_0){
                            ofile << "\t\t\t" << detectors[n_d_0].name << "_energies[" << to_string(n_c_0) << "] = isnan(" << detectors[n_d_0].channels[n_c_0].energy_branch_name << "[" << detectors[n_d_0].channels[n_c_0].energy_branch_index << "]) ? 0. : " << detectors[n_d_0].channels[n_c_0].energy_calibration_parameters[0] << " + " << detectors[n_d_0].channels[n_c_0].energy_calibration_parameters[1] << " * " << detectors[n_d_0].channels[n_c_0].energy_branch_name << "[" << detectors[n_d_0].channels[n_c_0].energy_branch_index << "]" << ";\n";
                            if(n_c_0 > 0){
                                ofile << "\t\t\tif(" << detectors[n_d_0].name << "_energies[" << to_string(n_c_0) << "] > " << detectors[n_d_0].name << "_energies[maximum_energy_deposition_index]){\n";
                                ofile << "\t\t\t\ttime_0 = " << detectors[n_d_0].channels[n_c_0].time_branch_name << "[" << detectors[n_d_0].channels[n_c_0].time_branch_index << "];\n";
                                ofile << "\t\t\t\tmaximum_energy_deposition_index = " << to_string(n_c_0) << ";\n";
                                ofile << "\t\t\t}\n";
                            }
                        }

                        ofile << "\t\t\tenergy_0 = " << detectors[n_d_0].name + "_energies[0]";
                        for(size_t n_c_0 = 1; n_c_0 < detectors[n_d_0].channels.size(); ++n_c_0){
                            ofile << " + " << detectors[n_d_0].name + "_energies[" << to_string(n_c_0) << "]";
                        }
                        ofile << ";\n";
                    } else{
                        ofile << "\t\t\tenergy_0 = " << detectors[n_d_0].channels[0].energy_calibration_parameters[0] << " + " << detectors[n_d_0].channels[0].energy_calibration_parameters[1] << " * " << detectors[n_d_0].channels[0].energy_branch_name << "[" << detectors[n_d_0].channels[0].energy_branch_index << "];\n";
                        ofile << "\t\t\ttime_0 = " << detectors[n_d_0].channels[0].time_branch_name << "[" << detectors[n_d_0].channels[0].time_branch_index << "];\n";
                    }

                    if(detectors[n_d_1].channels.size() > 1){
                        ofile << "\t\t\ttime_1 = " << detectors[n_d_1].channels[0].time_branch_name << "[" << detectors[n_d_1].channels[0].time_branch_index << "];\n";
                        ofile << "\t\t\tmaximum_energy_deposition_index = 0;\n";
                        for(size_t n_c_1 = 0; n_c_1 < detectors[n_d_1].channels.size(); ++n_c_1){
                            ofile << "\t\t\t" << detectors[n_d_1].name << "_energies[" << to_string(n_c_1) << "] = isnan(" << detectors[n_d_1].channels[n_c_1].energy_branch_name << "[" << detectors[n_d_1].channels[n_c_1].energy_branch_index << "]) ? 0. : " << detectors[n_d_1].channels[n_c_1].energy_calibration_parameters[0] << " + " << detectors[n_d_1].channels[n_c_1].energy_calibration_parameters[1] << " * " << detectors[n_d_1].channels[n_c_1].energy_branch_name << "[" << detectors[n_d_1].channels[n_c_1].energy_branch_index << "]" << ";\n";
                            if(n_c_1 > 0){
                                ofile << "\t\t\tif(" << detectors[n_d_1].name << "_energies[" << to_string(n_c_1) << "] > " << detectors[n_d_1].name << "_energies[maximum_energy_deposition_index]){\n";
                                ofile << "\t\t\t\ttime_0 = " << detectors[n_d_1].channels[n_c_1].time_branch_name << "[" << detectors[n_d_1].channels[n_c_1].time_branch_index << "];\n";
                                ofile << "\t\t\t\tmaximum_energy_deposition_index = " << to_string(n_c_1) << ";\n";
                                ofile << "\t\t\t}\n";
                            }
                        }

                        ofile << "\t\t\tenergy_1 = " << detectors[n_d_1].name + "_energies[0]";
                        for(size_t n_c_1 = 1; n_c_1 < detectors[n_d_1].channels.size(); ++n_c_1){
                            ofile << " + " << detectors[n_d_1].name + "_energies[" << to_string(n_c_1) << "]";
                        }
                        ofile << ";\n";
                    } else {
                        ofile << "\t\t\tenergy_1 = " << detectors[n_d_1].channels[0].energy_calibration_parameters[0] << " + " << detectors[n_d_1].channels[0].energy_calibration_parameters[1] << " * " << detectors[n_d_1].channels[0].energy_branch_name << "[" << detectors[n_d_1].channels[0].energy_branch_index << "];\n";
                        ofile << "\t\t\ttime_1 = " << detectors[n_d_1].channels[0].time_branch_name << "[" << detectors[n_d_1].channels[0].time_branch_index << "];\n";
                    }
                    histogram_name_matched = false;
                    for(size_t i = 0; i < detector_groups.size(); ++i){
                        for(size_t j = i; j < detector_groups.size(); ++j){
                            if(detector_groups[i].name == detectors[n_d_0].group.name && detector_groups[j].name == detectors[n_d_1].group.name){
                                histogram_name = detectors[n_d_0].group.name + "_" + detectors[n_d_1].group.name;
                                histogram_name_matched = true;
                                break;
                            }
                            if(detector_groups[i].name == detectors[n_d_1].group.name && detector_groups[j].name == detectors[n_d_0].group.name){
                                histogram_name = detectors[n_d_1].group.name + "_" + detectors[n_d_0].group.name;
                                histogram_name_matched = true;
                                break;
                            }
                        }
                        if(histogram_name_matched){
                            break;
                        }
                    }
                    ofile << "\t\t\tcoincidence_" << histogram_name << "->Fill(energy_0, energy_1);\n";
                    ofile << "\t\t\ttime_difference_" << histogram_name << "->Fill(" << detectors[n_d_0].channels[0].time_calibration_parameters[1] << " * time_0 - " << detectors[n_d_1].channels[0].time_calibration_parameters[1] << " * time_1 );\n";
                    if(detectors[n_d_0].group.name == detectors[n_d_1].group.name){
                        ofile << "\t\t\tcoincidence_" << histogram_name << "->Fill(energy_1, energy_0);\n";
                        ofile << "\t\t\ttime_difference_" << histogram_name << "->Fill(" << detectors[n_d_1].channels[0].time_calibration_parameters[1] << " * time_1 - " << detectors[n_d_0].channels[0].time_calibration_parameters[1] << " * time_0 );\n";
                    }

                    ofile << "\t\t}\n";
                }

                ofile << "\t}\n";
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

    cout << "Configured '" << code_generation_dir << "histograms_2d.cpp'." << endl;

}