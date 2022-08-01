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

bool MDPP16::data_found(const u_int32_t word) {
    return (word & data_found_mask) == data_found_flag;
}

bool MDPP16::eoe_found(const u_int32_t word) {
    return (word & eoe_mask) == eoe_found_flag;
}

bool MDPP16::extended_ts_found(const u_int32_t word) {
    return (word & extended_ts_mask) == extended_ts_flag;
}

u_int32_t MDPP16::get_data_length(const u_int32_t word) {
    return word & data_length_mask;
}

u_int32_t MDPP16::get_high_stamp(const u_int32_t word) {
    return word & high_stamp_mask;
}

u_int32_t MDPP16::get_low_stamp(const u_int32_t word) {
    return word & low_stamp_mask;
}

u_int32_t MDPP16::get_module_id(const u_int32_t word) {
    return (word & module_id_mask) / module_id_offset;
}

bool MDPP16::header_found(const u_int32_t word) {
    return (word & header_mask) == header_found_flag;
}

void MDPP16::reset_raw_amplitude_leaves() {
    for (size_t n_leaf = 0; n_leaf < 16; ++n_leaf) {
        amplitude.leaves[n_leaf] = numeric_limits<double>::quiet_NaN();
    }
}
void MDPP16::reset_raw_time_leaves() {
    for (size_t n_leaf = 0; n_leaf < 16; ++n_leaf) {
        time.leaves[n_leaf] = numeric_limits<double>::quiet_NaN();
    }
}
void MDPP16::reset_raw_reference_time_leaves() {
    reference_time.leaves[0] = numeric_limits<double>::quiet_NaN();
}

void MDPP16::reset_raw_timestamp_leaves() {
    timestamp.leaves[0] = 0;
}

void MDPP16::set_up_raw_amplitude_branches_for_reading(TTree *tree) {
    tree->SetBranchStatus(amplitude.name.c_str(), 1);
    tree->SetBranchAddress(amplitude.name.c_str(), amplitude.leaves);
}

void MDPP16::set_up_raw_time_branches_for_reading(TTree *tree) {
    tree->SetBranchStatus(time.name.c_str(), 1);
    tree->SetBranchAddress(time.name.c_str(), time.leaves);
}

void MDPP16::set_up_raw_reference_time_branches_for_reading(TTree *tree) {
    tree->SetBranchStatus((reference_time.name).c_str(), 1);
    tree->SetBranchAddress((reference_time.name).c_str(),
                           &reference_time.leaves[0]);
}

void MDPP16::set_up_raw_timestamp_branches_for_reading(TTree *tree) {
    tree->SetBranchStatus(timestamp.name.c_str(), 1);
    tree->SetBranchAddress(timestamp.name.c_str(), timestamp.leaves);
}

void MDPP16::set_up_raw_amplitude_branches_for_writing(TTree *tree) {
    tree->Branch(amplitude.name.c_str(), amplitude.leaves,
                 (amplitude.name + "[16]/D").c_str());
}

void MDPP16::set_up_raw_time_branches_for_writing(TTree *tree) {
    tree->Branch(time.name.c_str(), time.leaves,
                 (time.name + "[16]/D").c_str());
}

void MDPP16::set_up_raw_reference_time_branches_for_writing(TTree *tree) {
    tree->Branch(reference_time.name.c_str(), &reference_time.leaves[0]);
}

void MDPP16::set_up_raw_timestamp_branches_for_writing(TTree *tree) {
    tree->Branch(timestamp.name.c_str(), timestamp.leaves,
                 (timestamp.name + "[1]/l").c_str());
}