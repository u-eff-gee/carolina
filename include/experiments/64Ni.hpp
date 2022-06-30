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
    {make_shared<SIS3316>(0x0)},
    {
        make_shared<EnergySensitiveDetectorGroup>(
            "hpge", Histogram{65536, -0.125, 16383.875},
            Histogram{65536, -0.5, 65535.5},
            Histogram{8192, -4096 - 0.5, 4096 - 0.5},
            Histogram{8192, (-4096 - 0.5) * 0.125, (4096 - 0.5) * 0.125}),
        make_shared<EnergySensitiveDetectorGroup>(
            "labr", Histogram{16384, -0.5, 16383.5},
            Histogram{4096, -0.5, 4096 - 0.5},
            Histogram{8192, -4096 - 0.5, 4096 - 0.5},
            Histogram{8192, (-4096 - 0.5) * 0.125, (4096 - 0.5) * 0.125}),
    },
    {
        make_shared<EnergySensitiveDetector>(
            "labr_1", vector<EnergySensitiveDetectorChannel>{{"E", 0, 0}}, 1),
        make_shared<EnergySensitiveDetector>(
            "labr_2", vector<EnergySensitiveDetectorChannel>{{"E", 0, 1}}, 1),
        make_shared<EnergySensitiveDetector>(
            "labr_3", vector<EnergySensitiveDetectorChannel>{{"E", 0, 2}}, 1),
        make_shared<EnergySensitiveDetector>(
            "labr_4", vector<EnergySensitiveDetectorChannel>{{"E", 0, 3}}, 1),
        make_shared<EnergySensitiveDetector>(
            "hpge_1", vector<EnergySensitiveDetectorChannel>{{"E", 0, 4}}, 0),
        make_shared<EnergySensitiveDetector>(
            "hpge_2", vector<EnergySensitiveDetectorChannel>{{"E", 0, 5}}, 0),
        make_shared<EnergySensitiveDetector>(
            "hpge_3", vector<EnergySensitiveDetectorChannel>{{"E", 0, 6}}, 0),
        make_shared<EnergySensitiveDetector>(
            "hpge_4", vector<EnergySensitiveDetectorChannel>{{"E", 0, 7}}, 0),
    },
    {{"labr_1_vs_labr_2",
      {0},
      {1},
      Histogram{4096, -0.5, 4096 - 0.5},
      Histogram{4096, -0.5, 4096 - 0.5}}});