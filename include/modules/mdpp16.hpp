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

struct MDPP16 final : public DigitizerModule {
    MDPP16(const string amplitude_branch_name, const string time_branch_name,
           const string time_RF_branch_name, const string timestamp_branch_name,
           const double tdc_resolution)
        : DigitizerModule(tdc_resolution, time_RF_branch_name),
          amplitude(amplitude_branch_name), time(time_branch_name),
          timestamp(timestamp_branch_name) {}

    Branch<double, 16> amplitude;
    Branch<double, 16> time;
    Branch<double, 16> timestamp;

    double get_amplitude(const size_t leaf) const override final {
        return amplitude.leaves[leaf];
    }
    double get_time(const size_t leaf) const override final {
        return time.leaves[leaf];
    }

    double get_timestamp(const size_t leaf) const override final {
        return timestamp.leaves[leaf];
    }

    void set_amplitude(const size_t leaf, const double amp) override final {
        amplitude.leaves[leaf] = amp;
    }

    void set_time(const size_t leaf, const double t) override final {
        time.leaves[leaf] = t;
    }

    void reset_raw_leaves() override final;
    void set_up_raw_branches_for_reading(TTree *tree) override final;
    void set_up_raw_branches_for_writing(TTree *tree) override final;
};