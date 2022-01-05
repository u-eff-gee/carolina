#include "energy_sensitive_detector_channel.hpp"

void EnergySensitiveDetectorChannel::reset() {
    energy_calibrated = numeric_limits<double>::quiet_NaN();
    time_calibrated = numeric_limits<double>::quiet_NaN();
    timestamp_calibrated = numeric_limits<double>::quiet_NaN();
    time_vs_time_RF_calibrated = numeric_limits<double>::quiet_NaN();
}