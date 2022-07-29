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
            "labr", Histogram{4096, -2, 16382},
            Histogram{16384, -0.125, 4096 - 0.125},
            Histogram{8192, -4096 - 0.5, 4096 - 0.5},
            Histogram{8192, (-4096 - 0.5) * 0.125, (4096 - 0.5) * 0.125}),
    },
    
    {
        make_shared<EnergySensitiveDetector>(
            "labr_1",vector<EnergySensitiveDetectorChannel>{ {"E", 0, 0,[](const double channel, const long long) {return (17.601223374686242 +9.044300913068591 * channel * 4. +-0.0030645588610997794 * channel * channel * 16. +2.378951795388353e-06 * channel * channel *channel * 64.);}}}, 1),
        make_shared<EnergySensitiveDetector>(
            "labr_2",vector<EnergySensitiveDetectorChannel>{{"E", 0, 1,[](const double channel, const long long) {return (3.30011886270799 +6.5018748622678295 * channel * 4 +0.0008258622567823124 * channel * channel * 16. +2.9562841744863787e-07 * channel * channel *channel * 64.);}}},1),
        make_shared<EnergySensitiveDetector>(
            "labr_3",vector<EnergySensitiveDetectorChannel>{{"E", 0, 2,[](const double channel, const long long) {return (-4.334228864277975 +10.847058837462665 * channel * 4. +-0.00633271118898465 * channel * channel * 16. + 5.240694745133814e-06 * channel * channel * channel * 64.); }}}, 1),
        make_shared<EnergySensitiveDetector>(
            "labr_4",vector<EnergySensitiveDetectorChannel>{{"E", 0, 3,[](const double channel, const long long) {return (3.1909193216067653 +8.571459640672055 * channel * 4. +0.0008493099811167642 * channel * channel * 16. +6.174181102734334e-09 * channel * channel *channel * 64.); }}}, 1),
            make_shared<EnergySensitiveDetector>(
             "hpge_1", vector<EnergySensitiveDetectorChannel>{{"E", 0, 4, [](const double channel, const long long){ return (1.57661973524373+0.6817545334755168*channel+1.3873238594790636e-07*channel*channel);}}}, 0),
        make_shared<EnergySensitiveDetector>(
            "hpge_2", vector<EnergySensitiveDetectorChannel>{{"E", 0, 5, [](const double channel, const long long){ return (-0.12920658259438178+0.6949954832528151*channel+ -3.8910539767706286e-08*channel*channel);}}}, 0),
        make_shared<EnergySensitiveDetector>(
            "hpge_3", vector<EnergySensitiveDetectorChannel>{{"E", 0, 6, [](const double channel, const long long){ return (2.3379527308416117+0.728372161229253*channel+1.6704897670007945e-07*channel*channel);}}}, 0),
        make_shared<EnergySensitiveDetector>(
            "hpge_4", vector<EnergySensitiveDetectorChannel>{{"E", 0, 7, [](const double channel, const long long){ return (-0.3672812348956054+0.7588636040581321*channel+-1.2367294537567397e-07*channel*channel);}}}, 0),
    },
    {{"labr_labr",
      {0, 1, 2, 3}, {},
      Histogram{4096, -2, 16384 - 2},
      Histogram{4096, -2, 16384 - 2}},
      {"labr_hpge",
      {0, 1, 2, 3}, {4, 5, 6, 7},
      Histogram{4096, -2, 16384 - 2},
      Histogram{16384, -0.5, 16384 - 0.5}},
      });
