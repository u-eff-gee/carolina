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

#include <utility>

using std::pair;

#include <vector>

using std::vector;

vector<pair<long long, long long>>
divide_into_blocks(const long long first, const long long last,
                   const long long block_size);

string find_tree_in_file(const string filename, const string tree_name = "");

vector<string> read_log_file(const string filename);

string remove_or_replace_suffix(const string file_name,
                                const string new_suffix = "");

void write_list_of_output_files(const string output_file_name,
                                vector<string> list_of_files);