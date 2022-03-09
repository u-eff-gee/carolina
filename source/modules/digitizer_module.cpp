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

#include "digitizer_module.hpp"

void DigitizerModule::reset_raw_leaves(const vector<bool> amp_t_tref_ts) {
    if (amp_t_tref_ts[0]) {
        reset_raw_amplitude_leaves();
    }
    if (amp_t_tref_ts[1]) {
        reset_raw_time_leaves();
    }
    if (amp_t_tref_ts[2]) {
        reset_raw_reference_time_leaves();
    }
    if (amp_t_tref_ts[3]) {
        reset_raw_timestamp_leaves();
    }
}

void DigitizerModule::set_up_raw_branches_for_reading(
    TTree *tree, const vector<bool> amp_t_tref_ts) {
    if (amp_t_tref_ts[0]) {
        set_up_raw_amplitude_branches_for_reading(tree);
    }
    if (amp_t_tref_ts[1]) {
        set_up_raw_time_branches_for_reading(tree);
    }
    if (amp_t_tref_ts[2]) {
        set_up_raw_reference_time_branches_for_reading(tree);
    }
    if (amp_t_tref_ts[3]) {
        set_up_raw_timestamp_branches_for_reading(tree);
    }
}

void DigitizerModule::set_up_raw_branches_for_writing(
    TTree *tree, const vector<bool> amp_t_tref_ts) {
    if (amp_t_tref_ts[0]) {
        set_up_raw_amplitude_branches_for_writing(tree);
    }
    if (amp_t_tref_ts[1]) {
        set_up_raw_time_branches_for_writing(tree);
    }
    if (amp_t_tref_ts[2]) {
        set_up_raw_reference_time_branches_for_writing(tree);
    }
    if (amp_t_tref_ts[3]) {
        set_up_raw_timestamp_branches_for_writing(tree);
    }
}