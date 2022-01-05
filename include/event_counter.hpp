#pragma once

#include "branch.hpp"
#include "scaler_module.hpp"

template <size_t n_leaves> struct EventCounter final : public ScalerModule {
    EventCounter() : counter_values("counter_values") {}
    ~EventCounter() {}

    Branch<double, n_leaves> counter_values;

    void activate_branches([[maybe_unused]] TTree *tree) override final{};
    void register_branches([[maybe_unused]] TTree *tree) override final{};
};