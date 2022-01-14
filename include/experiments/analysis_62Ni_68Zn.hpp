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

#include <limits>

using std::numeric_limits;

#include "analysis.hpp"
#include "coincidence_matrix.hpp"
#include "energy_sensitive_detector.hpp"
#include "mdpp16.hpp"

DetectorGroup clover{.name = "clover",
                     .histogram_properties = {65536, -0.125, 16383.875},
                     .raw_histogram_properties = {65536, -0.5, 65535.5},
                     .time_difference_histogram_properties = {
                         8192, -4096. * 0.125, 4096. * 0.125}};
DetectorGroup cebr{.name = "cebr",
                   .histogram_properties = {16384, -0.5, 16383.5},
                   .raw_histogram_properties = {16384, -0.125, 4095.875},
                   .time_difference_histogram_properties = {
                       8192, -4096. * 0.125, 4096. * 0.125}};
DetectorGroup coaxial{.name = "coaxial",
                      .histogram_properties = {65536, -0.125, 16383.875},
                      .raw_histogram_properties = {65536, -0.5, 65535.5},
                      .time_difference_histogram_properties = {
                          8192, -4096. * 0.125, 4096. * 0.125}};
DetectorGroup labr{.name = "labr",
                   .histogram_properties = {16384, -0.5, 16383.5},
                   .raw_histogram_properties = {65536, -0.5, 65535.5},
                   .time_difference_histogram_properties = {
                       8192, -4096. * 0.125, 4096. * 0.125}};
const vector<DetectorGroup> detector_groups = {clover, cebr, labr};

const double tdc_resolution =
    0.098; // in nanoseconds, tdc resolution in nanoseconds per bin

const vector<shared_ptr<DigitizerModule>> modules = {
    shared_ptr<DigitizerModule>(
        new MDPP16("amplitude_clover_90", "time_clover_90",
                   "timestamp_clover_90", tdc_resolution)),
    shared_ptr<DigitizerModule>(
        new MDPP16("amplitude_clover_135", "time_clover_135",
                   "timestamp_clover_135", tdc_resolution)),
    shared_ptr<DigitizerModule>(new MDPP16("integration_long", "channel_time",
                                           "timestamp_cebr", tdc_resolution)),
    shared_ptr<DigitizerModule>(
        new MDPP16("amplitude_beam_monitor", "time_beam_monitor",
                   "timestamp_beam_monitor", tdc_resolution)),
};

vector<EnergySensitiveDetector> detectors{
    {
        "clover_1",
        {
            {"E1", modules[0], 0,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
            {"E2", modules[0], 1,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
            {"E3", modules[0], 2,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
            {"E4", modules[0], 3,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
        },
        clover,
    },
    {
        "clover_3",
        {
            {"E1", modules[0], 4,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
            {"E2", modules[0], 5,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
            {"E3", modules[0], 6,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
            {"E4", modules[0], 7,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
        },
        clover,
    },
    {
        "clover_5",
        {
            {"E1", modules[0], 8,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
            {"E2", modules[0], 9,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
            {"E3", modules[0], 10,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
            {"E4", modules[0], 11,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
        },
        clover,
    },
    {
        "clover_7",
        {
            {"E1", modules[0], 12,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
            {"E2", modules[0], 13,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
            {"E3", modules[0], 14,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
            {"E4", modules[0], 15,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
        },
        clover,
    },
    {
        "clover_B1",
        {
            {"E1", modules[1], 0,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
            {"E2", modules[1], 1,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
            {"E3", modules[1], 2,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
            {"E4", modules[1], 3,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
        },
        clover,
    },
    {
        "clover_B4",
        {
            {"E1", modules[1], 4,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
            {"E2", modules[1], 5,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
            {"E3", modules[1], 6,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
            {"E4", modules[1], 7,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
        },
        clover,
    },
    {
        "clover_B5",
        {
            {"E1", modules[1], 8,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
            {"E2", modules[1], 9,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
            {"E3", modules[1], 10,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
            {"E4", modules[1], 11,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
        },
        clover,
    },
    {
        "clover_B6",
        {
            {"E1", modules[1], 12,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
            {"E2", modules[1], 13,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
            {"E3", modules[1], 14,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
            {"E4", modules[1], 15,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
        },
        clover,
    },
    {
        "cebr_B",
        {
            {"E", modules[2], 0,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
        },
        cebr,
    },
    {
        "cebr_C",
        {
            {"E", modules[2], 1,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
        },
        cebr,
    },
    {
        "cebr_E",
        {
            {"E", modules[2], 2,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
        },
        cebr,
    },
    {
        "cebr_F",
        {
            {"E", modules[2], 3,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
        },
        cebr,
    },
    {
        "cebr_I",
        {
            {"E", modules[2], 4,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
        },
        cebr,
    },
    {
        "cebr_M",
        {
            {"E", modules[2], 5,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
        },
        cebr,
    },
    {
        "cebr_BB",
        {
            {"E", modules[2], 8,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
        },
        cebr,
    },
    {
        "cebr_BC",
        {
            {"E", modules[2], 9,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
        },
        cebr,
    },
    {
        "cebr_BD",
        {
            {"E", modules[2], 10,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
        },
        cebr,
    },
    {
        "cebr_BK",
        {
            {"E", modules[2], 11,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
        },
        cebr,
    },
    {
        "cebr_BL",
        {
            {"E", modules[2], 12,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
        },
        cebr,
    },
    {
        "cebr_BM",
        {
            {"E", modules[2], 13,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
        },
        cebr,
    },
    {
        "zero_degree",
        {
            {"E", modules[3], 0,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
        },
        coaxial,
    },
    {
        "labr_z",
        {
            {"E", modules[3], 8,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
        },
        labr,
    },
};

const vector<CoincidenceMatrix> coincidence_matrices{};

Analysis analysis(modules, detector_groups, detectors, coincidence_matrices);