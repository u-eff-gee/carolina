#pragma once

#include <string>

using std::string;

#include <utility>

using std::pair;

#include <vector>

using std::vector;

string add_index_to_file_name(const string filename, const size_t index);

string add_or_change_file_name_suffix(const string filename,
                                      const string new_suffix);

vector<pair<long long, long long>>
divide_into_blocks(const long long first, const long long last,
                   const long long block_size);

string find_tree_in_file(const string filename, const string tree_name = "");

vector<string> read_log_file(const string filename);

void write_list_of_output_files(const string output_file_name,
                                vector<string> list_of_files);