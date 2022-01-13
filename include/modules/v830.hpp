#pragma once

#include "branch.hpp"
#include "scaler_module.hpp"

struct V830 final : public ScalerModule {
    V830(const double trigger_frequency)
        : ScalerModule(trigger_frequency), counter_values("counter_values") {
        for (size_t i = 0; i < 32; ++i) {
            counter_values.leaves[i] = 0.;
        }
    }
    ~V830() {}

    Branch<double, 32> counter_values;

    long long get_counts(const size_t leaf) override final {
        return counter_values.leaves[leaf];
    }

    void add_counts(const size_t leaf, const long long counts) override final {
        counter_values.leaves[leaf] += (double)counts;
    }

    void reset_raw_leaves() override final;
    void set_up_raw_branches_for_reading(TTree *tree) override final;
    void set_up_raw_branches_for_writing(TTree *tree) override final;
};