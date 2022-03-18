/*
     This file is part of carolina.

    carolina is free software: you can redistribute it and/or modify it under
   the terms of the GNU General Public License as published by the Free Software
   Foundation, either version 3 of the License, or (at your option) any later
   version.

    carolina is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
    more details.

    You should have received a copy of the GNU General Public License along with
    carolina. If not, see <https://www.gnu.org/licenses/>.
*/

#include <cassert>

#include <iostream>

using std::cout;
using std::endl;

#include <string>

using std::string;

#include <boost/program_options.hpp>

namespace po = boost::program_options;

#include "TFile.h"
#include "TH1.h"

#include "sampler.hpp"
#include "test_histograms_1d_raw.hpp"

int main(int argc, char **argv) {
    po::options_description desc(
        "Check whether output of the 'sampler' script has been processed "
        "correctly by the 'histograms_1d' script.");
    po::positional_options_description p;
    desc.add_options()("ignore_errors",
                       "Do not raise an error if one of the tests fails.")(
        "help", "Produce help message.")("input_file", po::value<string>(),
                                         "Input file name.")(
        "n", po::value<unsigned int>()->default_value(1));
    ;
    p.add("input_file", -1);

    po::variables_map vm;

    po::store(
        po::command_line_parser(argc, argv).options(desc).positional(p).run(),
        vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << desc << endl;
        return 0;
    }

    if (!vm.count("input_file")) {
        cout << "No input file given. Aborting ..." << endl;
        return 1;
    }

    vector<vector<TGraph>> inverse_energy_calibrations =
        invert_energy_calibrations();

    TFile *file = new TFile(vm["input_file"].as<string>().c_str(), "READ");

    int gamma_energy_bin, rate_bin;
    string histogram_name;
    TH1D *histogram;

    cout << "Testing output of 'histograms_1d_raw' script, assuming that the "
            "test data contain n = "
         << vm["n"].as<unsigned int>() << " events.\n"
         << endl;
    cout << "The test may fail if ...\n\t- ... the '--random' option of the "
            "event sampler has been used. Since this script tests for the "
            "content of specific bins, their expected content may be changed "
            "if random energies incidentally have a similar energy.\n\t- ... "
            "the histograms are not suited for the expected distribution of "
            "energies. This may cause energies to end up in the "
            "overflow/underflow bins of the histograms. In this case, "
            "TH1::GetEntries() and TH1::Integral() will give different "
            "results.\n"
         << endl;
    cout << "Energy histograms for energy-sensitive detectors:" << endl;
    for (size_t n_detector = 0;
         n_detector < analysis.energy_sensitive_detectors.size();
         ++n_detector) {
        if (analysis.energy_sensitive_detectors[n_detector]->channels.size() >
            1) {
            histogram_name =
                analysis.energy_sensitive_detectors[n_detector]->name +
                "_addback";
            histogram = (TH1D *)file->Get(histogram_name.c_str());
            cout << "\nDetector '"
                 << analysis.energy_sensitive_detectors[n_detector]->name
                 << "' (addback):" << endl;
            check_expected_energy_sensitive_detector_events_with_addback(
                histogram, vm["n"].as<unsigned int>(), n_detector,
                vm.count("ignore_errors"), true);
            check_expected_full_energy_events_with_addback(
                histogram, vm["n"].as<unsigned int>(), n_detector,
                gamma_energy_bin, vm.count("ignore_errors"), 5, true);
        }
        for (size_t n_channel = 0;
             n_channel <
             analysis.energy_sensitive_detectors[n_detector]->channels.size();
             ++n_channel) {
            cout << "\nDetector '"
                 << analysis.energy_sensitive_detectors[n_detector]->name
                 << "', channel '"
                 << analysis.energy_sensitive_detectors[n_detector]
                        ->channels[n_channel]
                        .name
                 << "':" << endl;
            histogram_name =
                analysis.energy_sensitive_detectors[n_detector]->name + "_" +
                analysis.energy_sensitive_detectors[n_detector]
                    ->channels[n_channel]
                    .name;
            histogram = (TH1D *)file->Get(histogram_name.c_str());
            gamma_energy_bin = histogram->FindBin(gamma_energy);
            check_expected_energy_sensitive_detector_events(
                histogram, vm["n"].as<unsigned int>(), n_detector, n_channel,
                vm.count("ignore_errors"), true);
            cout << "Nominal gamma energy of " << gamma_energy
                 << " would be sorted into histogram "
                    "bin #"
                 << gamma_energy_bin << "." << endl;
            check_expected_full_energy_events(
                histogram, vm["n"].as<unsigned int>(), n_detector, n_channel,
                gamma_energy_bin, vm.count("ignore_errors"), 5);
        }
    }
    cout << "\nCount-rate histograms for counter detectors:" << endl;
    for (size_t n_detector = 0; n_detector <
    analysis.counter_detectors.size();
         ++n_detector) {
        for (size_t n_channel = 0;
             n_channel <
             analysis.counter_detectors[n_detector]->channels.size();
             ++n_channel) {
            cout << "\nDetector '"
                 << analysis.counter_detectors[n_detector]->name
                 << "', channel '"
                 << analysis.counter_detectors[n_detector]
                        ->channels[n_channel]
                        .name
                 << "':" << endl;
            histogram_name = analysis.counter_detectors[n_detector]->name +
                             "_" +
                             analysis.counter_detectors[n_detector]
                                 ->channels[n_channel]
                                 .name;
            histogram = (TH1D *)file->Get(histogram_name.c_str());
            rate_bin = histogram->FindBin(counter_increment);
            check_expected_counter_detector_rate(
                histogram, vm["n"].as<unsigned int>(), n_detector, n_channel, rate_bin,
                vm.count("ignore_errors"));
        }
    }
}