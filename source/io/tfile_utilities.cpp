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

#include "tfile_utilities.hpp"

#include <fstream>

using std::ifstream;
using std::ofstream;

#include <iostream>

using std::cout;
using std::endl;

#include <string>

using std::to_string;

#include "TFile.h"
#include "TKey.h"

string remove_or_replace_suffix(const string file_name,
                                const string new_suffix) {
    size_t suffix_separator_position = file_name.rfind(".");
    if (suffix_separator_position == std::string::npos) {
        return file_name + new_suffix;
    }

    return file_name.substr(0, suffix_separator_position) + new_suffix;
}

vector<pair<long long, long long>>
divide_into_blocks(const long long first, const long long last,
                   const long long block_size) {
    vector<pair<long long, long long>> blocks;

    long long current_index = first;

    while ((current_index + block_size - 1) < last) {
        blocks.push_back({current_index, current_index + block_size - 1});
        current_index = current_index + block_size;
    }

    blocks.push_back({current_index, last});

    return blocks;
};

string find_tree_in_file(const string filename, const string tree_name) {
    if (tree_name.size()) {
        return tree_name;
    }

    TFile file(filename.c_str());
    const string tree_class = "TTree";

    for (TObject *keyAsObj : *file.GetListOfKeys()) {
        auto key = dynamic_cast<TKey *>(keyAsObj);
        if (!tree_class.compare(key->GetClassName())) {
            return key->GetName();
        }
    }

    return tree_name;
}

vector<string> read_log_file(const string filename) {
    vector<string> file_names;
    ifstream file(filename);

    string line;
    while (getline(file, line)) {
        file_names.push_back(line);
    }
    return file_names;
}

void write_list_of_output_files(const string output_file_name,
                                vector<string> list_of_files) {
    ofstream log_file(output_file_name);
    for (auto file : list_of_files) {
        log_file << file;
        log_file << "\n";
    }
    log_file.close();

    cout << "Wrote list of generated output files to '" << output_file_name
         << "'." << endl;
}