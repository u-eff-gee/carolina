#pragma once

#include "module.hpp"

struct ScalerModule : Module {

    ScalerModule(const double trigger_frequency)
        : trigger_frequency(trigger_frequency){};

    const double trigger_frequency;

    virtual long long get_counts(const size_t leaf) = 0;
    virtual void add_counts(const size_t leaf, const long long counts) = 0;
};