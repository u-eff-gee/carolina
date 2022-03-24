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

#include <string>

using std::string;

#include <vector>

using std::vector;

#include "analysis.hpp"
#include "tfile_utilities.hpp"

struct ReaderBase {
    ReaderBase(const vector<string> input_files, const long long first = 0,
                   const long long last = -1)
        : input_files(input_files), first(first), last(last){};
    virtual void initialize(Analysis &analysis, const string option, const vector<bool> counter_values={false}, const vector<bool> amp_t_tref_ts={false, false, false, false}) = 0;
    virtual bool read(Analysis &analysis) = 0;
    virtual void finalize() = 0;

    vector<string> input_files;
    long long entry;
    long long first, last;
};