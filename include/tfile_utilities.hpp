#include <string>

using std::string;
using std::to_string;

#include "TFile.h"
#include "TKey.h"

string find_tree_in_file(const string filename, const string tree_name = "") {
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