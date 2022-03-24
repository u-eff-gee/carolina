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

const u_int32_t header_mask = 0xC0000000;
const u_int32_t header_found_flag = 0x40000000;
const u_int32_t data_length_mask = 0x000003FF;
const u_int32_t module_id_mask = 0x00FF0000;
const u_int32_t module_id_offset = 0x10000;
const u_int32_t data_mask = 0xF0000000;
const u_int32_t data_found_flag = 0x10000000;
const u_int32_t eoe_mask = 0xC0000000;
const u_int32_t eoe_found_flag = eoe_mask;

const u_int32_t channel_address_mask = 0x003F0000;
const u_int32_t channel_address_offset = 0x0010000;