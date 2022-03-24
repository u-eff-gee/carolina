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

#include <fstream>

using std::ifstream;

#include <iostream>

using std::cout;
using std::endl;

#include "mvlclst_dictionary.hpp"
#include "reader.hpp"

struct Reader : ReaderBase {
    Reader(const vector<string> input_files, const long long first,
           const long long last = -1)
        : ReaderBase(input_files, first, last){};

    void
    initialize([[maybe_unused]] Analysis &analysis,
               [[maybe_unused]] const string option,
               [[maybe_unused]] const vector<bool> counter_values = {false},
               [[maybe_unused]] const vector<bool> amp_t_tref_ts = {
                   false, false, false, false}) override final {
        if (input_files.size() > 1) {
            cout << "Warning: The 'mvlclst' reader can only process a single "
                    "file. "
                    "Reading only the first file from the given list, '"
                 << input_files[0] << "'." << endl;
        }
        if (option != "") {
            cout << "Warning: option '--tree=" << option
                 << "' was ignored. The 'mvlclst' reader has no optional "
                    "arguments."
                 << endl;
        }
        file.open(input_files[0], std::ios::binary | std::ios::ate);
        n_words = file.tellg() / 4;

        last = (last == -1) ? n_words - 1 : last;

        file.seekg(std::ios::beg);
    };

    bool read(Analysis &analysis) override final {
        entry = file.tellg() / 4;
        while (file.read(reinterpret_cast<char *>(&data_integer),
                         sizeof(data_integer)) &&
               entry < last) {
            if ((data_integer & header_mask) == header_found_flag) {
                module_id = (data_integer & module_id_mask) / module_id_offset;
                module_found =
                    analysis.find_module_by_id(module_index, module_id);
                if (module_found) {
                    return true;
                }
            }
            if (module_found && (data_integer & data_mask) == data_found_flag) {
                analysis.modules[module_index]->process_data_word(data_integer);
            };
        }
        return false;
    }

    void finalize() override final {
        file.close();
    }

    bool module_found;
    ifstream file;
    long long n_words;
    uint32_t channel_number, data_integer, data_length, module_id;
    size_t module_index;
};