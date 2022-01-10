#pragma once

#include <string>

using std::string;

#include <utility>

using std::pair;

#include <vector>

using std::vector;

#include "histogram_properties.hpp"

struct CoincidenceMatrix {
    const string name;

    const vector<size_t> detectors_x;
    const vector<size_t> detectors_y;

    const HistogramProperties x_axis;
    const HistogramProperties y_axis;

    vector<pair<size_t, size_t>> get_coincidence_pairs() const;
};