#pragma once

#include "sis3316.hpp"
#include "detector.hpp"

const double coincidence_window_half_width = 200.;

DetectorGroup hpge{
    "hpge",
    coincidence_window_half_width,
    {65536, -0.125, 16383.875},
    {65536, -0.5, 65535.5},
    {8192, -4096., 4096.},
    {2048, 0., 16384.}
};
DetectorGroup labr{
    "labr",
    coincidence_window_half_width,
    {16384, -0.5, 16383.5},
    {16384, -0.03125, 1023.96875},
    {8192, -4096., 4096.},
    {512, 0., 16384.}
};
vector<DetectorGroup> groups = {hpge, labr};

const double tdc_resolution = 0.125; // in nanoseconds, tdc resolution in nanoseconds per bin

vector<SIS3316> modules = {
    {tdc_resolution},
};

const vector<double> timestamp_calibration_parameters{0., 1./16.}; // in microseconds, inverse of the VME clock frequency, which is 16 MHz

vector<Detector> detectors{
    {"labr_1",
        {
            {
                "E", modules[0],  0, {0., 1.}, 5.
            },
        },
        labr,
    },
    {"labr_2",
        {
            {
                "E", modules[0],  1, {0., 1.}, 5.
            },
        },
        labr,
    },
    {"labr_3",
        {
            {
                "E", modules[0],  2, {0., 1.}, 5.
            },
        },
        labr,
    },
    {"labr_4",
        {
            {
                "E", modules[0],  3, {0., 1.}, 5.
            },
        },
        labr,
    },
    {"hpge_1",
        {
            {
                "E", modules[0],  4, {0., 1.}, 20.
            },
        },
        hpge,
    },
    {"hpge_2",
        {
            {
                "E", modules[0],  5, {0., 1.}, 20.
            },
        },
        hpge,
    },
    {"hpge_6",
        {
            {
                "E", modules[0],  6, {0., 1.}, 20.
            },
        },
        hpge,
    },
    {"hpge_4",
        {
            {
                "E", modules[0],  7, {0., 1.}, 20.
            },
        },
        hpge,
    },
};
