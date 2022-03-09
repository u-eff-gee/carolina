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

#include "polynomial.hpp"

template <typename MainParameter, typename AuxiliaryParameter>
function<double(const MainParameter, const AuxiliaryParameter)>
calibration_function(
    const function<double(const MainParameter, const AuxiliaryParameter)>
        function) {
    return function;
}

template <typename MainParameter, typename AuxiliaryParameter>
function<double(const MainParameter, const AuxiliaryParameter)>
calibration_function(const function<double(const MainParameter)> function) {
    return [&function](const MainParameter main_parameter,
                       const AuxiliaryParameter auxiliary_parameter) {
        return function(main_parameter);
    };
}

template <typename MainParameter, typename AuxiliaryParameter>
function<double(const MainParameter, const AuxiliaryParameter)>
calibration_function(const vector<double> parameters) {
    return Polynomial(parameters);
}

template <typename MainParameter, typename AuxiliaryParameter>
function<double(const MainParameter, const AuxiliaryParameter)>
calibration_function(const string parameter_string) {
    return Polynomial(parameter_string);
}