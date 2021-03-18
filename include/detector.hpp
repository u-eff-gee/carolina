#pragma once

#include <string>

using std::string;

#include <vector>

using std::vector;

#include "channel.hpp"
#include "detector_group.hpp"

struct Detector{
    const string name;
    const vector<Channel> channels;
    const DetectorGroup group;

    const HistogramProperties energy_histogram_properties;
    const HistogramProperties timestamp_difference_histogram_properties;
};