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

#include <fstream>

using std::ofstream;

#include <iostream>

using std::cout;
using std::endl;

#include <string>

using std::string;

#include <vector>

using std::vector;

#include <boost/program_options.hpp>

namespace po = boost::program_options;

#include "TFile.h"
#include "TH1.h"
#include "TKey.h"

#include "tfile_utilities.hpp"

void write_histogram_single_column(TH1 *histogram,
                                   const string output_file_name) {

    ofstream output_file(output_file_name);

    for (int i = 1; i <= histogram->GetNbinsX(); ++i) {
        output_file << histogram->GetBinContent(i) << "\n";
    }

    output_file.close();
}

void write_histogram_two_column(TH1 *histogram, const string separator,
                                const string output_file_name) {

    ofstream output_file(output_file_name);

    for (int i = 1; i <= histogram->GetNbinsX(); ++i) {
        output_file << histogram->GetBinCenter(i) << separator
                    << histogram->GetBinContent(i) << "\n";
    }

    output_file.close();
}

int main(int argc, char *argv[]) {

    po::variables_map vm;
    po::options_description desc(
        "Write the bin centers and bin contents of all TH1 histograms in a "
        "ROOT file to separate single- or two-column text files. The file "
        "names of the text files will contain the ROOT file name "
        "ROOT_FILE_NAME as a prefix, followed by the histogram name HIST_NAME, "
        "a user-defined suffix USER_SUFFIX, and '.root', "
        "i.e.\n\n\t{ROOT_FILE_NAME}_{HIST_NAME}[_{USER_SUFFIX}].txt\n");
    po::positional_options_description p;
    desc.add_options()("help", "Produce help message.")(
        "input_file", po::value<vector<string>>(), "Input file names.")(
        "rebin", po::value<unsigned int>()->default_value(1),
        "Before writing, rebin the spectrum using TH1::Rebin(). The parameter "
        "of the 'rebin' option corresponds to the 'ngroup' parameter of "
        "TH1::Rebin(). Default: 1, i.e. do not rebin.")(
        "separator", po::value<string>()->default_value(""),
        "Separator between 'bin center' and 'bin content' columns. The default "
        "is an empty string, indicating that only the bin contents should be "
        "written.")("suffix", po::value<string>()->default_value(""),
                    "User-defined suffix to be inserted between the file name "
                    "and the file-type ('.txt') suffix.");
    p.add("input_file", -1);

    po::store(
        po::command_line_parser(argc, argv).options(desc).positional(p).run(),
        vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << desc << "\n";
        return 0;
    }

    if (!vm.count("input_file")) {
        cout << "No input file given. Aborting ..." << endl;
        return 0;
    }

    const vector<string> input_files = vm["input_file"].as<vector<string>>();
    const string separator = vm["separator"].as<string>();

    string output_file_name;
    string prefix;

    for (auto input_file : input_files) {
        TFile file(input_file.c_str(), "READ");
        TIter next_key(file.GetListOfKeys());
        prefix = remove_or_replace_suffix(input_file) + "_";

        TKey *key;
        while ((key = (TKey *)next_key())) {
            TObject *obj = key->ReadObj();
            if (obj->IsA()->InheritsFrom(TH1::Class())) {
                TH1 *histogram = (TH1 *)obj;
                if (vm["rebin"].as<unsigned int>() != 1) {
                    histogram->Rebin(vm["rebin"].as<unsigned int>());
                }
                output_file_name = prefix + key->GetName();
                if (vm["suffix"].as<string>() != "") {
                    output_file_name += ("_" + vm["suffix"].as<string>());
                }
                output_file_name += ".txt";
                if (separator == "") {
                    write_histogram_single_column(histogram, output_file_name);
                } else {
                    write_histogram_two_column(histogram, separator,
                                               output_file_name);
                }
                cout << "Created file '" << output_file_name << "'." << endl;
                delete histogram;
            }
        }
    }
}
