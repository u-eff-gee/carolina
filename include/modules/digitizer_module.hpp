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

#pragma once

#include <string>

using std::string;

#include <vector>

using std::vector;

#include "TTree.h"

#include "branch.hpp"
#include "module.hpp"

struct DigitizerModule : Module {
    DigitizerModule(const unsigned int address,
                    const string reference_time_branch_name,
                    const string timestamp_branch_name)
        : Module(address), reference_time(reference_time_branch_name),
          timestamp(timestamp_branch_name) {}

    Branch<double, 1> reference_time;
    Branch<double, 1> timestamp;

    void process_data_word(const u_int32_t word) = 0;
    void reset_raw_leaves(const vector<bool> amp_t_tref_ts = {
                              false, false, false, false}) override final;
    void set_up_raw_branches_for_reading(TTree *tree,
                                         const vector<bool> amp_t_tref_ts = {
                                             false, false, false,
                                             false}) override final;
    void set_up_raw_branches_for_writing(TTree *tree,
                                         const vector<bool> amp_t_tref_ts = {
                                             false, false, false,
                                             false}) override final;

    virtual void reset_raw_amplitude_leaves() = 0;
    virtual void reset_raw_time_leaves() = 0;
    virtual void reset_raw_reference_time_leaves() = 0;
    virtual void reset_raw_timestamp_leaves() = 0;
    virtual void set_up_raw_amplitude_branches_for_reading(TTree *tree) = 0;
    virtual void set_up_raw_time_branches_for_reading(TTree *tree) = 0;
    virtual void
    set_up_raw_reference_time_branches_for_reading(TTree *tree) = 0;
    virtual void set_up_raw_timestamp_branches_for_reading(TTree *tree) = 0;
    virtual void set_up_raw_amplitude_branches_for_writing(TTree *tree) = 0;
    virtual void set_up_raw_time_branches_for_writing(TTree *tree) = 0;
    virtual void
    set_up_raw_reference_time_branches_for_writing(TTree *tree) = 0;
    virtual void set_up_raw_timestamp_branches_for_writing(TTree *tree) = 0;

    virtual double get_amplitude(const size_t leaf) const = 0;
    virtual double get_time(const size_t leaf) const = 0;
    double get_reference_time() const { return reference_time.leaves[0]; };
    virtual double get_timestamp() { return timestamp.leaves[0]; };

    virtual void set_amplitude(const size_t leaf, const double amplitude) = 0;
    virtual void set_time(const size_t leaf, const double time) = 0;
    void set_reference_time(const double ref_time) {
        reference_time.leaves[0] = ref_time;
    };
    void set_timestamp(const double ts) { timestamp.leaves[0] = ts; };
};