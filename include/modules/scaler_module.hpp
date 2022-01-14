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

#include "module.hpp"

struct ScalerModule : Module {

    ScalerModule(const double trigger_frequency)
        : trigger_frequency(trigger_frequency){};

    const double trigger_frequency;

    virtual long long get_counts(const size_t leaf) = 0;
    virtual void add_counts(const size_t leaf, const long long counts) = 0;
};