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

#include "TTree.h"

#include "branch.hpp"
#include "module.hpp"

struct DigitizerModule : Module {
    DigitizerModule(const double tdc_resolution,
                    const string time_RF_branch_name)
        : tdc_resolution(tdc_resolution), time_RF(time_RF_branch_name) {}

    const double tdc_resolution;

    Branch<double, 1> time_RF;

    virtual double get_amplitude(const size_t leaf) const = 0;
    virtual double get_time(const size_t leaf) const = 0;
    double get_time_RF() const { return time_RF.leaves[0]; };
    virtual double get_timestamp(const size_t leaf) const = 0;

    virtual void set_amplitude(const size_t leaf, const double amplitude) = 0;
    virtual void set_time(const size_t leaf, const double time) = 0;
    void set_time_RF(const double time) { time_RF.leaves[0] = time; };
};