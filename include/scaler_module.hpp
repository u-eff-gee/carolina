#pragma once

#include "module.hpp"

struct ScalerModule : Module {
    ScalerModule(const double trigger_frequency)
        : trigger_frequency(trigger_frequency) {}

    const double trigger_frequency;
};