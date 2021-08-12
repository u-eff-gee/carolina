#pragma once

#include "TTree.h"

#include "branch.hpp"
#include "module.hpp"

struct MDPP16 : public Module {
    MDPP16(const string amplitude_branch_name, const string time_branch_name,
           const string timestamp_branch_name, const double tdc_resolution)
        : Module(tdc_resolution), amplitude(amplitude_branch_name),
          time(time_branch_name), timestamp(timestamp_branch_name) {}

    Branch<double, 16> amplitude;
    Branch<double, 16> time;
    Branch<double, 16> timestamp;

    void register_branches(TTree *tree) override final;
    double get_amplitude(const size_t leaf) const override final {
        return amplitude.leaves[leaf];
    }
    double get_time(const size_t leaf) const override final {
        return time.leaves[leaf];
    }
    double get_timestamp(const size_t leaf) const override final {
        return timestamp.leaves[leaf];
    }
};