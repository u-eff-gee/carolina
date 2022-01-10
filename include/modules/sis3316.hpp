#pragma once

#include "TTree.h"

#include "branch.hpp"
#include "digitizer_module.hpp"

struct SIS3316 final : public DigitizerModule {
    SIS3316(const double tdc_resolution)
        : DigitizerModule(tdc_resolution), amplitude_e1("e1"),
          amplitude_e2("e2"), time("time"), time_RF("time_RF"),
          timestamp("timestamp") {}
    ~SIS3316() {}

    Branch<unsigned int, 8> amplitude_e1;
    Branch<unsigned int, 8> amplitude_e2;
    Branch<unsigned int, 8> time;
    Branch<unsigned int, 1> time_RF;
    Branch<unsigned int, 8> timestamp;

    void set_up_raw_branches(TTree *tree) override final;
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

    const double amplitude_conversion = 1. / pow(2, 8);
};