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

#include <iostream>

using std::cout;
using std::endl;

struct Polynomial {
    Polynomial(const vector<double> parameters) : parameters(parameters) {
        cout << "Polynomial initialized with parameters: ";
        for (auto p : parameters) {
            cout << p << ", ";
        }
        cout << endl;
    }
    Polynomial(const string parameter_string)
        : parameters(parse_string(parameter_string)) {}
    const vector<double> parameters;

    double operator()(const double x) const;
    double operator()(const double x, const long long i) const;

    vector<double> parse_string(const string parameters) const;
};