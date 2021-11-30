#pragma once

#include "TTree.h"

#include "branch.hpp"
#include "module.hpp"

struct SIS3316 : public Module {
    SIS3316(const double tdc_resolution)
        : Module(tdc_resolution), amplitude_e1("e1"), amplitude_e2("e2"),
          time("time"), timestamp("timestamp") {}
    ~SIS3316() {}

    Branch<unsigned int, 8> amplitude_e1;
    Branch<unsigned int, 8> amplitude_e2;
    Branch<unsigned int, 8> time;
    Branch<unsigned int, 8> timestamp;

    void activate_branches(TTree *tree) override final;
    void register_branches(TTree *tree) override final;
    vector<string> get_branch_names(const size_t leaf) const override final;
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

    const double amplitude_conversion = 1. / pow(2, 8);
};