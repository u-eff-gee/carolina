#pragma once

#include <limits>

using std::numeric_limits;

#include "analysis.hpp"
#include "coincidence_matrix.hpp"
#include "detector.hpp"
#include "mdpp16.hpp"

DetectorGroup clover{.name = "clover",
                     .energy_histogram_properties = {65536, -0.125, 16383.875},
                     .energy_raw_histogram_properties = {65536, -0.5, 65535.5},
                     .time_difference_histogram_properties = {
                         8192, -4096. * 0.125, 4096. * 0.125}};
DetectorGroup coaxial{.name = "coaxial",
                      .energy_histogram_properties = {65536, -0.125, 16383.875},
                      .energy_raw_histogram_properties = {65536, -0.5, 65535.5},
                      .time_difference_histogram_properties = {
                          8192, -4096. * 0.125, 4096. * 0.125}};
DetectorGroup nai{
    .name = "nai",
    .energy_histogram_properties = {16384, -0.5, 16383.5},
    .energy_raw_histogram_properties = {16384, -0.03125, 1023.96875},
    .time_difference_histogram_properties = {8192, -4096. * 0.125,
                                             4096. * 0.125}};
DetectorGroup fission_chamber{
    .name = "fission_chamber",
    .energy_histogram_properties = {65536, -0.125, 16383.875},
    .energy_raw_histogram_properties = {65536, -0.5, 65535.5},
    .time_difference_histogram_properties = {8192, -4096. * 0.125,
                                             4096. * 0.125}};
const vector<DetectorGroup> detector_groups = {clover, coaxial, nai,
                                               fission_chamber};

const double tdc_resolution =
    0.024; // in nanoseconds, tdc resolution in nanoseconds per bin

const vector<shared_ptr<Module>> modules = {
    shared_ptr<Module>(new MDPP16("amplitude_cross", "channel_time_cross",
                                  "module_timestamp_cross", tdc_resolution)),
    shared_ptr<Module>(new MDPP16("amplitude_back", "channel_time_back",
                                  "module_timestamp_back", tdc_resolution)),
    shared_ptr<Module>(new MDPP16("amplitude_beam", "channel_time_beam",
                                  "module_timestamp_beam", tdc_resolution)),
    shared_ptr<Module>(new MDPP16("integration_long_qdc", "channel_time_qdc",
                                  "module_timestamp_qdc", tdc_resolution)),
};

vector<Detector> detectors{
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
        "coaxial_B2",
        {
            {"E", modules[1], 4,

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
        "coaxial_B4",
        {
            {"E", modules[1], 8,

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
        "clover_B5",
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
        "fission_chamber_1",
        {
            {"E", modules[2], 12,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
        },
        fission_chamber,
    },
    {
        "fission_chamber_2",
        {
            {"E", modules[2], 13,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
        },
        fission_chamber,
    },
    {
        "zero_degree",
        {
            {"E", modules[2], 15,

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
        "molly",
        {
            {"E", modules[3], 15,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return amplitude;
             },

             []([[maybe_unused]] const double energy) { return 1.; },

             []([[maybe_unused]] const double time_vs_time_RF) { return true; },
             5.},
        },
        nai,
    },
};

const vector<CoincidenceMatrix> coincidence_matrices{};

Analysis analysis(modules, detector_groups, detectors, coincidence_matrices);