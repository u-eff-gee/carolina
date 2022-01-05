#pragma once

#include "channel.hpp"

struct CounterDetectorChannel final : public Channel {
    CounterDetectorChannel(const string name, const size_t module,
                           const size_t channel);

    void reset() override final;

    long long counts, previous_counts;
};