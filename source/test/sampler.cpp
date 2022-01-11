#include <iostream>

using std::cout;
using std::endl;

#include <memory>

using std::dynamic_pointer_cast;
using std::make_unique;
using std::unique_ptr;

#include <numeric>

using std::accumulate;

#include <random>

using std::mt19937;
using std::random_device;
using std::uniform_real_distribution;

#include <boost/program_options.hpp>

namespace po = boost::program_options;

#include "TFile.h"
#include "TGraph.h"
#include "TTree.h"

#include "analysis.hpp"
#include "inverse_calibration.hpp"
#include "progress_printer.hpp"
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

vector<double> split_up_energy(const double energy,
                               const unsigned int n_channels,
                               const unsigned int seed = 0) {
    if (n_channels == 1) {
        return {energy};
    }
    vector<double> energies(n_channels), uniform_random_numbers(n_channels);

    mt19937 random_engine(seed);
    uniform_real_distribution<double> uni_dis;

    for (unsigned int n_channel = 0; n_channel < n_channels; ++n_channel) {
        uniform_random_numbers[n_channel] = uni_dis(random_engine);
    }
    const double uniform_random_numbers_normalization =
        1. / accumulate(uniform_random_numbers.begin(),
                        uniform_random_numbers.end(), 0.);
    for (unsigned int n_channel = 0; n_channel < n_channels; ++n_channel) {
        energies[n_channel] = energy * uniform_random_numbers[n_channel] *
                              uniform_random_numbers_normalization;
    }
    return energies;
}

void create_single_event(const size_t n_detector, const size_t n_channel,
                         const double gamma_energy,
                         const vector<vector<TGraph>> energy_calibration,
                         const double gamma_time,
                         const vector<vector<TGraph>> time_calibration) {
    analysis.set_amplitude(
        n_detector, n_channel,
        energy_calibration[n_detector][n_channel].Eval(gamma_energy));
    analysis.set_time(n_detector, n_channel,
                      time_calibration[n_detector][n_channel].Eval(gamma_time));
}

void create_single_event_with_addback(
    const size_t n_detector, const double gamma_energy,
    const vector<vector<TGraph>> energy_calibration, const double gamma_time,
    const vector<vector<TGraph>> time_calibration) {
    random_device ran_dev;
    vector<double> energy_depositions = split_up_energy(
        gamma_energy, analysis.detectors[n_detector]->channels.size(),
        ran_dev());
    for (size_t n_channel = 0;
         n_channel < analysis.detectors[n_detector]->channels.size();
         ++n_channel) {
        analysis.set_amplitude(n_detector, n_channel,
                               energy_calibration[n_detector][n_channel].Eval(
                                   energy_depositions[n_channel]));
        analysis.set_time(
            n_detector, n_channel,
            time_calibration[n_detector][n_channel].Eval(gamma_time));
    }
}

int main(int argc, char **argv) {
    po::options_description desc(
        "Using the current analysis configuration, fill a TTree with test data "
        "and write it to a ROOT file.");
    desc.add_options()("help", "Produce help message.")(
        "n", po::value<unsigned int>()->default_value(1))(
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

    const double gamma_energy = 1000;
    const double gamma_time = 0.;
    vector<double> energies;

    const unsigned int n_max = vm["n"].as<unsigned int>();
    ProgressPrinter progress_printer(n_max, 0.01, "set of events",
                                     "sets of events");

    for (unsigned int n = 0; n < n_max; ++n) {
        progress_printer(n);
        for (size_t n_detector_1 = 0; n_detector_1 < analysis.detectors.size();
             ++n_detector_1) {
            if (analysis.detectors[n_detector_1]->type == energy_sensitive) {
                // Generate single events that require addback.
                create_single_event_with_addback(
                    n_detector_1, gamma_energy, inverse_energy_calibrations,
                    gamma_time, inverse_time_calibrations);
                tree->Fill();
                analysis.reset_raw_leaves();
                // Generate events in which the entire gamma-ray energy is
                // deposited in a single crystal.
                for (size_t n_channel = 0;
                     n_channel <
                     analysis.detectors[n_detector_1]->channels.size();
                     ++n_channel) {
                    create_single_event(n_detector_1, n_channel, gamma_energy,
                                        inverse_energy_calibrations, gamma_time,
                                        inverse_time_calibrations);
                    tree->Fill();
                    analysis.reset_raw_leaves();
                }

                for (size_t n_detector_2 = 0;
                     n_detector_2 < analysis.detectors.size(); ++n_detector_2) {
                    if (analysis.detectors[n_detector_2]->type ==
                        energy_sensitive) {
                        // Create a coincident event in two detectors that
                        // requires addback.
                        create_single_event_with_addback(
                            n_detector_1, gamma_energy,
                            inverse_energy_calibrations, gamma_time,
                            inverse_time_calibrations);
                        create_single_event_with_addback(
                            n_detector_2, gamma_energy,
                            inverse_energy_calibrations, gamma_time,
                            inverse_time_calibrations);
                        tree->Fill();
                        analysis.reset_raw_leaves();
                    }
                }
            }
        }
    }

    tree->Write();
    output_file->Close();
    cout << "Created output file '" << vm["output"].as<string>() << "'."
         << endl;
}