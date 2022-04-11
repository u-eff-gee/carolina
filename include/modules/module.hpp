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

#include "TTree.h"

struct Module {
    Module(const unsigned int address) : address(address) {}
    const unsigned int address;
    virtual bool data_found(const u_int32_t word) = 0;
    virtual u_int32_t get_data_length(const u_int32_t word) = 0;
    virtual u_int32_t get_module_id(const u_int32_t word) = 0;
    virtual bool header_found(const u_int32_t word) = 0;
    virtual void process_data_word(const uint32_t word) = 0;
    virtual void reset_raw_leaves(const vector<bool> flags) = 0;
    virtual void set_up_raw_branches_for_reading(TTree *tree,
                                                 const vector<bool> flags) = 0;
    virtual void set_up_raw_branches_for_writing(TTree *tree,
                                                 const vector<bool> flags) = 0;
};