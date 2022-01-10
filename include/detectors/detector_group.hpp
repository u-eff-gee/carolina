#pragma once

#include <string>

using std::string;

#include "histogram_properties.hpp"

struct DetectorGroup {
    DetectorGroup(const string name,
                  const HistogramProperties histogram_properties,
                  const HistogramProperties raw_histogram_properties)
        : name(name), histogram_properties(histogram_properties),
          raw_histogram_properties(raw_histogram_properties) {}
    virtual ~DetectorGroup(){};

    const string name;
    const HistogramProperties histogram_properties, raw_histogram_properties;
};

struct CounterDetectorGroup final : public DetectorGroup {
    CounterDetectorGroup(const string name,
                         const HistogramProperties histogram_properties,
                         const HistogramProperties raw_histogram_properties)
        : DetectorGroup{name, histogram_properties, raw_histogram_properties} {}
};

struct EnergySensitiveDetectorGroup final : public DetectorGroup {
    EnergySensitiveDetectorGroup(
        const string name, const HistogramProperties histogram_properties,
        const HistogramProperties raw_histogram_properties,
        const HistogramProperties time_histogram_properties,
        const HistogramProperties raw_time_histogram_properties)
        : DetectorGroup{name, histogram_properties, raw_histogram_properties},
          time_histogram_properties(time_histogram_properties),
          raw_time_histogram_properties(raw_time_histogram_properties) {}

    const HistogramProperties time_histogram_properties,
        raw_time_histogram_properties;
};