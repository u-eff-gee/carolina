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