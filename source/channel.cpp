#include "channel.hpp"

void Channel::reset() {
    energy_calibrated = numeric_limits<double>::quiet_NaN();
    time_calibrated = numeric_limits<double>::quiet_NaN();
    timestamp_calibrated = numeric_limits<double>::quiet_NaN();
    time_vs_time_RF_calibrated = numeric_limits<double>::quiet_NaN();
}