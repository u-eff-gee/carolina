#include "v830.hpp"

void V830::set_up_raw_branches(TTree *tree) {
    tree->SetBranchStatus(counter_values.name.c_str(), 1);

    tree->SetBranchAddress(counter_values.name.c_str(), counter_values.leaves);
}