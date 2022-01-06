#include <string>

using std::to_string;

#include "mdpp16.hpp"

void MDPP16::set_up_raw_branches(TTree *tree) {
    tree->SetBranchStatus(amplitude.name.c_str(), 1);
    tree->SetBranchStatus(time.name.c_str(), 1);
    tree->SetBranchStatus(timestamp.name.c_str(), 1);

    tree->SetBranchAddress(amplitude.name.c_str(), amplitude.leaves);
    tree->SetBranchAddress(time.name.c_str(), time.leaves);
    tree->SetBranchAddress(timestamp.name.c_str(), timestamp.leaves);
}