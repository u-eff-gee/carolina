#include <string>

using std::to_string;

#include "mdpp16.hpp"

void MDPP16::activate_branches(TTree *tree) {
    tree->SetBranchStatus(amplitude.name.c_str(), 1);
    tree->SetBranchStatus(time.name.c_str(), 1);
    tree->SetBranchStatus(timestamp.name.c_str(), 1);
}

vector<string> MDPP16::get_branch_names(const size_t leaf) const {
    vector<string> branch_names;

    const string index = "[" + to_string(leaf) + "]";
    branch_names.push_back(amplitude.name.c_str() + index);
    branch_names.push_back(time.name.c_str() + index);

    return branch_names;
}

void MDPP16::register_branches(TTree *tree) {
    tree->SetBranchAddress(amplitude.name.c_str(), amplitude.leaves);
    tree->SetBranchAddress(time.name.c_str(), time.leaves);
    tree->SetBranchAddress(timestamp.name.c_str(), timestamp.leaves);
}