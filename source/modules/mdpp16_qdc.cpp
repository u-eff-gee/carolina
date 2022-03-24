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

#include "mdpp16_qdc.hpp"

void MDPP16_QDC::process_data_word(const u_int32_t word) {
    channel_address = (word & channel_address_mask) / channel_address_offset;
    data_word = word & data_mask;
    if (channel_address < 16) {
        set_amplitude(channel_address, (double)data_word);
    } else if (channel_address < 32) {
        set_time(channel_address - 16, (double)data_word);
    } else if (channel_address < 34) {
        set_reference_time((double)data_word);
    }
};