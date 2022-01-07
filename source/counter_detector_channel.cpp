#include "counter_detector_channel.hpp"

#include <limits>

using std::numeric_limits;

CounterDetectorChannel::CounterDetectorChannel(const string name,
                                               const size_t module,
                                               const size_t channel)
    : Channel(name, module, channel), previous_counts(0) {}

void CounterDetectorChannel::reset_calibrated_leaves() {
    // Do not reset previous_counts here.
    // This function is only used to reset values that are actually written to
    // file. previous_counts is just an auxiliary quantity to calculate the
    // rate.
    count_rate = numeric_limits<double>::quiet_NaN();
}