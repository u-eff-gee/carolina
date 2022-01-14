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

#include "TTree.h"

#include "digitizer_module.hpp"

struct SIS3316 final : public DigitizerModule {
    SIS3316(const double tdc_resolution)
        : DigitizerModule(tdc_resolution, "reference_time"), amplitude_e1("e1"),
          amplitude_e2("e2"), time("time"), timestamp("timestamp") {}

    Branch<double, 8> amplitude_e1;
    Branch<double, 8> amplitude_e2;
    Branch<double, 8> time;
    Branch<double, 8> timestamp;

    double get_amplitude(const size_t leaf) const override final {
        return amplitude_conversion *
               (amplitude_e2.leaves[leaf] - amplitude_e1.leaves[leaf]);
    }
    double get_time(const size_t leaf) const override final {
        return time.leaves[leaf];
    }

    double get_timestamp(const size_t leaf) const override final {
        return timestamp.leaves[leaf];
    }

    void set_amplitude(const size_t leaf, const double amp) override final {
        amplitude_e2.leaves[leaf] = (amp * inverse_amplitude_conversion);
        amplitude_e1.leaves[leaf] = 0;
    }

    void set_time(const size_t leaf, const double t) override final {
        time.leaves[leaf] = t;
    }

    void reset_raw_leaves() override final;
    void set_up_raw_branches_for_reading(TTree *tree) override final;
    void set_up_raw_branches_for_writing(TTree *tree) override final;

    const double amplitude_conversion = 1. / pow(2, 8);
    const double inverse_amplitude_conversion = pow(2, 8);
};