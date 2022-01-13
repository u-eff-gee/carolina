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

string add_index_to_file_name(const string filename, const size_t index) {
    if (filename.find(".root")) {
        return filename.substr(0, filename.size() - 5) + "_" +
               to_string(index) + ".root";
    }
    return to_string(index) + "_" + filename;
}

string add_or_change_file_name_suffix(const string filename,
                                      const string new_suffix) {
    if (filename.find(".root")) {
        return filename.substr(0, filename.size() - 5) + new_suffix;
    }
    return filename + new_suffix;
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