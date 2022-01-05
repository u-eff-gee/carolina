#pragma once

#include "module.hpp"

struct ScalerModule : Module {
    virtual long long get_counts(const size_t leaf) = 0;
};