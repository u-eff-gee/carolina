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
           const string reference_time_branch_name,
           const string timestamp_branch_name)
        : DigitizerModule(reference_time_branch_name, timestamp_branch_name),
          amplitude(amplitude_branch_name), time(time_branch_name) {}

    Branch<double, 16> amplitude;
    Branch<double, 16> time;

    double get_amplitude(const size_t leaf) const override final {
        return amplitude.leaves[leaf];
    }
    double get_time(const size_t leaf) const override final {
        return time.leaves[leaf];
    }

    void set_amplitude(const size_t leaf, const double amp) override final {
        amplitude.leaves[leaf] = amp;
    }

    void set_time(const size_t leaf, const double t) override final {
        time.leaves[leaf] = t;
    }

    void reset_raw_amplitude_leaves() override final;
    void reset_raw_time_leaves() override final;
    void reset_raw_reference_time_leaves() override final;
    void reset_raw_timestamp_leaves() override final;

    void set_up_raw_amplitude_branches_for_reading(TTree *tree) override final;
    void set_up_raw_time_branches_for_reading(TTree *tree) override final;
    void
    set_up_raw_reference_time_branches_for_reading(TTree *tree) override final;
    void set_up_raw_timestamp_branches_for_reading(TTree *tree) override final;

    void set_up_raw_amplitude_branches_for_writing(TTree *tree) override final;
    void set_up_raw_time_branches_for_writing(TTree *tree) override final;
    void
    set_up_raw_reference_time_branches_for_writing(TTree *tree) override final;
    void set_up_raw_timestamp_branches_for_writing(TTree *tree) override final;
};