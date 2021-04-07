/**
 * Linear energy calibration for clover channels from run 487, using the 511 keV, 1461 keV, 
 * and 2615 keV background lines.
 */
#pragma once

#include "branch.hpp"
#include "detector.hpp"

DetectorGroup clover{
    "clover",
    {4096, 0., 16384.},
    {1000, -500., 500.},
};
DetectorGroup cebr{
    "cebr",
    {2048, 0., 16384.},
    {1000, -500., 500.},
};

vector<DetectorGroup> detector_groups {clover, cebr};

vector<Branch> branches{
	{"amplitude_clover_90" , 16, 16, false},
	{"amplitude_clover_135", 16, 16, false},
	{"integration_long"    , 16, 16, false},
	{"time_clover_90"      , 16, 16, false},
	{"time_clover_135"     , 16, 16, false},
	{"channel_time"        , 16, 16, false},
    {"timestamp_clover_90" ,  1, 16,  true},
    {"timestamp_clover_135",  1, 16,  true},
    {"timestamp_cebr"      ,  1, 16,  true}
};

const HistogramProperties energy_histogram_clover{65536, 0., 16384.};
const HistogramProperties energy_raw_histogram_clover{65536, 0., 65536.};

const HistogramProperties energy_histogram_cebr{4096, 0., 16384.};
const HistogramProperties energy_raw_histogram_cebr{4096, 0., 4096.};

const HistogramProperties timestamp_difference_histogram{10000, 0., 10000.};

const pair<double, double> channel_coincidence_window = {-100., 100.};

const double tdc_resolution = 0.098; // in nanoseconds per bin
const vector<double> timestamp_calibration_parameters{0., 1./16.}; // in microseconds, inverse of the VME clock frequency, which is 16 MHz

vector<Detector> detectors{
    {"clover_1",
        {
            {
                "E1",
                "amplitude_clover_90", 0, energy_raw_histogram_clover, {-1.485047e+00, 2.901548e-01, -1.016733e-07},
                "time_clover_90", 0, { 0., tdc_resolution },
                "timestamp_clover_90", 0, timestamp_calibration_parameters
            },
            {
                "E2",
                "amplitude_clover_90", 1, energy_raw_histogram_clover, {-1.272707e+00, 3.343115e-01, -1.360288e-07},
                "time_clover_90", 1, { 0., tdc_resolution },
                "timestamp_clover_90", 1, timestamp_calibration_parameters
            },
            {
                "E3",
                "amplitude_clover_90", 2, energy_raw_histogram_clover, {-7.617836e-01, 3.404271e-01, -1.078742e-07},
                "time_clover_90", 2, { 0., tdc_resolution },
                "timestamp_clover_90", 2, timestamp_calibration_parameters
            },
            {
                "E4",
                "amplitude_clover_90", 3, energy_raw_histogram_clover, {1.001582e-01, 3.681067e-01, -9.131797e-08},
                "time_clover_90", 3, { 0., tdc_resolution },
                "timestamp_clover_90", 3, timestamp_calibration_parameters
            },
        },
        channel_coincidence_window,
        clover,
        energy_histogram_clover,
        timestamp_difference_histogram
    },
    {"clover_3",
        {
            {
                "E1",
                "amplitude_clover_90", 4, energy_raw_histogram_clover, {5.186644e+00, 3.181802e-01},
                "time_clover_90", 4, { 0., tdc_resolution },
                "timestamp_clover_90", 4, timestamp_calibration_parameters
            },
            {
                "E2",
                "amplitude_clover_90", 5, energy_raw_histogram_clover, {3.594272e-01, 3.414518e-01},
                "time_clover_90", 5, { 0., tdc_resolution },
                "timestamp_clover_90", 5, timestamp_calibration_parameters
            },
            {
                "E3",
                "amplitude_clover_90", 6, energy_raw_histogram_clover, {3.970839e+00, 3.519584e-01},
                "time_clover_90", 6, { 0., tdc_resolution },
                "timestamp_clover_90", 6, timestamp_calibration_parameters
            },
            {
                "E4",
                "amplitude_clover_90", 7, energy_raw_histogram_clover, {4.794616e+00, 3.205708e-01},
                "time_clover_90", 7, { 0., tdc_resolution },
                "timestamp_clover_90", 7, timestamp_calibration_parameters
            },
        },
        channel_coincidence_window,
        clover,
        energy_histogram_clover,
        timestamp_difference_histogram
    },
    {"clover_5",
        {
            {
                "E1",
                "amplitude_clover_90", 8, energy_raw_histogram_clover, {2.408986e+00, 3.421157e-01},
                "time_clover_90", 8, { 0., tdc_resolution },
                "timestamp_clover_90", 8, timestamp_calibration_parameters
            },
            {
                "E2",
                "amplitude_clover_90", 9, energy_raw_histogram_clover, {4.161841e+00, 3.471642e-01},
                "time_clover_90", 9, { 0., tdc_resolution },
                "timestamp_clover_90", 9, timestamp_calibration_parameters
            },
            {
                "E3",
                "amplitude_clover_90", 10, energy_raw_histogram_clover, {2.964035e+00, 3.360415e-01},
                "time_clover_90", 10, { 0., tdc_resolution },
                "timestamp_clover_90", 10, timestamp_calibration_parameters
            },
            {
                "E4",
                "amplitude_clover_90", 11, energy_raw_histogram_clover, {3.063589e+00, 3.330917e-01},
                "time_clover_90", 11, { 0., tdc_resolution },
                "timestamp_clover_90", 11, timestamp_calibration_parameters
            },
        },
        channel_coincidence_window,
        clover,
        energy_histogram_clover,
        timestamp_difference_histogram
    },
   {"clover_7",
        {
            {
                "E1",
                "amplitude_clover_90", 12, energy_raw_histogram_clover, {2.192697e+00, 3.430912e-01},
                "time_clover_90", 12, { 0., tdc_resolution },
                "timestamp_clover_90", 12, timestamp_calibration_parameters
            },
            {
                "E2",
                "amplitude_clover_90", 13, energy_raw_histogram_clover, {3.672990e+00, 3.392175e-01},
                "time_clover_90", 13, { 0., tdc_resolution },
                "timestamp_clover_90", 13, timestamp_calibration_parameters
            },
            {
                "E3",
                "amplitude_clover_90", 14, energy_raw_histogram_clover, {2.950477e+00, 3.511651e-01},
                "time_clover_90", 14, { 0., tdc_resolution },
                "timestamp_clover_90", 14, timestamp_calibration_parameters
            },
            {
                "E4",
                "amplitude_clover_90", 15, energy_raw_histogram_clover, {4.216275e+00, 3.446497e-01},
                "time_clover_90", 15, { 0., tdc_resolution },
                "timestamp_clover_90", 15, timestamp_calibration_parameters
            },
        },
        channel_coincidence_window,
        clover,
        energy_histogram_clover,
        timestamp_difference_histogram
    },
   {"clover_B1",
        {
            {
                "E1",
                "amplitude_clover_135", 0, energy_raw_histogram_clover, {3.188829e+00, 1.969612e-01},
                "time_clover_135", 0, { 0., tdc_resolution },
                "timestamp_clover_135", 0, timestamp_calibration_parameters
            },
            {
                "E2",
                "amplitude_clover_135", 1, energy_raw_histogram_clover, {3.660195e+00, 1.980626e-01},
                "time_clover_135", 1, { 0., tdc_resolution },
                "timestamp_clover_135", 1, timestamp_calibration_parameters
            },
            {
                "E3",
                "amplitude_clover_135", 2, energy_raw_histogram_clover, {3.551523e+00, 2.015126e-01},
                "time_clover_135", 2, { 0., tdc_resolution },
                "timestamp_clover_135", 2, timestamp_calibration_parameters
            },
            {
                "E4",
                "amplitude_clover_135", 3, energy_raw_histogram_clover, {2.700718e+00, 1.974208e-01},
                "time_clover_135", 3, { 0., tdc_resolution },
                "timestamp_clover_135", 3, timestamp_calibration_parameters
            },
        },
        channel_coincidence_window,
        clover,
        energy_histogram_clover,
        timestamp_difference_histogram
    },
    {"clover_B4",
        {
            {
                "E1",
                "amplitude_clover_135", 4, energy_raw_histogram_clover, {1.238283e+00, 3.417338e-01},
                "time_clover_135", 4, { 0., tdc_resolution },
                "timestamp_clover_135", 4, timestamp_calibration_parameters
            },
            // {
            //     "E2",
            //     "amplitude_clover_135", 5, energy_raw_histogram_clover, {5.688416e+00, 1.064333e+00},
            //     "time_clover_135", 5, { 0., tdc_resolution },
            //     "timestamp_clover_135", 5, timestamp_calibration_parameters
            // },
            {
                "E3",
                "amplitude_clover_135", 6, energy_raw_histogram_clover, {2.980456e+00, 3.519861e-01},
                "time_clover_135", 6, { 0., tdc_resolution },
                "timestamp_clover_135", 6, timestamp_calibration_parameters
            },
            {
                "E4",
                "amplitude_clover_135", 7, energy_raw_histogram_clover, {2.887370e+00, 3.390173e-01},
                "time_clover_135", 7, { 0., tdc_resolution },
                "timestamp_clover_135", 7, timestamp_calibration_parameters
            },
        },
        channel_coincidence_window,
        clover,
        energy_histogram_clover,
        timestamp_difference_histogram
    },
    {"clover_B5",
        {
            {
                "E1",
                "amplitude_clover_135", 8, energy_raw_histogram_clover, {2.605859e+00,3.458897e-01},
                "time_clover_135", 8, { 0., tdc_resolution },
                "timestamp_clover_135", 8, timestamp_calibration_parameters
            },
            {
                "E2",
                "amplitude_clover_135", 9, energy_raw_histogram_clover, {1.205310e+00, 3.492821e-01},
                "time_clover_135", 9, { 0., tdc_resolution },
                "timestamp_clover_135", 9, timestamp_calibration_parameters
            },
            {
                "E3",
                "amplitude_clover_135", 10, energy_raw_histogram_clover, {1.373708e+00, 3.392059e-01},
                "time_clover_135", 10, { 0., tdc_resolution },
                "timestamp_clover_135", 10, timestamp_calibration_parameters
            },
            {
                "E4",
                "amplitude_clover_135", 11, energy_raw_histogram_clover, {1.694657e+00, 3.457768e-01},
                "time_clover_135", 11, { 0., tdc_resolution },
                "timestamp_clover_135", 11, timestamp_calibration_parameters
            },
        },
        channel_coincidence_window,
        clover,
        energy_histogram_clover,
        timestamp_difference_histogram
    },
    {"clover_B6",
        {
            {
                "E1",
                "amplitude_clover_135", 12, energy_raw_histogram_clover, {1.082980e+00, 3.380270e-01},
                "time_clover_135", 12, { 0., tdc_resolution },
                "timestamp_clover_135", 12, timestamp_calibration_parameters
            },
            {
                "E2",
                "amplitude_clover_135", 13, energy_raw_histogram_clover, {8.868178e-01, 3.429586e-01},
                "time_clover_135", 13, { 0., tdc_resolution },
                "timestamp_clover_135", 13, timestamp_calibration_parameters
            },
            {
                "E3",
                "amplitude_clover_135", 14, energy_raw_histogram_clover, {2.499840e+00, 3.416498e-01},
                "time_clover_135", 14, { 0., tdc_resolution },
                "timestamp_clover_135", 14, timestamp_calibration_parameters
            },
            {
                "E4",
                "amplitude_clover_135", 15, energy_raw_histogram_clover, {4.175447e+00, 3.506034e-01},
                "time_clover_135", 15, { 0., tdc_resolution },
                "timestamp_clover_135", 15, timestamp_calibration_parameters
            },
        },
        channel_coincidence_window,
        clover,
        energy_histogram_clover,
        timestamp_difference_histogram
    },
    {"cebr_B",
        {
            {
                "E",
                "integration_long", 0, energy_raw_histogram_cebr, {7.970388e+00, 2.910997e+00},
                "channel_time", 0, { 0., tdc_resolution },
                "timestamp_cebr", 0, timestamp_calibration_parameters
            },
        },
        channel_coincidence_window,
        cebr,
        energy_histogram_cebr,
        timestamp_difference_histogram
    },
    {"cebr_C",
        {
            {
                "E",
                "integration_long", 1, energy_raw_histogram_cebr, {1.806513e+01, 2.864689e+00},
                "channel_time", 1, { 0., tdc_resolution },
                "timestamp_cebr", 1, timestamp_calibration_parameters
            },
        },
        channel_coincidence_window,
        cebr,
        energy_histogram_cebr,
        timestamp_difference_histogram
    },
    {"cebr_E",
        {
            {
                "E",
                "integration_long", 2, energy_raw_histogram_cebr, {1.431229e+01, 3.107743e+00},
                "channel_time", 2, { 0., tdc_resolution },
                "timestamp_cebr", 2, timestamp_calibration_parameters
            },
        },
        channel_coincidence_window,
        cebr,
        energy_histogram_cebr,
        timestamp_difference_histogram
    },
    {"cebr_F",
        {
            {
                "E",
                "integration_long", 3, energy_raw_histogram_cebr, {1.299113e+01, 2.958187e+00},
                "channel_time", 3, { 0., tdc_resolution },
                "timestamp_cebr", 3, timestamp_calibration_parameters
            },
        },
        channel_coincidence_window,
        cebr,
        energy_histogram_cebr,
        timestamp_difference_histogram
    },
    {"cebr_I",
        {
            {
                "E",
                "integration_long", 4, energy_raw_histogram_cebr, {1.706866e+01, 2.685529e+00},
                "channel_time", 4, { 0., tdc_resolution },
                "timestamp_cebr", 4, timestamp_calibration_parameters
            },
        },
        channel_coincidence_window,
        cebr,
        energy_histogram_cebr,
        timestamp_difference_histogram
    },
    {"cebr_M",
        {
            {
                "E",
                "integration_long", 5, energy_raw_histogram_cebr, {1.681380e+01, 2.793310e+00},
                "channel_time", 5, { 0., tdc_resolution },
                "timestamp_cebr", 5, timestamp_calibration_parameters
            },
        },
        channel_coincidence_window,
        cebr,
        energy_histogram_cebr,
        timestamp_difference_histogram
    },
    {"cebr_BB",
        {
            {
                "E",
                "integration_long", 8, energy_raw_histogram_cebr, {2.462225e+01, 2.892358e+00},
                "channel_time", 8, { 0., tdc_resolution },
                "timestamp_cebr", 8, timestamp_calibration_parameters
            },
        },
        channel_coincidence_window,
        cebr,
        energy_histogram_cebr,
        timestamp_difference_histogram
    },
    {"cebr_BC",
        {
            {
                "E",
                "integration_long", 9, energy_raw_histogram_cebr, {7.986022e+00, 3.196667e+00},
                "channel_time", 9, { 0., tdc_resolution },
                "timestamp_cebr", 9, timestamp_calibration_parameters
            },
        },
        channel_coincidence_window,
        cebr,
        energy_histogram_cebr,
        timestamp_difference_histogram
    },
    {"cebr_BD",
        {
            {
                "E",
                "integration_long", 10, energy_raw_histogram_cebr, {1.622308e+01, 3.001918e+00},
                "channel_time", 10, { 0., tdc_resolution },
                "timestamp_cebr", 10, timestamp_calibration_parameters
            },
        },
        channel_coincidence_window,
        cebr,
        energy_histogram_cebr,
        timestamp_difference_histogram
    },
    {"cebr_BK",
        {
            {
                "E",
                "integration_long", 11, energy_raw_histogram_cebr, {2.331539e+01, 2.609833e+00},
                "channel_time", 11, { 0., tdc_resolution },
                "timestamp_cebr", 11, timestamp_calibration_parameters
            },
        },
        channel_coincidence_window,
        cebr,
        energy_histogram_cebr,
        timestamp_difference_histogram
    },
    {"cebr_BL",
        {
            {
                "E",
                "integration_long", 12, energy_raw_histogram_cebr, {1.418627e+01, 3.085454e+00},
                "channel_time", 12, { 0., tdc_resolution },
                "timestamp_cebr", 12, timestamp_calibration_parameters
            },
        },
        channel_coincidence_window,
        cebr,
        energy_histogram_cebr,
        timestamp_difference_histogram
    },
    {"cebr_BM",
        {
            {
                "E",
                "integration_long", 13, energy_raw_histogram_cebr, {1.626798e+01, 2.907252e+00},
                "channel_time", 13, { 0., tdc_resolution },
                "timestamp_cebr", 13, timestamp_calibration_parameters
            },
        },
        channel_coincidence_window,
        cebr,
        energy_histogram_cebr,
        timestamp_difference_histogram
    },
};
