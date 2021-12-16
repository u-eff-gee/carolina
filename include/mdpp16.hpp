#pragma once

#include "TTree.h"

#include "branch.hpp"
#include "digitizer_module.hpp"

struct MDPP16 final : public DigitizerModule {
    MDPP16(const string amplitude_branch_name, const string time_branch_name,
           const string timestamp_branch_name, const double tdc_resolution)
        : DigitizerModule(tdc_resolution), amplitude(amplitude_branch_name),
          time(time_branch_name), timestamp(timestamp_branch_name) {}

    Branch<double, 16> amplitude;
    Branch<double, 16> time;
    Branch<double, 16> timestamp;

    void activate_branches(TTree *tree) override final;
    void register_branches(TTree *tree) override final;
    double get_amplitude(const size_t leaf) const override final {
        return amplitude.leaves[leaf];
    }
    double get_time(const size_t leaf) const override final {
        return time.leaves[leaf];
    }
    double get_time_RF([
        [maybe_unused]] const size_t leaf) const override final {
        return 0.;
    };
    double get_timestamp(const size_t leaf) const override final {
        return timestamp.leaves[leaf];
    }
};