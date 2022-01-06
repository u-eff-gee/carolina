#pragma once

#include <string>

using std::string;

#include "histogram_properties.hpp"

struct DetectorGroup {
    const string name;
    const HistogramProperties histogram_properties;
    const HistogramProperties raw_histogram_properties;
};