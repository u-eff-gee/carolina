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

struct Histogram {
    Histogram(const unsigned int n_bins, const double lower_edge_of_first_bin,
              const double upper_edge_of_last_bin)
        : n_bins(n_bins), lower_edge_of_first_bin(lower_edge_of_first_bin),
          upper_edge_of_last_bin(upper_edge_of_last_bin) {}

    const unsigned int n_bins;
    const double lower_edge_of_first_bin;
    const double upper_edge_of_last_bin;
};