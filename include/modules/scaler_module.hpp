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

#include <vector>

using std::vector;

#include "module.hpp"

struct ScalerModule : Module {

    ScalerModule(const unsigned int address, const double trigger_frequency)
        : Module(address), trigger_frequency(trigger_frequency){};

    const double trigger_frequency;

    void process_data_word(const u_int32_t word) = 0;
    void reset_raw_leaves(const vector<bool> counter_values = {
                              false}) override final;
    void set_up_raw_branches_for_reading(TTree *tree,
                                         const vector<bool> counter_values = {
                                             false}) override final;
    void set_up_raw_branches_for_writing(TTree *tree,
                                         const vector<bool> counter_values = {
                                             false}) override final;
    virtual void reset_raw_counter_leaves() = 0;
    virtual void set_up_raw_counter_branches_for_reading(TTree *tree) = 0;
    virtual void set_up_raw_counter_branches_for_writing(TTree *tree) = 0;

    virtual long long get_counts(const size_t leaf) = 0;
    virtual void add_counts(const size_t leaf, const long long counts) = 0;
};