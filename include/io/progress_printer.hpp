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

class ProgressPrinter {

  public:
    ProgressPrinter(const long long first, const long long last,
                    const double update_increment = 0.01,
                    const string unit_singular = "event",
                    const string unit_plural = "events");

    void operator()(const long long index);

  private:
    char *get_time_string() const;

    const time_t start_time;
    const long long first, last, n_entries;
    const double inverse_n_entries, update_increment;
    double current_percentage;
};