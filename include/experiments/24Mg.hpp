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

/*
    Calibration for clover detectors in the cross using run 005.
    For the horizontal detectors, the background lines at 511 keV (annihilation),
    2615 keV (208Tl decay), and the resonance of 24Mg at 9967 keV were used.
    For the vertical detectors, the 24-Mg line was replaced by the 
    1461 keV (40K decay) background line.
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
EnergySensitiveDetectorGroup cebr{
    "cebr",
    {65536, -0.125, 16383.875},
    {65536, -0.5, 65535.5},
    {8192, -4096 - 0.5, 4096 - 0.5},
    {8192, (-4096 - 0.5) * 0.125, (4096 - 0.5) * 0.125}};

const double tdc_resolution =
    0.024; // in nanoseconds, tdc resolution in nanoseconds per bin

Analysis analysis(
    {
        make_shared<MDPP16>("clover_cross.amplitude",
                            "clover_cross.channel_time",
                            "clover_cross.trigger_time",
                            "clover_cross.module_timestamp", tdc_resolution),
        make_shared<MDPP16>("clover_back.amplitude", "clover_back.channel_time",
                            "clover_back.trigger_time",
                            "clover_back.module_timestamp", tdc_resolution),
        make_shared<MDPP16>("cebr.integration_long", "cebr.channel_time",
                            "cebr.trigger_time", "cebr.module_timestamp",
                            tdc_resolution),
    },
    {
        make_shared<EnergySensitiveDetectorGroup>(clover),
        make_shared<EnergySensitiveDetectorGroup>(clover),
        make_shared<EnergySensitiveDetectorGroup>(clover),
        make_shared<EnergySensitiveDetectorGroup>(clover),
        make_shared<EnergySensitiveDetectorGroup>(clover),
        make_shared<EnergySensitiveDetectorGroup>(clover),
        make_shared<EnergySensitiveDetectorGroup>(clover),
        make_shared<EnergySensitiveDetectorGroup>(clover),
        make_shared<EnergySensitiveDetectorGroup>(cebr),
        make_shared<EnergySensitiveDetectorGroup>(cebr),
        make_shared<EnergySensitiveDetectorGroup>(cebr),
        make_shared<EnergySensitiveDetectorGroup>(cebr),
        make_shared<EnergySensitiveDetectorGroup>(cebr),
        make_shared<EnergySensitiveDetectorGroup>(cebr),
        make_shared<EnergySensitiveDetectorGroup>(cebr),
        make_shared<EnergySensitiveDetectorGroup>(cebr),
        make_shared<EnergySensitiveDetectorGroup>(cebr),
        make_shared<EnergySensitiveDetectorGroup>(cebr),
        make_shared<EnergySensitiveDetectorGroup>(cebr),
        make_shared<EnergySensitiveDetectorGroup>(cebr),
    },
    {
        make_shared<EnergySensitiveDetector>(
            "clover_1",
            vector<shared_ptr<Channel>>{
                make_shared<EnergySensitiveDetectorChannel>("E1", 0, 0, [](const double amplitude, [[maybe_unused]] const long long n_entry){ return -1.357670042896768+0.23254657820908242*amplitude;}),
                make_shared<EnergySensitiveDetectorChannel>("E2", 0, 1, [](const double amplitude, [[maybe_unused]] const long long n_entry){ return -0.43667531961729567+0.2223846473998629*amplitude;}),
                make_shared<EnergySensitiveDetectorChannel>("E3", 0, 2, [](const double amplitude, [[maybe_unused]] const long long n_entry){ return -0.3261173225549259+0.23036986521633754*amplitude;}),
                make_shared<EnergySensitiveDetectorChannel>("E4", 0, 3, [](const double amplitude, [[maybe_unused]] const long long n_entry){ return -1.5543790196819267+0.22603709790950074*amplitude;}),
            }),
        make_shared<EnergySensitiveDetector>(
            "clover_3",
            vector<shared_ptr<Channel>>{
                make_shared<EnergySensitiveDetectorChannel>("E1", 0, 4, [](const double amplitude, [[maybe_unused]] const long long n_entry){ return 1.3588690809220547+0.22100529456619394*amplitude;}),
                make_shared<EnergySensitiveDetectorChannel>("E2", 0, 5, [](const double amplitude, [[maybe_unused]] const long long n_entry){ return -0.5073185078067178+0.2392054019186488*amplitude;}),
                make_shared<EnergySensitiveDetectorChannel>("E3", 0, 6, [](const double amplitude, [[maybe_unused]] const long long n_entry){ return 3.030632530658489+0.24481828172035539*amplitude;}),
                make_shared<EnergySensitiveDetectorChannel>("E4", 0, 7, [](const double amplitude, [[maybe_unused]] const long long n_entry){ return 1.640643585892883+0.2237584703730718*amplitude;}),
            }),
        make_shared<EnergySensitiveDetector>(
            "clover_5",
            vector<shared_ptr<Channel>>{
                make_shared<EnergySensitiveDetectorChannel>("E1", 0, 8, [](const double amplitude, [[maybe_unused]] const long long n_entry){ return -0.6285103194282383+0.22873159386095931*amplitude;}),
                make_shared<EnergySensitiveDetectorChannel>("E2", 0, 9, [](const double amplitude, [[maybe_unused]] const long long n_entry){ return -0.6955677493024829+0.23172591241189425*amplitude;}),
                make_shared<EnergySensitiveDetectorChannel>("E3", 0, 10, [](const double amplitude, [[maybe_unused]] const long long n_entry){ return 1.0884874916810643+0.22413914295029846*amplitude;}),
                make_shared<EnergySensitiveDetectorChannel>("E4", 0, 11, [](const double amplitude, [[maybe_unused]] const long long n_entry){ return -0.44355129313031233+0.2217763320358819*amplitude;}),
            }),
        make_shared<EnergySensitiveDetector>(
            "clover_7",
            vector<shared_ptr<Channel>>{
                make_shared<EnergySensitiveDetectorChannel>("E1", 0, 12, [](const double amplitude, [[maybe_unused]] const long long n_entry){ return 0.9038423359585059+0.22309052137716562*amplitude;}),
                make_shared<EnergySensitiveDetectorChannel>("E2", 0, 13, [](const double amplitude, [[maybe_unused]] const long long n_entry){ return 0.14029832716151142+0.22683776580111584*amplitude;}),
                make_shared<EnergySensitiveDetectorChannel>("E3", 0, 14, [](const double amplitude, [[maybe_unused]] const long long n_entry){ return 1.0097060157284898+0.22573698377598658*amplitude;}),
                make_shared<EnergySensitiveDetectorChannel>("E4", 0, 15, [](const double amplitude, [[maybe_unused]] const long long n_entry){ return 1.0009805079579375+0.23533663500092974*amplitude;}),
            }),
        make_shared<EnergySensitiveDetector>(
            "clover_B1",
            vector<shared_ptr<Channel>>{
                make_shared<EnergySensitiveDetectorChannel>("E1", 1, 0, [](const double amplitude, [[maybe_unused]] const long long n_entry){ return 1.3149105504725251+0.12984302699580796*amplitude;}),
                make_shared<EnergySensitiveDetectorChannel>("E2", 1, 1, [](const double amplitude, [[maybe_unused]] const long long n_entry){ return 1.5419867218116021+0.1336003273298801*amplitude;}),
                make_shared<EnergySensitiveDetectorChannel>("E3", 1, 2, [](const double amplitude, [[maybe_unused]] const long long n_entry){ return -0.1292445615884874+0.1304410531776831*amplitude;}),
                make_shared<EnergySensitiveDetectorChannel>("E4", 1, 3, [](const double amplitude, [[maybe_unused]] const long long n_entry){ return 0.2343212240352991+0.13273398065428804*amplitude;}),
            }),
        make_shared<EnergySensitiveDetector>(
            "clover_B3",
            vector<shared_ptr<Channel>>{
                make_shared<EnergySensitiveDetectorChannel>("E1", 1, 4, [](const double amplitude, [[maybe_unused]] const long long n_entry){ return 2.259872827802891+0.22413363378557488*amplitude;}),
                make_shared<EnergySensitiveDetectorChannel>("E2", 1, 5, [](const double amplitude, [[maybe_unused]] const long long n_entry){ return 1.9742245893570578+0.23200883114940973*amplitude;}),
                make_shared<EnergySensitiveDetectorChannel>("E3", 1, 6, [](const double amplitude, [[maybe_unused]] const long long n_entry){ return -0.23870245946512375+0.22724125914935445*amplitude;}),
                make_shared<EnergySensitiveDetectorChannel>("E4", 1, 7, [](const double amplitude, [[maybe_unused]] const long long n_entry){ return 1.2634286500035723+0.23166263622439273*amplitude;}),
            }),
        make_shared<EnergySensitiveDetector>(
            "clover_B4",
            vector<shared_ptr<Channel>>{
                make_shared<EnergySensitiveDetectorChannel>("E1", 1, 8, [](const double amplitude, [[maybe_unused]] const long long n_entry){ return 1.1254932340824215+0.22017891435311046*amplitude;}),
                make_shared<EnergySensitiveDetectorChannel>("E2", 1, 9, [](const double amplitude, [[maybe_unused]] const long long n_entry){ return 1.3569148961927768+0.2576090645787928*amplitude;}),
                make_shared<EnergySensitiveDetectorChannel>("E3", 1, 10, [](const double amplitude, [[maybe_unused]] const long long n_entry){ return 0.0974816828005082+0.22373500556204043*amplitude;}),
                make_shared<EnergySensitiveDetectorChannel>("E4", 1, 11, [](const double amplitude, [[maybe_unused]] const long long n_entry){ return 0.48639406624533926+0.24027390541159122*amplitude;}),
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
            "cebr_B",
            vector<shared_ptr<Channel>>{
                make_shared<EnergySensitiveDetectorChannel>("E", 2, 0),
            }),
        make_shared<EnergySensitiveDetector>(
            "cebr_C",
            vector<shared_ptr<Channel>>{
                make_shared<EnergySensitiveDetectorChannel>("E", 2, 1),
            }),
        make_shared<EnergySensitiveDetector>(
            "cebr_D",
            vector<shared_ptr<Channel>>{
                make_shared<EnergySensitiveDetectorChannel>("E", 2, 2),
            }),
        make_shared<EnergySensitiveDetector>(
            "cebr_F",
            vector<shared_ptr<Channel>>{
                make_shared<EnergySensitiveDetectorChannel>("E", 2, 3),
            }),
        make_shared<EnergySensitiveDetector>(
            "cebr_G",
            vector<shared_ptr<Channel>>{
                make_shared<EnergySensitiveDetectorChannel>("E", 2, 4),
            }),
        make_shared<EnergySensitiveDetector>(
            "cebr_H",
            vector<shared_ptr<Channel>>{
                make_shared<EnergySensitiveDetectorChannel>("E", 2, 5),
            }),
        make_shared<EnergySensitiveDetector>(
            "cebr_K",
            vector<shared_ptr<Channel>>{
                make_shared<EnergySensitiveDetectorChannel>("E", 2, 6),
            }),
        make_shared<EnergySensitiveDetector>(
            "cebr_O",
            vector<shared_ptr<Channel>>{
                make_shared<EnergySensitiveDetectorChannel>("E", 2, 7),
            }),
        make_shared<EnergySensitiveDetector>(
            "cebr_BB",
            vector<shared_ptr<Channel>>{
                make_shared<EnergySensitiveDetectorChannel>("E", 2, 8),
            }),
        make_shared<EnergySensitiveDetector>(
            "cebr_BI",
            vector<shared_ptr<Channel>>{
                make_shared<EnergySensitiveDetectorChannel>("E", 2, 9),
            }),
        make_shared<EnergySensitiveDetector>(
            "cebr_BK",
            vector<shared_ptr<Channel>>{
                make_shared<EnergySensitiveDetectorChannel>("E", 2, 10),
            }),
        make_shared<EnergySensitiveDetector>(
            "cebr_BM",
            vector<shared_ptr<Channel>>{
                make_shared<EnergySensitiveDetectorChannel>("E", 2, 11),
            }),
    },
    {});