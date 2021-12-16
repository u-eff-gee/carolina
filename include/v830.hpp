#pragma once

#include "branch.hpp"
#include "scaler_module.hpp"

struct V830 final : public ScalerModule {
    V830(const double trigger_frequency)
        : ScalerModule(trigger_frequency), counter_values("counter_values") {}
    ~V830() {}

    Branch<double, 32> counter_values;

    void activate_branches(TTree *tree) override final;
    void register_branches(TTree *tree) override final;
};