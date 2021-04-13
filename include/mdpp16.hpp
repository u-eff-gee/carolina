#pragma once

#include "TTree.h"

#include "branch.hpp"

struct MDPP16{
    Branch<double, 16> amplitude;
    Branch<double, 16> time;
    Branch<double, 16> timestamp;

    const double tdc_resolution;

    void register_branches(TTree* tree);
};