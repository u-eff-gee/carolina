#include "channel.hpp"

void Channel::calibrate(const long long n_entry) {
    energy_calibrated = 0.;
    if (!isnan(module->get_amplitude(leaf))) {
        energy_calibrated =
            energy_calibration(n_entry, module->get_amplitude(leaf));
        time_calibrated = time_calibration(energy_calibrated) *
                          module->get_time(leaf) * module->tdc_resolution;
        time_vs_time_RF_calibrated =
            time_calibrated -
            module->get_time_RF(leaf) * module->tdc_resolution;
        timestamp_calibrated =
            module->get_timestamp(leaf) * INVERSE_VME_CLOCK_FREQUENCY;
    } else {
        energy_calibrated = numeric_limits<double>::quiet_NaN();
        time_calibrated = numeric_limits<double>::quiet_NaN();
        time_vs_time_RF_calibrated = numeric_limits<double>::quiet_NaN();
        timestamp_calibrated = numeric_limits<double>::quiet_NaN();
    }
}

void Channel::reset() {
    energy_calibrated = numeric_limits<double>::quiet_NaN();
    time_calibrated = numeric_limits<double>::quiet_NaN();
    timestamp_calibrated = numeric_limits<double>::quiet_NaN();
    time_vs_time_RF_calibrated = numeric_limits<double>::quiet_NaN();
}