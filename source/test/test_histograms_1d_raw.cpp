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
        "correctly by the 'histograms_1d_raw' script.");
    po::positional_options_description p;
    desc.add_options()("help", "Produce help message.")(
        "input_file", po::value<string>(),
        "Input file name.")("n", po::value<unsigned int>()->default_value(1));
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

    double raw_gamma_energy, raw_background_gamma_energy;
    int raw_gamma_energy_bin, raw_background_gamma_energy_bin;
    unsigned int expected_entries, expected_fep_entries;
    const size_t n_energy_sensitive_detector_channels =
        analysis.get_n_energy_sensitive_detector_channels();
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
        for (size_t n_channel = 0;
             n_channel <
             analysis.energy_sensitive_detectors[n_detector]->channels.size();
             ++n_channel) {
            histogram_name =
                analysis.energy_sensitive_detectors[n_detector]->name + "_" +
                analysis.energy_sensitive_detectors[n_detector]
                    ->channels[n_channel]
                    .name;
            histogram = (TH1D *)file->Get(histogram_name.c_str());
            raw_gamma_energy =
                inverse_energy_calibrations[n_detector][n_channel].Eval(
                    gamma_energy);
            raw_gamma_energy_bin = histogram->FindBin(raw_gamma_energy);
            raw_background_gamma_energy =
                inverse_energy_calibrations[n_detector][n_channel].Eval(
                    background_gamma_energy);
            raw_background_gamma_energy_bin =
                histogram->FindBin(raw_background_gamma_energy);
            expected_entries =
                vm["n"].as<unsigned int>() *
                (3 + (analysis.energy_sensitive_detectors.size() - 1));
            if (analysis.energy_sensitive_detectors[n_detector]
                    ->channels.size() == 1) {
                expected_fep_entries =
                    vm["n"].as<unsigned int>() *
                    (2 + (analysis.energy_sensitive_detectors.size() - 1));
            } else {
                expected_fep_entries = vm["n"].as<unsigned int>();
            }

            cout << "Detector channel: " << histogram_name << endl;
            cout << "Nominal gamma energy of " << gamma_energy << " appears as "
                 << raw_gamma_energy
                 << " in this channel, which would be sorted into histogram "
                    "bin #"
                 << raw_gamma_energy_bin << "." << endl;
            cout << "Nominal background gamma energy of "
                 << background_gamma_energy << " appears as "
                 << raw_background_gamma_energy
                 << " in this channel, which would be sorted into histogram "
                    "bin #"
                 << raw_background_gamma_energy_bin << "." << endl;
            cout << "\t" << histogram_name
                 << "->GetEntries() = " << histogram->GetEntries()
                 << " [Expect " << expected_entries << ": "
                 << vm["n"].as<unsigned int>()
                 << " events where the total energy of " << gamma_energy
                 << " is deposited in this channel, "
                 << vm["n"].as<unsigned int>()
                 << " events where the same energy is split between the "
                    "channels of the detector (if it has multiple channels, "
                    "otherwise they are just another "
                 << vm["n"].as<unsigned int>() << " events with an energy of "
                 << gamma_energy << "), " << vm["n"].as<unsigned int>()
                 << " background events with an energy of "
                 << background_gamma_energy << ", and "
                 << (analysis.energy_sensitive_detectors.size() - 1) *
                        vm["n"].as<unsigned int>()
                 << " events for coincidences with the other "
                 << analysis.energy_sensitive_detectors.size() - 1
                 << " detectors]" << endl;
            cout << "\t" << histogram_name
                 << "->Integral() = " << histogram->Integral() << " (Expect "
                 << expected_entries
                 << " events due to the same reasoning as "
                    "above)"
                 << endl;
            cout << "\t" << histogram_name << "->GetBinContent("
                 << raw_gamma_energy_bin
                 << ") = " << histogram->GetBinContent(raw_gamma_energy_bin);
            if (analysis.energy_sensitive_detectors[n_detector]
                    ->channels.size() > 1) {
                cout << " (Expect " << vm["n"].as<unsigned int>()
                     << " Events with an energy deposition of " << gamma_energy
                     << ")";
            } else {
                cout << " [Expect " << expected_fep_entries
                     << " Events with an energy deposition of " << gamma_energy
                     << ". Same as the output of TH1::GetEntries(), but "
                        "without the "
                     << vm["n"].as<unsigned int>()
                     << " background events that have a different energy ("
                     << background_gamma_energy << ")].";
            }
            cout << endl;
            cout << "\t" << histogram_name << "->GetBinContent("
                 << raw_background_gamma_energy_bin << ") = "
                 << histogram->GetBinContent(raw_background_gamma_energy_bin)
                 << " (Expect " << vm["n"].as<unsigned int>()
                 << " background events with an energy deposition of "
                 << background_gamma_energy << ")\n"
                 << endl;
            assert(histogram->GetEntries() == expected_entries);
            assert((unsigned int)histogram->Integral() == expected_entries);
            assert((unsigned int)histogram->GetBinContent(
                       raw_background_gamma_energy_bin) ==
                   vm["n"].as<unsigned int>());
            if (analysis.energy_sensitive_detectors[n_detector]
                    ->channels.size() == 1) {
                assert((unsigned int)histogram->GetBinContent(
                           raw_gamma_energy_bin) == expected_fep_entries);
            } else {
                assert((unsigned int)histogram->GetBinContent(
                           raw_gamma_energy_bin) == vm["n"].as<unsigned int>());
            }
        }
    }
    cout << "Counter histograms for counter detectors:" << endl;
    for (size_t n_detector = 0; n_detector < analysis.counter_detectors.size();
         ++n_detector) {
        for (size_t n_channel = 0;
             n_channel <
             analysis.counter_detectors[n_detector]->channels.size();
             ++n_channel) {
            expected_entries =
                vm["n"].as<unsigned int>() *
                (n_energy_sensitive_detector_channels   // Single-channel events
                 + n_energy_sensitive_detector_channels // Background events
                 + analysis.energy_sensitive_detectors.size() // Addback events
                 + (analysis.energy_sensitive_detectors.size() - 1) *
                       analysis.energy_sensitive_detectors.size() /
                       2 // Number of possible coincidences. The first of N
                         // detectors has N-1 coincidence partners, the second
                         // has N-2 partners, i.e. the number of coincidences is
                         // the sum (arithmetic progression)
                         // N-1 + N-2 + ... + 1 = N*(N-1)/2
                 + 1     // Counter events
                );
            histogram_name = analysis.counter_detectors[n_detector]->name +
                             "_" +
                             analysis.counter_detectors[n_detector]
                                 ->channels[n_channel]
                                 .name;
            cout << "Detector channel: " << histogram_name << endl;
            histogram = (TH1D *)file->Get(histogram_name.c_str());
            cout << "\t" << histogram_name
                 << "->GetEntries() = " << histogram->GetEntries()
                 << " [Expect " << expected_entries
                 << " entries: The counter value is recorded each time one of "
                    "the energy-sensitive detector events is recorded, "
                    "resulting in "
                 << n_energy_sensitive_detector_channels << " x "
                 << vm["n"].as<unsigned int>() << " single-channel events, "
                 << n_energy_sensitive_detector_channels << " x "
                 << vm["n"].as<unsigned int>() << " background events, "
                 << analysis.energy_sensitive_detectors.size() << " x "
                 << vm["n"].as<unsigned int>() << " addback events, and "
                 << (analysis.energy_sensitive_detectors.size() - 1) *
                        analysis.energy_sensitive_detectors.size() / 2
                 << " (number of unique coincidences between detectors) x "
                 << vm["n"].as<unsigned int>()
                 << " coincident events. In addition, there are "
                 << vm["n"].as<unsigned int>()
                 << " events in which only the counter is increased.]" << endl;
            assert(histogram->GetEntries() == expected_entries);
        }
    }
}