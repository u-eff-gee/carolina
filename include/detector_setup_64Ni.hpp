#pragma once

#include <limits>

using std::numeric_limits;

#include "coincidence_matrix.hpp"
#include "detector.hpp"
#include "sis3316.hpp"

DetectorGroup hpge{
    .name = "hpge",
    .energy_histogram_properties = {65536, -0.125, 16383.875},
    .energy_raw_histogram_properties = {65536, -0.5, 65535.5},
    .time_difference_histogram_properties = {8192, -4096., 4096.}};
DetectorGroup labr{
    "labr", .energy_histogram_properties = {16384, -0.5, 16383.5},
    .energy_raw_histogram_properties = {16384, -0.03125, 1023.96875},
    .time_difference_histogram_properties = {8192, -4096., 4096.}};
vector<DetectorGroup> groups = {hpge, labr};

vector<SIS3316> modules = {
    {.tdc_resolution = 0.125}, // in nanoseconds, tdc resolution in
                               // nanoseconds per bin
};

vector<Detector> detectors{
    {
        .name = "labr_1",
        {
            {.name = "E",
             .module = modules[0],
             .leaf = 0,
             .energy_calibration_parameters = {{numeric_limits<int>::max(),
                                                {0., 1.}}},
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
    {"labr1_labr2", {0}, {1}, {1024, 0., 16384.}, {1024, 0., 16384.}, true}};