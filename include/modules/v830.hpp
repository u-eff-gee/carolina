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

    void set_up_raw_branches(TTree *tree) override final;

    long long get_counts(const size_t leaf) override final {
        return counter_values.leaves[leaf];
    }
};