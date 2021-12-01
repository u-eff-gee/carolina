#pragma once

#include <string>

using std::string;

#include <vector>

using std::vector;

#include "histogram_properties.hpp"

struct CoincidenceMatrix {
    const string name;

    const vector<size_t> detectors;

    const HistogramProperties x_axis;
    const HistogramProperties y_axis;

    const bool symmetrize;
};