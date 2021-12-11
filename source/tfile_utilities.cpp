#include "tfile_utilities.hpp"

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

vector<pair<long long, long long>>
divide_into_blocks(const long long first, const long long last,
                   const long long block_size) {
    vector<pair<long long, long long>> blocks;

    long long current_index = first;

    while (current_index < last) {
        current_index += block_size;
        if (current_index < last) {
            blocks.push_back({current_index - block_size, current_index});
        } else {
            blocks.push_back({current_index - block_size, last});
            break;
        }
    }

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