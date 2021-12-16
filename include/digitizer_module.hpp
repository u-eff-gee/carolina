#pragma once

#include <string>

using std::string;

#include <vector>

using std::vector;

#include "TTree.h"

#include "module.hpp"

struct DigitizerModule : Module {
    DigitizerModule(const double tdc_resolution)
        : tdc_resolution(tdc_resolution) {}

    const double tdc_resolution;

    virtual double get_amplitude(const size_t leaf) const = 0;
    virtual double get_time(const size_t leaf) const = 0;
    virtual double get_time_RF(const size_t leaf) const = 0;
    virtual double get_timestamp(const size_t leaf) const = 0;
};