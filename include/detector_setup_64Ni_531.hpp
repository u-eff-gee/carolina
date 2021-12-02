#pragma once

#include <limits>

using std::numeric_limits;

#include <memory>

using std::shared_ptr;

#include "coincidence_matrix.hpp"
#include "detector.hpp"
#include "detector_setup.hpp"
#include "sis3316.hpp"

DetectorGroup hpge{.name = "hpge",
                   .energy_histogram_properties = {65536, -0.125, 16383.875},
                   .energy_raw_histogram_properties = {65536, -0.5, 65535.5},
                   .time_difference_histogram_properties = {
                       8192, -4096. * 0.125, 4096. * 0.125}};
DetectorGroup labr{
    "labr", .energy_histogram_properties = {16384, -0.5, 16383.5},
    .energy_raw_histogram_properties = {16384, -0.03125, 1023.96875},
    .time_difference_histogram_properties = {8192, -4096. * 0.125,
                                             4096. * 0.125}};
const vector<DetectorGroup> detector_groups = {hpge, labr};

const vector<shared_ptr<Module>> modules = {
    shared_ptr<Module>(new SIS3316(0.125)), // nanoseconds, tdc resolution in
                                            // nanoseconds per bin
};

vector<Detector> detectors{
    {
        .name = "labr_1",
        {
            {.name = "E",
             .module = modules[0],
             .leaf = 0,
             .energy_calibration_parameters =
                 {
                     {numeric_limits<int>::max(),
                      {2.685975e+02, 1.644962e+00 * 16,
                       2.248462e-04 * 16 * 16}}, // Run 531
                 },
             .time_calibration = // Run 528
             [](const double energy) {
                 if (energy < 800. || energy > 1400.) {
                     return 1.;
                 } else {
                     return 1. / (1.0 - 3.54978575e-01 *
                                            exp(-7.30421449e-03 *
                                                (energy - 5.96228695e+02)));
                 }
             },
             .amplitude_threshold = 5.},
        },
        labr,
    },
    {
        .name = "labr_2",
        {
            {.name = "E",
             .module = modules[0],
             .leaf = 1,
             .energy_calibration_parameters =
                 {
                     {numeric_limits<int>::max(),
                      {2.018431e+02, 1.140523e+00 * 16,
                       3.438323e-04 * 16 * 16}}, // Run 531
                 },
             .time_calibration = // Run 528
             [](const double energy) {
                 if (energy < 800. || energy > 1400.) {
                     return 1.;
                 } else {
                     return 1. / (1.0 - 2.00916232e-04 *
                                            exp(-5.01816114e-03 *
                                                (energy - 1.95964658e+03)));
                 }
             },
             .amplitude_threshold = 5.},
        },
        labr,
    },
    {
        .name = "labr_3",
        {
            {.name = "E",
             .module = modules[0],
             .leaf = 2,
             .energy_calibration_parameters =
                 {
                     {numeric_limits<int>::max(),
                      {2.137622e+02, 2.114113e+00 * 16,
                       5.824968e-05 * 16 * 16}}, // Run 531
                 },
             .time_calibration = // Run 528
             [](const double energy) {
                 if (energy < 800. || energy > 1500.) {
                     return 1.;
                 } else {
                     return 1. / (1.0 - 6.30618678e-04 *
                                            exp(-3.96193663e-03 *
                                                (energy - 2.02533142e+03)));
                 }
             },
             .amplitude_threshold = 5.},
        },
        labr,
    },
    {
        .name = "labr_4",
        {
            {.name = "E",
             .module = modules[0],
             .leaf = 3,
             .energy_calibration_parameters =
                 {
                     {numeric_limits<int>::max(),
                      {1.765400e+02, 1.618102e+00 * 16,
                       4.511530e-04 * 16 * 16}}, // Run 531
                 },
             .time_calibration = // Run 528
             [](const double energy) {
                 if (energy < 800. || energy > 1600.) {
                     return 1.;
                 } else {
                     return 1. / (1.0 - 9.79036424e-04 *
                                            exp(-3.22123603e-03 *
                                                (energy - 2.12618155e+03)));
                 }
             },
             .amplitude_threshold = 5.},
        },
        labr,
    },
    {
        .name = "hpge_1",
        {
            {.name = "E",
             .module = modules[0],
             .leaf = 4,
             .energy_calibration_parameters =
                 {
                     {numeric_limits<int>::max(),
                      {5.570186e+00, 6.799282e-01, 3.132755e-07}}, // Run 531
                 },
             .time_calibration = // Run 528
             []([[maybe_unused]] const double energy) { return 1.; },
             .amplitude_threshold = 20.},
        },
        hpge,
    },
    {
        .name = "hpge_2",
        {
            {.name = "E",
             .module = modules[0],
             .leaf = 5,
             .energy_calibration_parameters =
                 {
                     {numeric_limits<int>::max(),
                      {-1.084339e+00, 6.977068e-01, -1.894253e-07}}, // Run 531
                 },
             .time_calibration = // Run 528
             []([[maybe_unused]] const double energy) { return 1.; },
             .amplitude_threshold = 20.},
        },
        hpge,
    },
    {
        .name = "hpge_3",
        {
            {.name = "E",
             .module = modules[0],
             .leaf = 6,
             .energy_calibration_parameters =
                 {
                     {numeric_limits<int>::max(),
                      {2.161040e+01, 7.134485e-01, 2.873566e-06}}, // Run 531
                 },
             .time_calibration = // Run 528
             []([[maybe_unused]] const double energy) { return 1.; },
             .amplitude_threshold = 20.},
        },
        hpge,
    },
    {
        .name = "hpge_4",
        {
            {.name = "E",
             .module = modules[0],
             .leaf = 7,
             .energy_calibration_parameters =
                 {
                     {numeric_limits<int>::max(),
                      {8.355447e+00, 7.510629e-01, 1.469643e-06}}, // Run 531
                 },
             .time_calibration = // Run 528
             []([[maybe_unused]] const double energy) { return 1.; },
             .amplitude_threshold = 20.},
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

DetectorSetup detector_setup(modules, detector_groups, detectors);