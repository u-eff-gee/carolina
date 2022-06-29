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
    SIS3316(const unsigned int address)
        : DigitizerModule(address, "reference_time", "timestamp"),
          amplitude_e1("e1"), amplitude_e2("e2"), time("time") {}

    Branch<unsigned int, 8> amplitude_e1;
    Branch<unsigned int, 8> amplitude_e2;
    Branch<unsigned int, 8> time;

    double get_amplitude(const size_t leaf) const override final {
        return amplitude_conversion *
               (amplitude_e2.leaves[leaf] - amplitude_e1.leaves[leaf]);
    }
    double get_time(const size_t leaf) const override final {
        return time.leaves[leaf];
    }

    void set_amplitude(const size_t leaf, const double amp) override final {
        amplitude_e2.leaves[leaf] = (amp * inverse_amplitude_conversion);
        amplitude_e1.leaves[leaf] = 0;
    }

    void set_time(const size_t leaf, const double t) override final {
        time.leaves[leaf] = t;
    }

    bool data_found([[maybe_unused]] const u_int32_t word) override final {
        return false;
    }
    u_int32_t get_data_length([
        [maybe_unused]] const u_int32_t word) override final {
        return 0;
    };
    u_int32_t get_module_id([
        [maybe_unused]] const u_int32_t word) override final {
        return 0;
    };
    bool header_found([[maybe_unused]] const u_int32_t word) override final {
        return false;
    };
    void process_data_word([
        [maybe_unused]] const u_int32_t word) override final{};
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

    const double amplitude_conversion = 1. / pow(2, 8);
    const double inverse_amplitude_conversion = pow(2, 8);
};