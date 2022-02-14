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

#include <memory>

using std::make_shared;

#include "analysis_include.hpp"

auto single = make_shared<EnergySensitiveDetectorGroup>(
    "single", Histogram{65536, -0.125, 16384. - 0.125},
    Histogram{65536, -0.5, 65536. - 0.5},
    Histogram{2000, -1000. - 0.5, 1000. - 0.5},
    Histogram{2000, -1000. - 0.5, 1000. - 0.5});
auto segmented = make_shared<EnergySensitiveDetectorGroup>(
    "segmented", Histogram{65536, -0.125, 16384. - 0.125},
    Histogram{65536, -0.5, 65536. - 0.5},
    Histogram{2000, -1000. - 0.5, 1000. - 0.5},
    Histogram{2000, -1000. - 0.5, 1000. - 0.5});
auto scaler = make_shared<CounterDetectorGroup>(
    "counter", Histogram{100000, -5., 1e6 - 5.},
    Histogram{65536, 0, numeric_limits<int>::max()});

Analysis analysis(
    {make_shared<MDPP16>("amplitude", "time", "reference_time", "timestamp",
                         0.024),
     make_shared<SIS3316>(0.125), make_shared<V830>(5.)},
    {single, segmented, scaler},
    {make_shared<EnergySensitiveDetector>(
         "sin",
         vector<EnergySensitiveDetectorChannel>{
             {"E1", 0, 0, vector<double>{50., 0.1}}},
         single),
     make_shared<EnergySensitiveDetector>(
         "seg",
         vector<EnergySensitiveDetectorChannel>{
             {"E1", 1, 0, "60.,2."},
             {"E2", 1, 1, "70. 0.7"},
             {"E3", 1, 2,
              [](const double amplitude,
                 [[maybe_unused]] const long long n_entry) {
                  return 80. + 0.8 * amplitude;
              }},
             {"E4", 1, 3,
              [](const double amplitude,
                 [[maybe_unused]] const long long n_entry) {
                  return 90. + 0.9 * amplitude;
              }}},
         segmented),
     make_shared<CounterDetector>("cou",
                                  vector<CounterDetectorChannel>{{"cts", 2, 0}},
                                  scaler)},
    {{"sin_vs_seg", {0}, {1}, {200, -5., 2000. - 5.}, {200, -5., 2000. - 5.}}});