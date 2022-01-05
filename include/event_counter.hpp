#pragma once

#include "branch.hpp"
#include "scaler_module.hpp"

template <size_t n_leaves> struct EventCounter final : public ScalerModule {
    EventCounter() : counter_values("counter_values") {
        for(size_t leaf = 0; leaf < n_leaves; ++leaf){
            counter_values.leaves[leaf] = 0;
        }
    }
    ~EventCounter() {}

    Branch<long long, n_leaves> counter_values;

    void activate_branches([[maybe_unused]] TTree *tree) override final{};
    void register_branches([[maybe_unused]] TTree *tree) override final{};

    long long get_counts(const size_t leaf) override final {
        return ++counter_values.leaves[leaf];
    }
};