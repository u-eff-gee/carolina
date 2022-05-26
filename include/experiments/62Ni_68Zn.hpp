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
        make_shared<MDPP16_SCP>(0x50, "amplitude_clover_90", "time_clover_90",
                                "timestamp_clover_90",
                                "trigger_time_clover_90"),
        make_shared<MDPP16_SCP>(0x70, "amplitude_clover_135", "time_clover_135",
                                "timestamp_clover_135",
                                "trigger_time_clover_135"),
        make_shared<MDPP16_SCP>(0x90, "amplitude_beam_monitor",
                                "time_beam_monitor",
                                "trigger_time_beam_beam_monitor",
                                "timestamp_beam_monitor"),
        make_shared<MDPP16_QDC>(0xd0, "integration_long", "channel_time",
                                "trigger_time", "timestamp_cebr"),
        make_shared<V830>(0x11, 5.),
    },
    {make_shared<EnergySensitiveDetectorGroup>(
         "clover", Histogram{65536, -0.125, 16383.875},
         Histogram{65536, -0.5, 65535.5},
         Histogram{8192, -4096 - 0.5, 4096 - 0.5},
         Histogram{8192, (-4096 - 0.5) * 0.125, (4096 - 0.5) * 0.125}),
     make_shared<EnergySensitiveDetectorGroup>(
         "cebr", Histogram{16384, -0.5, 16383.5},
         Histogram{4096, -0.5, 4096 - 0.5},
         Histogram{8192, -4096 - 0.5, 4096 - 0.5},
         Histogram{8192, (-4096 - 0.5) * 0.125, (4096 - 0.5) * 0.125})},
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
         "clover_B4",
         vector<EnergySensitiveDetectorChannel>{
             {"E1", 1, 4},
             {"E2", 1, 5},
             {"E3", 1, 6},
             {"E4", 1, 7},
         },
         0),
     make_shared<EnergySensitiveDetector>(
         "clover_B5",
         vector<EnergySensitiveDetectorChannel>{
             {"E1", 1, 8},
             {"E2", 1, 9},
             {"E3", 1, 10},
             {"E4", 1, 11},
         },
         0),
     make_shared<EnergySensitiveDetector>(
         "clover_B6",
         vector<EnergySensitiveDetectorChannel>{
             {"E1", 1, 12},
             {"E2", 1, 13},
             {"E3", 1, 14},
             {"E4", 1, 15},
         },
         0)},
    {});