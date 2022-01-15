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

#include <string>

using std::to_string;

#include "mdpp16.hpp"

void MDPP16::reset_raw_leaves() {
    for (size_t n_leaf = 0; n_leaf < 16; ++n_leaf) {
        amplitude.leaves[n_leaf] = numeric_limits<double>::quiet_NaN();
        time.leaves[n_leaf] = numeric_limits<double>::quiet_NaN();
    }
    reference_time.leaves[0] = numeric_limits<double>::quiet_NaN();
}

void MDPP16::set_up_raw_branches_for_reading(TTree *tree) {
    tree->SetBranchStatus(amplitude.name.c_str(), 1);
    tree->SetBranchStatus(time.name.c_str(), 1);
    tree->SetBranchStatus(timestamp.name.c_str(), 1);

    tree->SetBranchAddress(amplitude.name.c_str(), amplitude.leaves);
    tree->SetBranchAddress(time.name.c_str(), time.leaves);
    tree->SetBranchAddress(timestamp.name.c_str(), timestamp.leaves);
}

void MDPP16::set_up_raw_branches_for_writing(TTree *tree) {
    tree->Branch(amplitude.name.c_str(), amplitude.leaves,
                 (amplitude.name + "[16]/D").c_str());
    tree->Branch(time.name.c_str(), time.leaves,
                 (time.name + "[16]/D").c_str());
    tree->Branch(timestamp.name.c_str(), timestamp.leaves,
                 (timestamp.name + "[1]/D").c_str());
}