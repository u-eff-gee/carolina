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

#pragma once

#include "TChain.h"

#include "reader.hpp"

struct Reader : ReaderBase {
    Reader(const vector<string> input_files, const long long first,
           const long long last = -1)
        : ReaderBase(input_files, first, last){};

    void initialize(Analysis &analysis, const string tree_name,
                    const vector<bool> counter_values = {false},
                    const vector<bool> amp_t_tref_ts = {false, false, false,
                                                        false}) override final {
        tree = new TChain(find_tree_in_file(input_files[0], tree_name).c_str());
        for (auto input_file : input_files) {
            cout << "Adding '" << input_file.c_str() << "' to TChain." << endl;
            tree->Add(input_file.c_str());
        }

        n_entries = tree->GetEntries();
        if (n_entries == 0) {
            cout << "TTree::GetEntries() returned 0." << endl;
            abort();
        }
        entry = first - 1;
        last = (last == -1) ? n_entries - 1 : last;

        tree->SetBranchStatus("*", 0);
        analysis.set_up_raw_counter_detector_branches_for_reading(
            tree, counter_values);
        analysis.set_up_raw_energy_sensitive_detector_branches_for_reading(
            tree, amp_t_tref_ts);
    };

    bool read([[maybe_unused]] Analysis &analysis) override final {
        ++entry;
        if (entry <= last) {
            tree->GetEntry(entry);
            return true;
        }
        return false;
    };

    void finalize() override final {};

    TChain *tree;
    long long n_entries;
};