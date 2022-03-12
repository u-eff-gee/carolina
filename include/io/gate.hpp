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

#include <functional>

using std::function;

struct Gate {
    Gate(const double lower_limit, const double upper_limit)
        : lower_limit(lower_limit), upper_limit(upper_limit) {}

    bool operator()(const double x) const {
        return (x > lower_limit) && (x < upper_limit);
    }

    const double lower_limit;
    const double upper_limit;
};

function<bool(const double)> gate(const function<bool(const double)> function) {
    return function;
}

function<bool(const double)> gate(const double lower_limit,
                                  const double upper_limit) {
    return Gate(lower_limit, upper_limit);
}