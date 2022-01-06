#include "counter_detector_channel.hpp"

CounterDetectorChannel::CounterDetectorChannel(const string name,
                                               const size_t module,
                                               const size_t channel)
    : Channel(name, module, channel), counts(0), previous_counts(0) {}

void CounterDetectorChannel::reset_calibrated_leaves() {
    counts = 0;
    previous_counts = 0;
}