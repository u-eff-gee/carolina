#pragma once

#include <limits>

using std::numeric_limits;

#include <memory>

using std::shared_ptr;

#include "analysis.hpp"
#include "coincidence_matrix.hpp"
#include "detector.hpp"
#include "sis3316.hpp"

DetectorGroup hpge{.name = "hpge",
                   .energy_histogram_properties = {65536, -0.125, 16383.875},
                   .energy_raw_histogram_properties = {65536, -0.5, 65535.5},
                   .time_difference_histogram_properties = {
                       8192, -4096. * 0.125, 4096. * 0.125}};
DetectorGroup labr{
    .name = "labr",
    .energy_histogram_properties = {16384, -0.5, 16383.5},
    .energy_raw_histogram_properties = {16384, -0.03125, 1023.96875},
    .time_difference_histogram_properties = {8192, -4096. * 0.125,
                                             4096. * 0.125}};
const vector<DetectorGroup> detector_groups = {hpge, labr};

const vector<shared_ptr<DigitizerModule>> modules = {
    shared_ptr<DigitizerModule>(
        new SIS3316(0.125)), // nanoseconds, tdc resolution in
                             // nanoseconds per bin
};

vector<Detector> detectors{
    {
        "labr_1",
        {
            {"E", modules[0], 0,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return 2.685975e+02 + 1.644962e+00 * 16 * amplitude +
                        2.248462e-04 * 16 * 16 * amplitude * amplitude;
             },
             // Run 528
             [](const double energy) {
                 if (energy < 800. || energy > 1400.) {
                     return 1.;
                 } else {
                     return 1. / (1.0 - 3.54978575e-01 *
                                            exp(-7.30421449e-03 *
                                                (energy - 5.96228695e+02)));
                 }
             },

             [](const double time_vs_time_RF) {
                 if (abs(time_vs_time_RF - 180.) < 20.) {
                     return true;
                 }
                 return false;
             },
             5.},
        },
        labr,
    },
    {
        "labr_2",
        {
            {"E", modules[0], 1,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return 2.018431e+02 + 1.140523e+00 * 16 * amplitude +
                        3.438323e-04 * 16 * 16 * amplitude * amplitude;
             },
             // Run 528
             [](const double energy) {
                 if (energy < 800. || energy > 1400.) {
                     return 1.;
                 } else {
                     return 1. / (1.0 - 2.00916232e-04 *
                                            exp(-5.01816114e-03 *
                                                (energy - 1.95964658e+03)));
                 }
             },

             [](const double time_vs_time_RF) {
                 if (abs(time_vs_time_RF - 180.) < 20.) {
                     return true;
                 }
                 return false;
             },
             5.},
        },
        labr,
    },
    {
        "labr_3",
        {
            {"E", modules[0], 2,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return 2.137622e+02 + 2.114113e+00 * 16 * amplitude +
                        5.824968e-05 * 16 * 16 * amplitude * amplitude;
             },
             // Run 528
             [](const double energy) {
                 if (energy < 800. || energy > 1500.) {
                     return 1.;
                 } else {
                     return 1. / (1.0 - 6.30618678e-04 *
                                            exp(-3.96193663e-03 *
                                                (energy - 2.02533142e+03)));
                 }
             },

             [](const double time_vs_time_RF) {
                 if (abs(time_vs_time_RF - 180.) < 20.) {
                     return true;
                 }
                 return false;
             },
             5.},
        },
        labr,
    },
    {
        "labr_4",
        {
            {"E", modules[0], 3,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return 1.765400e+02 + 1.618102e+00 * 16 * amplitude +
                        4.511530e-04 * 16 * 16 * amplitude * amplitude;
             },
             // Run 528
             [](const double energy) {
                 if (energy < 800. || energy > 1600.) {
                     return 1.;
                 } else {
                     return 1. / (1.0 - 9.79036424e-04 *
                                            exp(-3.22123603e-03 *
                                                (energy - 2.12618155e+03)));
                 }
             },

             [](const double time_vs_time_RF) {
                 if (abs(time_vs_time_RF - 180.) < 20.) {
                     return true;
                 }
                 return false;
             },
             5.},
        },
        labr,
    },
    {
        "hpge_1",
        {
            {"E", modules[0], 4,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return 5.570186e+00 + 6.799282e-01 * amplitude +
                        3.132755e-07 * amplitude * amplitude;
             },
             // Run 528
             []([[maybe_unused]] const double energy) { return 1.; },

             [](const double time_vs_time_RF) {
                 if (abs(time_vs_time_RF - 180.) < 150.) {
                     return true;
                 }
                 return false;
             },
             20.},
        },
        hpge,
    },
    {
        "hpge_2",
        {
            {"E", modules[0], 5,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return -1.084339e+00 + 6.977068e-01 * amplitude +
                        -1.894253e-07 * amplitude * amplitude;
             },
             // Run 528
             []([[maybe_unused]] const double energy) { return 1.; },

             [](const double time_vs_time_RF) {
                 if (abs(time_vs_time_RF - 180.) < 150.) {
                     return true;
                 }
                 return false;
             },
             20.},
        },
        hpge,
    },
    {
        "hpge_3",
        {
            {"E", modules[0], 6,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return 2.161040e+01 + 7.134485e-01 * amplitude +
                        2.873566e-06 * amplitude * amplitude;
             },
             // Run 528
             []([[maybe_unused]] const double energy) { return 1.; },

             [](const double time_vs_time_RF) {
                 if (abs(time_vs_time_RF - 180.) < 150.) {
                     return true;
                 }
                 return false;
             },
             20.},
        },
        hpge,
    },
    {
        "hpge_4",
        {
            {"E", modules[0], 7,

             []([[maybe_unused]] const int n_entry, const double amplitude) {
                 return 8.355447e+00 + 7.510629e-01 * amplitude +
                        1.469643e-06 * amplitude * amplitude;
             },
             // Run 528
             []([[maybe_unused]] const double energy) { return 1.; },

             [](const double time_vs_time_RF) {
                 if (abs(time_vs_time_RF - 180.) < 150.) {
                     return true;
                 }
                 return false;
             },
             20.},
        },
        hpge,
    },
};

const vector<CoincidenceMatrix> coincidence_matrices{
    {"labr_labr", {0, 1, 2, 3}, {}, {1024, -8., 16376.}, {1024, -8., 16376.}},
    {"hpge_hpge", {4, 5, 6, 7}, {}, {1024, -8., 16376.}, {1024, -8., 16376.}},
    {"labr_hpge",
     {4, 5, 6, 7},
     {0, 1, 2, 3},
     {1024, -8., 16376.},
     {1024, -8., 16376.}},
};

Analysis analysis(modules, detector_groups, detectors, coincidence_matrices);