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

Analysis analysis(
    {
        make_shared<MDPP16_SCP>(0x10, "amplitude_cross", "channel_time_cross",
                                "trigger_time_cross", "module_timestamp_cross"),
        make_shared<MDPP16_SCP>(0x30, "amplitude_back", "channel_time_back",
                                "trigger_time_back", "module_timestamp_back"),
        make_shared<MDPP16_SCP>(0x70, "amplitude_beam", "channel_time_beam",
                                "trigger_time_beam", "module_timestamp_beam"),
        make_shared<MDPP16_QDC>(0xb0, "integration_long_qdc",
                                "channel_time_qdc", "trigger_time_qdc",
                                "module_timestamp_qdc"),
        make_shared<V830>(0x00, 5.),
    },
    {
        make_shared<EnergySensitiveDetectorGroup>(
            "clover", Histogram{65536, -0.125, 16383.875},
            Histogram{65536, -0.5, 65535.5},
            Histogram{8192, -4096 - 0.5, 4096 - 0.5},
            Histogram{8192, (-4096 - 0.5) * 0.125, (4096 - 0.5) * 0.125}),
        make_shared<EnergySensitiveDetectorGroup>(
            "coaxial", Histogram{65536, -0.125, 16383.875},
            Histogram{65536, -0.5, 65535.5},
            Histogram{8192, -4096 - 0.5, 4096 - 0.5},
            Histogram{8192, (-4096 - 0.5) * 0.125, (4096 - 0.5) * 0.125}),
        make_shared<EnergySensitiveDetectorGroup>(
            "nai", Histogram{16384, -0.5, 16383.5},
            Histogram{4096, -0.5, 4096 - 0.5},
            Histogram{8192, -4096 - 0.5, 4096 - 0.5},
            Histogram{8192, (-4096 - 0.5) * 0.125, (4096 - 0.5) * 0.125}),
        make_shared<EnergySensitiveDetectorGroup>(
            "fission_chamber", Histogram{65536, -0.125, 16383.875},
            Histogram{65536, -0.5, 65535.5},
            Histogram{8192, -4096 - 0.5, 4096 - 0.5},
            Histogram{8192, (-4096 - 0.5) * 0.125, (4096 - 0.5) * 0.125}),
        make_shared<CounterDetectorGroup>(
            "paddle", Histogram{100000, -5., 1e6 - 5.},
            Histogram{65536, 0, numeric_limits<int>::max()}),
        make_shared<CounterDetectorGroup>(
            "pulser", Histogram{100000, -5., 1e6 - 5.},
            Histogram{65536, 0, numeric_limits<int>::max()}),
    },
    {make_shared<EnergySensitiveDetector>(
         "clover_1",
         vector<EnergySensitiveDetectorChannel>{
             {"E1", 0, 0},
             {"E2", 0, 1},
             {"E3", 0, 2},
             {"E4", 0, 3},
         },
         0),
     make_shared<EnergySensitiveDetector>(
         "clover_3",
         vector<EnergySensitiveDetectorChannel>{
             {"E1", 0, 4},
             {"E2", 0, 5},
             {"E3", 0, 6},
             {"E4", 0, 7},
         },
         0),
     make_shared<EnergySensitiveDetector>(
         "clover_5",
         vector<EnergySensitiveDetectorChannel>{
             {"E1", 0, 8},
             {"E2", 0, 9},
             {"E3", 0, 10},
             {"E4", 0, 11},
         },
         0),
     make_shared<EnergySensitiveDetector>(
         "clover_7",
         vector<EnergySensitiveDetectorChannel>{
             {"E1", 0, 12},
             {"E2", 0, 13},
             {"E3", 0, 14},
             {"E4", 0, 15},
         },
         0),
     make_shared<EnergySensitiveDetector>(
         "clover_B1",
         vector<EnergySensitiveDetectorChannel>{
             {"E1", 1, 0},
             {"E2", 1, 1},
             {"E3", 1, 2},
             {"E4", 1, 3},
         },
         0),
     make_shared<EnergySensitiveDetector>(
         "coaxial_B2",
         vector<EnergySensitiveDetectorChannel>{
             {"E1", 1, 4},
         },
         1),
     make_shared<EnergySensitiveDetector>(
         "coaxial_B4",
         vector<EnergySensitiveDetectorChannel>{
             {"E1", 1, 8},
         },
         1),
     make_shared<EnergySensitiveDetector>(
         "clover_B5",
         vector<EnergySensitiveDetectorChannel>{
             {"E1", 1, 12},
             {"E2", 1, 13},
             {"E3", 1, 14},
             {"E4", 1, 15},
         },
         0),
     make_shared<EnergySensitiveDetector>(
         "fission_chamber",
         vector<EnergySensitiveDetectorChannel>{
             {"E1", 2, 12},
             {"E2", 2, 13},
         },
         3),
     make_shared<EnergySensitiveDetector>(
         "zero_degree",
         vector<EnergySensitiveDetectorChannel>{
             {"E", 2, 15},
         },
         1),
     make_shared<EnergySensitiveDetector>(
         "molly",
         vector<EnergySensitiveDetectorChannel>{
             {"E", 3, 15},
         },
         2),
     make_shared<CounterDetector>(
         "paddle",
         vector<CounterDetectorChannel>{
             {"mirror", 4, 12}, {"single", 4, 13}, {"compton", 4, 14}},
         4),
     make_shared<CounterDetector>(
         "mvlc", vector<CounterDetectorChannel>{{"pulser", 4, 15}}, 5)},
    {{"clover_1_vs_clover_3",
      {0},
      {1},
      {2048, -2., 16382.},
      {2048, -2., 16382.}}});