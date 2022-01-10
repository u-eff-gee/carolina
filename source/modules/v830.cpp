#include <limits>

using std::numeric_limits;

#include "v830.hpp"

void V830::reset_raw_leaves() {
    for (size_t n_leaf = 0; n_leaf < 32; ++n_leaf) {
        counter_values.leaves[n_leaf] = numeric_limits<long long>::quiet_NaN();
    }
}

void V830::set_up_raw_branches_for_reading(TTree *tree) {
    tree->SetBranchStatus(counter_values.name.c_str(), 1);

    tree->SetBranchAddress(counter_values.name.c_str(), counter_values.leaves);
}

void V830::set_up_raw_branches_for_writing(TTree *tree) {
    tree->Branch(counter_values.name.c_str(), counter_values.leaves, (counter_values.name + "[32]/D").c_str());
}