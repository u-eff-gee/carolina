#pragma once

#include "TTree.h"

#include "branch.hpp"
#include "digitizer_module.hpp"

struct SIS3316 final : public DigitizerModule {
    SIS3316(const double tdc_resolution)
        : DigitizerModule(tdc_resolution), amplitude_e1("e1"),
          amplitude_e2("e2"), time("time"), time_RF("time_RF"),
          timestamp("timestamp") {}

    Branch<unsigned int, 8> amplitude_e1;
    Branch<unsigned int, 8> amplitude_e2;
    Branch<unsigned int, 8> time;
    Branch<unsigned int, 1> time_RF;
    Branch<unsigned int, 8> timestamp;

    double get_amplitude(const size_t leaf) const override final {
        return amplitude_conversion *
               (amplitude_e2.leaves[leaf] - amplitude_e1.leaves[leaf]);
    }
    double get_time(const size_t leaf) const override final {
        return time.leaves[leaf];
    }
    double get_time_RF([
        [maybe_unused]] const size_t leaf) const override final {
        return time_RF.leaves[0];
    }
    double get_timestamp(const size_t leaf) const override final {
        return timestamp.leaves[leaf];
    }

    void set_amplitude(const size_t leaf, const double amp) override final {
        amplitude_e2.leaves[leaf] = (unsigned int) amp * inverse_amplitude_conversion;
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