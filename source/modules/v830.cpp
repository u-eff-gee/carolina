#include <limits>

using std::numeric_limits;

#include "v830.hpp"

void V830::reset_raw_leaves() {
    // A real V830 module memorizes its current state, so this implementation of
    // the inherited method does nothing.
}

void V830::set_up_raw_branches_for_reading(TTree *tree) {
    tree->SetBranchStatus(counter_values.name.c_str(), 1);

    tree->SetBranchAddress(counter_values.name.c_str(), counter_values.leaves);
}

void V830::set_up_raw_branches_for_writing(TTree *tree) {
    tree->Branch(counter_values.name.c_str(), counter_values.leaves,
                 (counter_values.name + "[32]/D").c_str());
}