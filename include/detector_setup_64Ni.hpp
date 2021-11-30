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
                     {2406208, {0.000000, 1.000000}},
                     {2416928, {-3.455282, 1.000362}},
                     {54652960, {-2.826526, 1.004762}},
                     {60058656, {-5.119628, 1.004899}},
                     {61472160, {-4.489615, 1.003895}},
                     {146132896, {-8.011980, 1.003089}},
                     {224601824, {-12.359262, 1.003119}},
                     {303285952, {-0.511097, 0.994950}},
                     {342088768, {-7.179128, 0.990396}},
                     {423058528, {-8.752953, 0.992509}},
                     {501463840, {73.868960, 0.992820}},
                     {580736800, {40.202088, 0.993830}},
                     {658717408, {-10.278469, 0.995691}},
                     {734875840, {-11.742271, 0.998623}},
                     {795080704, {-9.635501, 1.002810}},
                     {871852256, {-10.435182, 0.997006}},
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
             .energy_calibration_parameters = {{numeric_limits<int>::max(),
                                                {0., 1.}}},
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
             .energy_calibration_parameters = {{numeric_limits<int>::max(),
                                                {0., 1.}}},
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
             .energy_calibration_parameters = {{numeric_limits<int>::max(),
                                                {0., 1.}}},
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
             .energy_calibration_parameters = {{numeric_limits<int>::max(),
                                                {0., 1.}}},
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
             .energy_calibration_parameters = {{numeric_limits<int>::max(),
                                                {0., 1.}}},
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
             .energy_calibration_parameters = {{numeric_limits<int>::max(),
                                                {0., 1.}}},
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
             .energy_calibration_parameters = {{numeric_limits<int>::max(),
                                                {0., 1.}}},
             .amplitude_threshold = 20.},
        },
        hpge,
    },
};

const vector<CoincidenceMatrix> coincidence_matrices{
    // {"labr1_labr2", {0}, {1}, {1024, 0., 16384.}, {1024, 0., 16384.}, true},
    {"labr_labr",
     {0, 1, 2, 3},
     {},
     {1024, 0., 16384.},
     {1024, 0., 16384.},
     true}};

DetectorSetup detector_setup(modules, detector_groups, detectors);