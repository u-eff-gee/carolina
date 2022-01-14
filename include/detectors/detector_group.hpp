/*
     This file is part of carolina.

    carolina is free software: you can redistribute it and/or modify it under
   the terms of the GNU General Public License as published by the Free Software
   Foundation, either version 3 of the License, or (at your option) any later
   version.

    carolina is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
    more details.

    You should have received a copy of the GNU General Public License along with
    carolina. If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#include <string>

using std::string;

#include "histogram_properties.hpp"

struct DetectorGroup {
    DetectorGroup(const string name, const Histogram histogram_properties,
                  const Histogram raw_histogram_properties)
        : name(name), histogram_properties(histogram_properties),
          raw_histogram_properties(raw_histogram_properties) {}
    virtual ~DetectorGroup(){};

    const string name;
    const Histogram histogram_properties, raw_histogram_properties;
};

struct CounterDetectorGroup final : public DetectorGroup {
    CounterDetectorGroup(const string name,
                         const Histogram histogram_properties,
                         const Histogram raw_histogram_properties)
        : DetectorGroup{name, histogram_properties, raw_histogram_properties} {}
};

struct EnergySensitiveDetectorGroup final : public DetectorGroup {
    EnergySensitiveDetectorGroup(const string name,
                                 const Histogram histogram_properties,
                                 const Histogram raw_histogram_properties,
                                 const Histogram time_histogram_properties,
                                 const Histogram raw_time_histogram_properties)
        : DetectorGroup{name, histogram_properties, raw_histogram_properties},
          time_histogram_properties(time_histogram_properties),
          raw_time_histogram_properties(raw_time_histogram_properties) {}

    const Histogram time_histogram_properties, raw_time_histogram_properties;
};