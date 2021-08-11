#pragma once

#include <cmath>

#include <string>

using std::string;

#include "module.hpp"
#include "vme.hpp"

double polynomial_calibration(double uncalibrated, vector<double> calibration_parameters){
    double calibrated = calibration_parameters[calibration_parameters.size()-1];

    for(int i = calibration_parameters.size()-2; i >= 0; --i){
        calibrated = calibration_parameters[i] + uncalibrated*calibrated;
    }

    return calibrated;
}

struct Channel{
    Channel(const string name, Module& module, const size_t leaf, const vector<double> energy_calibration_parameters, const double amplitude_threshold=0.):
    name(name),
    module(module),
    leaf(leaf),
    energy_calibration_parameters(energy_calibration_parameters),
    amplitude_threshold(amplitude_threshold)
    {}

    const string name;
    Module &module;
    const size_t leaf;
    vector<double> energy_calibration_parameters;

    double energy_calibrated, time_calibrated, timestamp_calibrated;
    const double amplitude_threshold;

    double get_amplitude() const { return module.get_amplitude(leaf); }
    double get_time() const { return module.get_time(leaf); }
    double get_timestamp() const { return module.get_timestamp(leaf); }

    void calibrate(const int n_entry){
        if(isnan(module.get_amplitude(leaf))){
            energy_calibrated = 0.;
        } else {
            energy_calibrated = polynomial_calibration(module.get_amplitude(leaf), energy_calibration_parameters);
            time_calibrated = module.get_time(leaf)*module.tdc_resolution;
            timestamp_calibrated = module.get_timestamp(leaf)*INVERSE_VME_CLOCK_FREQUENCY;
        }
    }
};
