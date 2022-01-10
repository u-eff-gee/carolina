#include <iostream>

using std::cout;
using std::endl;

#include <memory>

using std::dynamic_pointer_cast;
using std::make_unique;
using std::unique_ptr;

#include <boost/program_options.hpp>

namespace po = boost::program_options;

#include "TFile.h"
#include "TGraph.h"
#include "TTree.h"

#include "analysis.hpp"
#include "inverse_calibration.hpp"
#include "sampler.hpp"

TGraph invert_energy_calibration(const size_t n_detector,
                                 const size_t n_channel) {
    function<double(const double, const long long)> calibration =
        dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
            analysis.detectors[n_detector]->channels[n_channel])
            ->energy_calibration;
    return invert_calibration<1000>(
        [&calibration](const double amplitude) {
            return calibration(amplitude, 0);
        },
        dynamic_pointer_cast<EnergySensitiveDetectorGroup>(
            analysis.get_group(n_detector))
            ->raw_histogram_properties.minimum,
        dynamic_pointer_cast<EnergySensitiveDetectorGroup>(
            analysis.get_group(n_detector))
            ->raw_histogram_properties.maximum);
}

TGraph invert_time_calibration(const size_t n_detector, const size_t n_channel,
                               const double tdc_resolution) {
    function<double(const double)> calibration =
        dynamic_pointer_cast<EnergySensitiveDetectorChannel>(
            analysis.detectors[n_detector]->channels[n_channel])
            ->time_calibration;
    return invert_calibration<1000>(
        [&calibration, &tdc_resolution](const double energy) {
            return calibration(energy) / tdc_resolution;
        },
        dynamic_pointer_cast<EnergySensitiveDetectorGroup>(
            analysis.get_group(n_detector))
            ->raw_histogram_properties.minimum,
        dynamic_pointer_cast<EnergySensitiveDetectorGroup>(
            analysis.get_group(n_detector))
            ->raw_histogram_properties.maximum);
}

vector<vector<TGraph>> invert_energy_calibrations() {
    vector<vector<TGraph>> inverse_calibrations;
    for (size_t n_detector = 0; n_detector < analysis.detectors.size();
         ++n_detector) {
        inverse_calibrations.push_back(vector<TGraph>());
        if (analysis.detectors[n_detector]->type == energy_sensitive) {
            for (size_t n_channel = 0;
                 n_channel < analysis.detectors[n_detector]->channels.size();
                 ++n_channel) {
                inverse_calibrations[n_detector].push_back(
                    invert_energy_calibration(n_detector, n_channel));
            }
        }
    }

    return inverse_calibrations;
}

vector<vector<TGraph>> invert_time_calibrations() {
    vector<vector<TGraph>> inverse_calibrations;
    for (size_t n_detector = 0; n_detector < analysis.detectors.size();
         ++n_detector) {
        inverse_calibrations.push_back(vector<TGraph>());
        if (analysis.detectors[n_detector]->type == energy_sensitive) {
            for (size_t n_channel = 0;
                 n_channel < analysis.detectors[n_detector]->channels.size();
                 ++n_channel) {
                inverse_calibrations[n_detector].push_back(
                    invert_time_calibration(
                        n_detector, n_channel,
                        analysis.get_tdc_resolution(n_detector, n_channel)));
            }
        }
    }

    return inverse_calibrations;
}

int main(int argc, char **argv) {
    po::options_description desc(
        "Using the current analysis configuration, fill a TTree with test data "
        "and write it to a ROOT file.");
    desc.add_options()("help", "Produce help message.")(
        "output", po::value<string>()->default_value("test.root"));
    ;

    po::variables_map vm;

    po::store(po::command_line_parser(argc, argv).options(desc).run(), vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << desc << endl;
        return 0;
    }

    TFile *output_file =
        new TFile(vm["output"].as<string>().c_str(), "RECREATE");
    TTree *tree = new TTree("test", "test");

    analysis.set_up_raw_branches_for_writing(tree);
    analysis.reset_raw_leaves();

    vector<vector<TGraph>> inverse_time_calibrations =
        invert_time_calibrations();
    vector<vector<TGraph>> inverse_energy_calibrations =
        invert_energy_calibrations();

    for (size_t n_detector = 0; n_detector < analysis.detectors.size();
         ++n_detector) {
        if (analysis.detectors[n_detector]->type == energy_sensitive) {
            for (size_t n_channel = 0;
                 n_channel < analysis.detectors[n_detector]->channels.size();
                 ++n_channel) {
                analysis.set_amplitude(
                    n_detector, n_channel,
                    inverse_energy_calibrations[n_detector][n_channel].Eval(
                        1000.));
                analysis.set_time(
                    n_detector, n_channel,
                    inverse_time_calibrations[n_detector][n_channel].Eval(0.));
                tree->Fill();
                analysis.reset_raw_leaves();
            }
        }
    }

    tree->Write();
    output_file->Close();
    cout << "Created output file '" << vm["output"].as<string>() << "'."
         << endl;
}