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
                                                        false}) override final;
    bool read() override final;
    TChain *tree;
    long long n_entries;
};