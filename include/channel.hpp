#pragma once

#include <cmath>

#include <string>

#include <utility>

using std::pair;

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
    Channel(const string name, Module& module, const size_t leaf, const vector<pair<int, vector<double>>> energy_calibration_parameters, const double amplitude_threshold=0.):
    name(name),
    module(module),
    leaf(leaf),
    energy_calibration_parameters(energy_calibration_parameters),
    amplitude_threshold(amplitude_threshold)
    {}

    const string name;
    Module &module;
    const size_t leaf;
    vector<pair<int, vector<double>>> energy_calibration_parameters;

    double energy_calibrated, time_calibrated, timestamp_calibrated;
    const double amplitude_threshold;

    double get_amplitude() const { return module.get_amplitude(leaf); }
    double get_time() const { return module.get_time(leaf); }
    double get_timestamp() const { return module.get_timestamp(leaf); }

    void calibrate(const int n_entry){
        if(isnan(module.get_amplitude(leaf))){
            energy_calibrated = 0.;
        } else {
            for(auto ene_cal_par: energy_calibration_parameters){
                if(n_entry < ene_cal_par.first){
                    energy_calibrated = polynomial_calibration(module.get_amplitude(leaf), ene_cal_par.second);
                    break;
                }
            }
            time_calibrated = module.get_time(leaf)*module.tdc_resolution;
            timestamp_calibrated = module.get_timestamp(leaf)*INVERSE_VME_CLOCK_FREQUENCY;
        }
    }
};
