#pragma once

#include <cmath>

#include <string>

using std::string;

#include "mdpp16.hpp"
#include "vme.hpp"

double polynomial_calibration(double uncalibrated, vector<double> calibration_parameters){
    double calibrated = calibration_parameters[0];

    for(size_t i = 1; i < calibration_parameters.size(); ++i){
        calibrated += calibration_parameters[i]*pow(uncalibrated, i);
    }

    return calibrated;
}

struct Channel{
    Channel(const string name, MDPP16& module, const size_t leaf, const vector<double> energy_calibration_parameters):
    name(name),
    module(module),
    leaf(leaf),
    energy_calibration_parameters(energy_calibration_parameters),
    energy(module.amplitude.leaves[leaf]),
    time(module.time.leaves[leaf]),
    timestamp(module.timestamp.leaves[leaf]){}

    const string name;
    MDPP16& module;
    const size_t leaf;
    vector<double> energy_calibration_parameters;

    double &energy;
    double &time;
    double &timestamp;

    double energy_calibrated, time_calibrated, timestamp_calibrated;

    void calibrate(){
        if(isnan(energy)){
            energy_calibrated = 0.;
        } else {
            energy_calibrated = polynomial_calibration(energy, energy_calibration_parameters);
            time_calibrated = time*module.tdc_resolution;
            timestamp_calibrated = timestamp*INVERSE_VME_CLOCK_FREQUENCY;
        }
    }
};
