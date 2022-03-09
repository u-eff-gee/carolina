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

#include "scaler_module.hpp"

void ScalerModule::reset_raw_leaves(const vector<bool> counter_values) {
    if (counter_values[0]) {
        reset_raw_counter_leaves();
    }
}

void ScalerModule::set_up_raw_branches_for_reading(
    TTree *tree, const vector<bool> counter_values) {
    if (counter_values[0]) {
        set_up_raw_counter_branches_for_reading(tree);
    }
}

void ScalerModule::set_up_raw_branches_for_writing(
    TTree *tree, const vector<bool> counter_values) {
    if (counter_values[0]) {
        set_up_raw_counter_branches_for_writing(tree);
    }
}