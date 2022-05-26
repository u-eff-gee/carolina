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

auto cebr = make_shared<EnergySensitiveDetectorGroup>(
    "cebr", Histogram{65536, -0.125, 16383.875},
    Histogram{65536, -0.5, 65535.5}, Histogram{8192, -4096 - 0.5, 4096 - 0.5},
    Histogram{8192, (-4096 - 0.5) * 0.125, (4096 - 0.5) * 0.125});
auto clover = make_shared<EnergySensitiveDetectorGroup>(
    "clover", Histogram{65536, -0.125, 16384. - 0.125},
    Histogram{65536, -0.5, 65536. - 0.5},
    Histogram{2000, -1000. - 0.5, 1000. - 0.5},
    Histogram{2000, -1000. - 0.5, 1000. - 0.5});

Analysis analysis(
    {make_shared<MDPP16_SCP>(0x30, "clover_cross.amplitude",
                             "clover_cross.channel_time",
                             "clover_cross.trigger_time",
                             "clover_cross.timestamp"),
     make_shared<MDPP16_SCP>(0x50, "clover_back.amplitude",
                             "clover_back.channel_time",
                             "clover_back.trigger_time",
                             "clover_back.timestamp"),
     make_shared<MDPP16_QDC>(0x90, "cebr.integration_long", "cebr.channel_time",
                             "cebr.trigger_time", "cebr.module_timestamp")},
    {clover, clover, clover, clover, clover, clover, clover,
     clover, cebr,   cebr,   cebr,   cebr,   cebr,   cebr,
     cebr,   cebr,   cebr,   cebr,   cebr,   cebr},
    {
        make_shared<EnergySensitiveDetector>(
            "clover_1",
            vector<EnergySensitiveDetectorChannel>{
                {"E1", 0, 0},
                {"E2", 0, 1},
                {"E3", 0, 2},
                {"E4", 0, 3},
            },
            clover),
        make_shared<EnergySensitiveDetector>(
            "clover_3",
            vector<EnergySensitiveDetectorChannel>{
                {"E1", 0, 4},
                {"E2", 0, 5},
                {"E3", 0, 6},
                {"E4", 0, 7},
            },
            clover),
        make_shared<EnergySensitiveDetector>(
            "clover_5",
            vector<EnergySensitiveDetectorChannel>{
                {"E1", 0, 8},
                {"E2", 0, 9},
                {"E3", 0, 10},
                {"E4", 0, 11},
            },
            clover),
        make_shared<EnergySensitiveDetector>(
            "clover_7",
            vector<EnergySensitiveDetectorChannel>{
                {"E1", 0, 12},
                {"E2", 0, 13},
                {"E3", 0, 14},
                {"E4", 0, 15},
            },
            clover),
        make_shared<EnergySensitiveDetector>(
            "clover_B1",
            vector<EnergySensitiveDetectorChannel>{
                {"E1", 1, 0},
                {"E2", 1, 1},
                {"E3", 1, 2},
                {"E4", 1, 3},
            },
            clover),
        make_shared<EnergySensitiveDetector>(
            "clover_B3",
            vector<EnergySensitiveDetectorChannel>{
                {"E1", 1, 4},
                {"E2", 1, 5},
                {"E3", 1, 6},
                {"E4", 1, 7},
            },
            clover),
        make_shared<EnergySensitiveDetector>(
            "clover_B4",
            vector<EnergySensitiveDetectorChannel>{
                {"E1", 1, 8},
                {"E2", 1, 9},
                {"E3", 1, 10},
                {"E4", 1, 11},
            },
            clover),
        make_shared<EnergySensitiveDetector>(
            "clover_B5",
            vector<EnergySensitiveDetectorChannel>{
                {"E1", 1, 12},
                {"E2", 1, 13},
                {"E3", 1, 14},
                {"E4", 1, 15},
            },
            clover),
        make_shared<EnergySensitiveDetector>(
            "cebr_B",
            vector<EnergySensitiveDetectorChannel>{
                {"E", 2, 0},
            },
            cebr),
        make_shared<EnergySensitiveDetector>(
            "cebr_C",
            vector<EnergySensitiveDetectorChannel>{
                {"E", 2, 1},
            },
            cebr),
        make_shared<EnergySensitiveDetector>(
            "cebr_D",
            vector<EnergySensitiveDetectorChannel>{
                {"E", 2, 2},
            },
            cebr),
        make_shared<EnergySensitiveDetector>(
            "cebr_F",
            vector<EnergySensitiveDetectorChannel>{
                {"E", 2, 3},
            },
            cebr),
        make_shared<EnergySensitiveDetector>(
            "cebr_G",
            vector<EnergySensitiveDetectorChannel>{
                {"E", 2, 4},
            },
            cebr),
        make_shared<EnergySensitiveDetector>(
            "cebr_H",
            vector<EnergySensitiveDetectorChannel>{
                {"E", 2, 5},
            },
            cebr),
        make_shared<EnergySensitiveDetector>(
            "cebr_K",
            vector<EnergySensitiveDetectorChannel>{
                {"E", 2, 6},
            },
            cebr),
        make_shared<EnergySensitiveDetector>(
            "cebr_O",
            vector<EnergySensitiveDetectorChannel>{
                {"E", 2, 7},
            },
            cebr),
        make_shared<EnergySensitiveDetector>(
            "cebr_BI",
            vector<EnergySensitiveDetectorChannel>{
                {"E", 2, 9},
            },
            cebr),
        make_shared<EnergySensitiveDetector>(
            "cebr_BK",
            vector<EnergySensitiveDetectorChannel>{
                {"E", 2, 10},
            },
            cebr),
        make_shared<EnergySensitiveDetector>(
            "cebr_BM",
            vector<EnergySensitiveDetectorChannel>{
                {"E", 2, 11},
            },
            cebr),
    },
    {});