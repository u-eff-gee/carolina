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

#include "mdpp16.hpp"

struct MDPP16_QDC : public MDPP16 {
    MDPP16_QDC(const unsigned int address, const string amplitude_branch_name,
               const string time_branch_name,
               const string reference_time_branch_name,
               const string timestamp_branch_name)
        : MDPP16(address, amplitude_branch_name, time_branch_name,
                 reference_time_branch_name, timestamp_branch_name) {}

    void process_data_word(const u_int32_t word);
};