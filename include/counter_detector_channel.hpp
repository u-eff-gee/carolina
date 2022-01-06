#pragma once

#include "channel.hpp"

struct CounterDetectorChannel final : public Channel {
    CounterDetectorChannel(const string name, const size_t module,
                           const size_t channel);

    void reset_calibrated_leaves() override final;

    long long previous_counts;
    double count_rate;
};