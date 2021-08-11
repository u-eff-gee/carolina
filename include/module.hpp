#pragma once

#include "TTree.h"

struct Module{
    Module(const double tdc_resolution):
        tdc_resolution(tdc_resolution)
    {}

    const double tdc_resolution;

    virtual void register_branches(TTree* tree) = 0;
    virtual double get_amplitude(const size_t leaf) const = 0;
    virtual double get_time(const size_t leaf) const = 0;
    virtual double get_timestamp(const size_t leaf) const = 0;
};