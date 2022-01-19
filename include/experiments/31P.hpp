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

EnergySensitiveDetectorGroup clover{
    "clover",
    {65536, -0.125, 16383.875},
    {65536, -0.5, 65535.5},
    {8192, -4096 - 0.5, 4096 - 0.5},
    {8192, (-4096 - 0.5) * 0.125, (4096 - 0.5) * 0.125}};
EnergySensitiveDetectorGroup coaxial{
    "coaxial",
    {65536, -0.125, 16383.875},
    {65536, -0.5, 65535.5},
    {8192, -4096 - 0.5, 4096 - 0.5},
    {8192, (-4096 - 0.5) * 0.125, (4096 - 0.5) * 0.125}};

CounterDetectorGroup paddle{
    "paddle", {100000, -5., 1e6 - 5.}, {65536, 0, numeric_limits<int>::max()}};

CounterDetectorGroup pulser{
    "pulser", {100000, -5., 1e6 - 5.}, {65536, 0, numeric_limits<int>::max()}};

const double tdc_resolution =
    0.024; // in nanoseconds, tdc resolution in nanoseconds per bin

Analysis analysis(
    {
        make_shared<MDPP16>("clover_90.amplitude", "clover_90.channel_time",
                            "clover_90.trigger_time",
                            "clover_90.module_timestamp", tdc_resolution),
        make_shared<MDPP16>("clover_135.amplitude", "clover_135.channel_time",
                            "clover_135.trigger_time",
                            "clover_135.module_timestamp", tdc_resolution),
        make_shared<MDPP16>("zero_degree.amplitude", "zero_degree.channel_time",
                            "zero_degree.trigger_time",
                            "zero_degree.module_timestamp", tdc_resolution),
        make_shared<V830>(5.),
    },
    {make_shared<EnergySensitiveDetectorGroup>(clover),
     make_shared<EnergySensitiveDetectorGroup>(clover),
     make_shared<EnergySensitiveDetectorGroup>(clover),
     make_shared<EnergySensitiveDetectorGroup>(clover),
     make_shared<EnergySensitiveDetectorGroup>(clover),
     make_shared<EnergySensitiveDetectorGroup>(clover),
     make_shared<EnergySensitiveDetectorGroup>(clover),
     make_shared<EnergySensitiveDetectorGroup>(coaxial),
     make_shared<CounterDetectorGroup>(paddle),
     make_shared<CounterDetectorGroup>(pulser)},
    {make_shared<EnergySensitiveDetector>(
         "clover_1",
         vector<shared_ptr<Channel>>{
             make_shared<EnergySensitiveDetectorChannel>("E1", 0, 0),
             make_shared<EnergySensitiveDetectorChannel>("E2", 0, 1),
             make_shared<EnergySensitiveDetectorChannel>("E3", 0, 2),
             make_shared<EnergySensitiveDetectorChannel>("E4", 0, 3),
         }),
     make_shared<EnergySensitiveDetector>(
         "clover_3",
         vector<shared_ptr<Channel>>{
             make_shared<EnergySensitiveDetectorChannel>("E1", 0, 4),
             make_shared<EnergySensitiveDetectorChannel>("E2", 0, 5),
             make_shared<EnergySensitiveDetectorChannel>("E3", 0, 6),
             make_shared<EnergySensitiveDetectorChannel>("E4", 0, 7),
         }),
     make_shared<EnergySensitiveDetector>(
         "clover_5",
         vector<shared_ptr<Channel>>{
             make_shared<EnergySensitiveDetectorChannel>("E1", 0, 8),
             make_shared<EnergySensitiveDetectorChannel>("E2", 0, 9),
             make_shared<EnergySensitiveDetectorChannel>("E3", 0, 10),
             make_shared<EnergySensitiveDetectorChannel>("E4", 0, 11),
         }),
     make_shared<EnergySensitiveDetector>(
         "clover_7",
         vector<shared_ptr<Channel>>{
             make_shared<EnergySensitiveDetectorChannel>("E1", 0, 12),
             make_shared<EnergySensitiveDetectorChannel>("E2", 0, 13),
             make_shared<EnergySensitiveDetectorChannel>("E3", 0, 14),
             make_shared<EnergySensitiveDetectorChannel>("E4", 0, 15),
         }),
     make_shared<EnergySensitiveDetector>(
         "clover_B1",
         vector<shared_ptr<Channel>>{
             make_shared<EnergySensitiveDetectorChannel>("E1", 1, 0),
             make_shared<EnergySensitiveDetectorChannel>("E2", 1, 1),
             make_shared<EnergySensitiveDetectorChannel>("E3", 1, 2),
             make_shared<EnergySensitiveDetectorChannel>("E4", 1, 3),
         }),
     make_shared<EnergySensitiveDetector>(
         "clover_B3",
         vector<shared_ptr<Channel>>{
             make_shared<EnergySensitiveDetectorChannel>("E1", 1, 0),
             make_shared<EnergySensitiveDetectorChannel>("E2", 1, 1),
             make_shared<EnergySensitiveDetectorChannel>("E3", 1, 2),
             make_shared<EnergySensitiveDetectorChannel>("E4", 1, 3),
         }),
     make_shared<EnergySensitiveDetector>(
         "clover_B5",
         vector<shared_ptr<Channel>>{
             make_shared<EnergySensitiveDetectorChannel>("E1", 1, 12),
             make_shared<EnergySensitiveDetectorChannel>("E2", 1, 13),
             make_shared<EnergySensitiveDetectorChannel>("E3", 1, 14),
             make_shared<EnergySensitiveDetectorChannel>("E4", 1, 15),
         }),
     make_shared<EnergySensitiveDetector>(
         "zero_degree",
         vector<shared_ptr<Channel>>{
             make_shared<EnergySensitiveDetectorChannel>("E", 2, 0),
         }),
     make_shared<CounterDetector>(
         "paddle",
         vector<shared_ptr<Channel>>{
             make_shared<CounterDetectorChannel>("mirror", 3, 12),
             make_shared<CounterDetectorChannel>("single", 3, 13),
             make_shared<CounterDetectorChannel>("compton", 3, 14)}),
     make_shared<CounterDetector>(
         "mvlc",
         vector<shared_ptr<Channel>>{
             make_shared<CounterDetectorChannel>("pulser", 3, 15)})},
    {});