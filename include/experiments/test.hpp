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

EnergySensitiveDetectorGroup single{"single",
                                    {65536, -0.125, 16384. - 0.125},
                                    {65536, -0.5, 65536. - 0.5},
                                    {2000, -1000. - 0.5, 1000. - 0.5},
                                    {2000, -1000. - 0.5, 1000. - 0.5}};
EnergySensitiveDetectorGroup segmented{"segmented",
                                       {65536, -0.125, 16384. - 0.125},
                                       {65536, -0.5, 65536. - 0.5},
                                       {2000, -1000. - 0.5, 1000. - 0.5},
                                       {2000, -1000. - 0.5, 1000. - 0.5}};
CounterDetectorGroup scaler{
    "counter", {100000, -5., 1e6 - 5.}, {65536, 0, numeric_limits<int>::max()}};

Analysis analysis(
    {make_shared<MDPP16>("amplitude", "time", "reference_time", "timestamp",
                         0.024),
     make_shared<SIS3316>(0.125), make_shared<V830>(5.)},
    {make_shared<EnergySensitiveDetectorGroup>(single),
     make_shared<EnergySensitiveDetectorGroup>(segmented),
     make_shared<CounterDetectorGroup>(scaler)},
    {make_shared<EnergySensitiveDetector>(
         "sin",
         vector<shared_ptr<Channel>>{
             make_shared<EnergySensitiveDetectorChannel>(
                 "E1", 0, 0, vector<double>{50., 0.1})}),
     make_shared<EnergySensitiveDetector>(
         "seg",
         vector<shared_ptr<Channel>>{
             make_shared<EnergySensitiveDetectorChannel>("E1", 1, 0, "60.,2."),
             make_shared<EnergySensitiveDetectorChannel>("E2", 1, 1, "70. 0.7"),
             make_shared<EnergySensitiveDetectorChannel>(
                 "E3", 1, 2,
                 [](const double amplitude,
                    [[maybe_unused]] const long long n_entry) {
                     return 80. + 0.8 * amplitude;
                 }),
             make_shared<EnergySensitiveDetectorChannel>(
                 "E4", 1, 3,
                 [](const double amplitude,
                    [[maybe_unused]] const long long n_entry) {
                     return 90. + 0.9 * amplitude;
                 })}),
     make_shared<CounterDetector>(
         "cou",
         vector<shared_ptr<Channel>>{
             make_shared<CounterDetectorChannel>("cts", 2, 0)})},
    {{"sin_vs_seg", {0}, {1}, {200, -5., 2000. - 5.}, {200, -5., 2000. - 5.}}});