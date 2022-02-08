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
                make_shared<EnergySensitiveDetectorChannel>("E1", 1, 4),
                make_shared<EnergySensitiveDetectorChannel>("E2", 1, 5),
                make_shared<EnergySensitiveDetectorChannel>("E3", 1, 6),
                make_shared<EnergySensitiveDetectorChannel>("E4", 1, 7),
            }),
        make_shared<EnergySensitiveDetector>(
            "clover_B4",
            vector<shared_ptr<Channel>>{
                make_shared<EnergySensitiveDetectorChannel>("E1", 1, 8),
                make_shared<EnergySensitiveDetectorChannel>("E2", 1, 9),
                make_shared<EnergySensitiveDetectorChannel>("E3", 1, 10),
                make_shared<EnergySensitiveDetectorChannel>("E4", 1, 11),
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