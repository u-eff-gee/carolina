#include <iostream>

using std::cout;
using std::endl;

#include <memory>

using std::dynamic_pointer_cast;

#include "TFile.h"
#include "TGraph.h"
#include "TTree.h"

#include "analysis.hpp"
#include "inverse_calibration.hpp"
#include "sampler.hpp"

TGraph invert_energy_calibration(const size_t n_detector, const size_t n_channel){
    function<double(const double, const long long)> calibration = dynamic_pointer_cast<EnergySensitiveDetectorChannel>(analysis.detectors[n_detector]->channels[n_channel])->energy_calibration;
    return invert_calibration<1000>([&calibration](const double amplitude){ return calibration(amplitude, 0);}, dynamic_pointer_cast<EnergySensitiveDetectorGroup>(analysis.get_group(n_detector))->raw_histogram_properties.minimum, dynamic_pointer_cast<EnergySensitiveDetectorGroup>(analysis.get_group(n_detector))->raw_histogram_properties.maximum);
}

TGraph invert_time_calibration(const size_t n_detector, const size_t n_channel, const double tdc_resolution){
    function<double(const double)> calibration = dynamic_pointer_cast<EnergySensitiveDetectorChannel>(analysis.detectors[n_detector]->channels[n_channel])->time_calibration;
    return invert_calibration<1000>([&calibration, &tdc_resolution](const double energy){ return calibration(energy)/tdc_resolution;},dynamic_pointer_cast<EnergySensitiveDetectorGroup>(analysis.get_group(n_detector))->raw_histogram_properties.minimum, dynamic_pointer_cast<EnergySensitiveDetectorGroup>(analysis.get_group(n_detector))->raw_histogram_properties.maximum);
}

vector<vector<TGraph>> invert_energy_calibrations(){
    vector<vector<TGraph>> inverse_calibrations;
    for (size_t n_detector = 0; n_detector < analysis.detectors.size();
         ++n_detector) {
        inverse_calibrations.push_back(vector<TGraph>());
        if (analysis.detectors[n_detector]->type == energy_sensitive) {
            for (size_t n_channel = 0;
                 n_channel < analysis.detectors[n_detector]->channels.size();
                 ++n_channel) {
                inverse_calibrations[n_detector].push_back(invert_energy_calibration(n_detector, n_channel));
            }
        }
    }

    return inverse_calibrations;
}

vector<vector<TGraph>> invert_time_calibrations(){
    vector<vector<TGraph>> inverse_calibrations;
    for (size_t n_detector = 0; n_detector < analysis.detectors.size();
         ++n_detector) {
        inverse_calibrations.push_back(vector<TGraph>());
        if (analysis.detectors[n_detector]->type == energy_sensitive) {
            for (size_t n_channel = 0;
                 n_channel < analysis.detectors[n_detector]->channels.size();
                 ++n_channel) {
                inverse_calibrations[n_detector].push_back(invert_time_calibration(n_detector, n_channel, analysis.get_tdc_resolution(n_detector, n_channel)));
            }
        }
    }

    return inverse_calibrations;
}

int main() {
    TFile *output_file = new TFile("output.root", "RECREATE");
    TTree *tree = new TTree("test", "test");

    analysis.set_up_raw_branches_for_writing(tree);

    vector<vector<TGraph>> inverse_time_calibrations = invert_time_calibrations();
    vector<vector<TGraph>> inverse_energy_calibrations = invert_energy_calibrations();

    for (size_t n_detector = 0; n_detector < analysis.detectors.size();
         ++n_detector) {
        if (analysis.detectors[n_detector]->type == energy_sensitive) {
            for (size_t n_channel = 0;
                 n_channel < analysis.detectors[n_detector]->channels.size();
                 ++n_channel) {
                analysis.set_amplitude(n_detector, n_channel, inverse_energy_calibrations[n_detector][n_channel].Eval(1000.));
            }
        }
    }

    tree->Fill();

    tree->Write();
    output_file->Close();
}