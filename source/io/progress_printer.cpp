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

#include <ctime>

using std::ctime;
using std::time;

#include <cstring>

using std::strtok;

#include <iomanip>

using std::setw;

#include <iostream>

using std::cout;
using std::endl;

#include "progress_printer.hpp"

ProgressPrinter::ProgressPrinter(const long long first, const long long last,
                                 const double update_increment,
                                 const string unit_singular,
                                 const string unit_plural)
    : start_time(time(nullptr)), first(first), last(last),
      n_entries(last - first + 1), inverse_n_entries(1. / (double)n_entries),
      update_increment(update_increment), current_percentage(update_increment) {
    cout << get_time_string() << " : Starting to process " << n_entries << " ";
    if (n_entries == 1) {
        cout << unit_singular;
    } else {
        cout << unit_plural;
    }
    cout << endl;
}

void ProgressPrinter::operator()(const long long index) {
    const double percentage = (index - first + 1) * inverse_n_entries;

    if (percentage >= current_percentage) {
        time_t current_time = time(nullptr);
        cout << get_time_string() << " : " << setw(5)
             << current_percentage * 100. << " % processed in " << setw(5)
             << current_time - start_time << " second(s)." << endl;

        current_percentage =
            ((int)((percentage + update_increment) / update_increment)) *
            update_increment;
    }
}

char *ProgressPrinter::get_time_string() const {
    time_t current_time = time(nullptr);
    return strtok(ctime(&current_time), "\n");
}