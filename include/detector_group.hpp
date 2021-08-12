#pragma once

#include <string>

using std::string;

#include "histogram_properties.hpp"

struct DetectorGroup {
    const string name;
    const HistogramProperties energy_histogram_properties;
    const HistogramProperties energy_raw_histogram_properties;
    const HistogramProperties time_difference_histogram_properties;
};