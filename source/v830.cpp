#include "v830.hpp"

void V830::activate_branches(TTree *tree) {
    tree->SetBranchStatus(counter_values.name.c_str(), 1);
}

void V830::register_branches(TTree *tree) {
    tree->SetBranchAddress(counter_values.name.c_str(), counter_values.leaves);
}