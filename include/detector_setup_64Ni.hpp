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
                     {2406208,
                      {45.845185751404024, 2.114188617352532 * 16}}, // Run 495
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
                     {2406208,
                      {-10.124324221548868, 1.677338897840358 * 16}}, // Run 495
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
                     {2406208,
                      {37.24986202252936, 2.4409531823983714 * 16}}, // Run 495
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
                     {2406208,
                      {-7.966427805396491, 2.2238549383688917 * 16}}, // Run 495
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
                     {2406208,
                      {2.224801749620616, 0.6821961140000355}}, // Run 495
                 },
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
                     {2406208,
                      {-3.307975494417557, 0.6962769336752404}}, // Run 495
                 },
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
                     {2406208,
                      {1.875662214048816, 0.7308577379533665}}, // Run 495
                 },
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
                     {2406208,
                      {-0.47612931936339586, 0.7582054746223055}}, // Run 495
                 },
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