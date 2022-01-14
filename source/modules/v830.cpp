/*
     This file is part of carolina.

    carolina is free software: you can redistribute it and/or modify it under
   the terms of the GNU General Public License as published by the Free Software
   Foundation, either version 3 of the License, or (at your option) any later
   version.

    carolina is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
    more details.

    You should have received a copy of the GNU General Public License along with
    carolina. If not, see <https://www.gnu.org/licenses/>.
*/

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