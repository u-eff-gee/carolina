#include "channel.hpp"

double
Channel::polynomial_calibration(double uncalibrated,
                                vector<double> calibration_parameters) const {
    double calibrated =
        calibration_parameters[calibration_parameters.size() - 1];

    for (int i = calibration_parameters.size() - 2; i >= 0; --i) {
        calibrated = calibration_parameters[i] + uncalibrated * calibrated;
    }

    return calibrated;
}

void Channel::calibrate(const int n_entry) {
    energy_calibrated = 0.;
    if (!isnan(module->get_amplitude(leaf))) {
        for (auto ene_cal_par : energy_calibration_parameters) {
            if (n_entry < ene_cal_par.first) {
                energy_calibrated = polynomial_calibration(
                    module->get_amplitude(leaf), ene_cal_par.second);
                break;
            }
        }
        time_calibrated = module->get_time(leaf) * module->tdc_resolution;
        timestamp_calibrated =
            module->get_timestamp(leaf) * INVERSE_VME_CLOCK_FREQUENCY;
    }
}