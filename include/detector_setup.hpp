#include "branch.hpp"
#include "detector.hpp"

DetectorGroup clover{"clover"};
DetectorGroup cebr{"cebr"};

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

const double tdc_resolution = 0.098; // in nanoseconds per bin
vector<double> timestamp_calibration_parameters{0., 1./16.}; // in microseconds, inverse of the VME clock frequency, which is 16 MHz

vector<Detector> detectors{
    {"clover_1",
        {
            {
                "E1",
                "amplitude_clover_90", 0, energy_raw_histogram_clover, {8.195428e-01, 1.917486e-01},
                "time_clover_90", 0, { 0., tdc_resolution },
                "timestamp_clover_90", 0, timestamp_calibration_parameters
            },
            {
                "E2",
                "amplitude_clover_90", 1, energy_raw_histogram_clover, {4.511201e+00, 2.209234e-01},
                "time_clover_90", 1, { 0., tdc_resolution },
                "timestamp_clover_90", 1, timestamp_calibration_parameters
            },
            {
                "E3",
                "amplitude_clover_90", 2, energy_raw_histogram_clover, {4.082621e+00, 2.246197e-01},
                "time_clover_90", 2, { 0., tdc_resolution },
                "timestamp_clover_90", 2, timestamp_calibration_parameters
            },
            {
                "E4",
                "amplitude_clover_90", 3, energy_raw_histogram_clover, {3.356518e00, 2.433405e-01},
                "time_clover_90", 3, { 0., tdc_resolution },
                "timestamp_clover_90", 3, timestamp_calibration_parameters
            },
        },
        clover,
        energy_histogram_clover,
        timestamp_difference_histogram
    },
    {"clover_3",
        {
            {
                "E1",
                "amplitude_clover_90", 4, energy_raw_histogram_clover, {2.616710e+00, 2.098547e-01},
                "time_clover_90", 4, { 0., tdc_resolution },
                "timestamp_clover_90", 4, timestamp_calibration_parameters
            },
            {
                "E2",
                "amplitude_clover_90", 5, energy_raw_histogram_clover, {2.581603e+00, 2.257879e-01},
                "time_clover_90", 5, { 0., tdc_resolution },
                "timestamp_clover_90", 5, timestamp_calibration_parameters
            },
            {
                "E3",
                "amplitude_clover_90", 6, energy_raw_histogram_clover, {3.241107e+00, 2.320975e-01},
                "time_clover_90", 6, { 0., tdc_resolution },
                "timestamp_clover_90", 6, timestamp_calibration_parameters
            },
            {
                "E4",
                "amplitude_clover_90", 7, energy_raw_histogram_clover, {3.239621e+00, 2.112736e-01},
                "time_clover_90", 7, { 0., tdc_resolution },
                "timestamp_clover_90", 7, timestamp_calibration_parameters
            },
        },
        clover,
        energy_histogram_clover,
        timestamp_difference_histogram
    },
   {"clover_5",
        {
            {
                "E1",
                "amplitude_clover_90", 8, energy_raw_histogram_clover, {3.819561e+00, 2.260582e-01},
                "time_clover_90", 8, { 0., tdc_resolution },
                "timestamp_clover_90", 8, timestamp_calibration_parameters
            },
            {
                "E2",
                "amplitude_clover_90", 9, energy_raw_histogram_clover, {4.040720e+00, 2.296258e-01},
                "time_clover_90", 9, { 0., tdc_resolution },
                "timestamp_clover_90", 9, timestamp_calibration_parameters
            },
            {
                "E3",
                "amplitude_clover_90", 10, energy_raw_histogram_clover, {2.864699e+00, 2.217378e-01},
                "time_clover_90", 10, { 0., tdc_resolution },
                "timestamp_clover_90", 10, timestamp_calibration_parameters
            },
            {
                "E4",
                "amplitude_clover_90", 11, energy_raw_histogram_clover, {3.711482e+00, 2.199104e-01},
                "time_clover_90", 11, { 0., tdc_resolution },
                "timestamp_clover_90", 11, timestamp_calibration_parameters
            },
        },
        clover,
        energy_histogram_clover,
        timestamp_difference_histogram
    },
   {"clover_7",
        {
            {
                "E1",
                "amplitude_clover_90", 12, energy_raw_histogram_clover, {3.234694e+00, 2.278309e-01},
                "time_clover_90", 12, { 0., tdc_resolution },
                "timestamp_clover_90", 12, timestamp_calibration_parameters
            },
            {
                "E2",
                "amplitude_clover_90", 13, energy_raw_histogram_clover, {3.483455e+00, 2.243242e-01},
                "time_clover_90", 13, { 0., tdc_resolution },
                "timestamp_clover_90", 13, timestamp_calibration_parameters
            },
            {
                "E3",
                "amplitude_clover_90", 14, energy_raw_histogram_clover, {3.412767e+00, 2.334142e-01},
                "time_clover_90", 14, { 0., tdc_resolution },
                "timestamp_clover_90", 14, timestamp_calibration_parameters
            },
            {
                "E4",
                "amplitude_clover_90", 15, energy_raw_histogram_clover, {3.972959e+00, 2.287037e-01},
                "time_clover_90", 15, { 0., tdc_resolution },
                "timestamp_clover_90", 15, timestamp_calibration_parameters
            },
        },
        clover,
        energy_histogram_clover,
        timestamp_difference_histogram
    },
   {"clover_B1",
        {
            {
                "E1",
                "amplitude_clover_135", 0, energy_raw_histogram_clover, {2.287037e-01, 1.648521e-01},
                "time_clover_135", 0, { 0., tdc_resolution },
                "timestamp_clover_135", 0, timestamp_calibration_parameters
            },
            {
                "E2",
                "amplitude_clover_135", 1, energy_raw_histogram_clover, {2.297035e+00, 1.629191e-01},
                "time_clover_135", 1, { 0., tdc_resolution },
                "timestamp_clover_135", 1, timestamp_calibration_parameters
            },
            {
                "E3",
                "amplitude_clover_135", 2, energy_raw_histogram_clover, {4.445848e+00, 2.020955e-01},
                "time_clover_135", 2, { 0., tdc_resolution },
                "timestamp_clover_135", 2, timestamp_calibration_parameters
            },
            {
                "E4",
                "amplitude_clover_135", 3, energy_raw_histogram_clover, {3.211260e+00, 1.998439e-01},
                "time_clover_135", 3, { 0., tdc_resolution },
                "timestamp_clover_135", 3, timestamp_calibration_parameters
            },
        },
        clover,
        energy_histogram_clover,
        timestamp_difference_histogram
    },
    {"clover_B4",
        {
            {
                "E1",
                "amplitude_clover_135", 4, energy_raw_histogram_clover, {2.719021e+00, 2.258225e-01},
                "time_clover_135", 4, { 0., tdc_resolution },
                "timestamp_clover_135", 4, timestamp_calibration_parameters
            },
            {
                "E2",
                "amplitude_clover_135", 5, energy_raw_histogram_clover, {-4.628883e-01, 1.068767e+00},
                "time_clover_135", 5, { 0., tdc_resolution },
                "timestamp_clover_135", 5, timestamp_calibration_parameters
            },
            {
                "E3",
                "amplitude_clover_135", 6, energy_raw_histogram_clover, {4.020829e+00, 2.328474e-01},
                "time_clover_135", 6, { 0., tdc_resolution },
                "timestamp_clover_135", 6, timestamp_calibration_parameters
            },
            {
                "E4",
                "amplitude_clover_135", 7, energy_raw_histogram_clover, {3.418135e+00, 2.239762e-01},
                "time_clover_135", 7, { 0., tdc_resolution },
                "timestamp_clover_135", 7, timestamp_calibration_parameters
            },
        },
        clover,
        energy_histogram_clover,
        timestamp_difference_histogram
    },
    {"clover_B5",
        {
            {
                "E1",
                "amplitude_clover_135", 8, energy_raw_histogram_clover, {2.822781e+00, 2.274120e-01},
                "time_clover_135", 8, { 0., tdc_resolution },
                "timestamp_clover_135", 8, timestamp_calibration_parameters
            },
            {
                "E2",
                "amplitude_clover_135", 9, energy_raw_histogram_clover, {2.945326e+00, 2.296954e-01},
                "time_clover_135", 9, { 0., tdc_resolution },
                "timestamp_clover_135", 9, timestamp_calibration_parameters
            },
            {
                "E3",
                "amplitude_clover_135", 10, energy_raw_histogram_clover, {2.915758e+00, 2.228363e-01},
                "time_clover_135", 10, { 0., tdc_resolution },
                "timestamp_clover_135", 10, timestamp_calibration_parameters
            },
            {
                "E4",
                "amplitude_clover_135", 11, energy_raw_histogram_clover, {3.046281e+00, 2.270979e-01},
                "time_clover_135", 11, { 0., tdc_resolution },
                "timestamp_clover_135", 11, timestamp_calibration_parameters
            },
        },
        clover,
        energy_histogram_clover,
        timestamp_difference_histogram
    },
    {"clover_B6",
        {
            {
                "E1",
                "amplitude_clover_135", 12, energy_raw_histogram_clover, {3.278164e+00, 2.218043e-01},
                "time_clover_135", 12, { 0., tdc_resolution },
                "timestamp_clover_135", 12, timestamp_calibration_parameters
            },
            {
                "E2",
                "amplitude_clover_135", 13, energy_raw_histogram_clover, {3.039850e+00, 2.251673e-01},
                "time_clover_135", 13, { 0., tdc_resolution },
                "timestamp_clover_135", 13, timestamp_calibration_parameters
            },
            {
                "E3",
                "amplitude_clover_135", 14, energy_raw_histogram_clover, {3.206270e+00, 2.237607e-01},
                "time_clover_135", 14, { 0., tdc_resolution },
                "timestamp_clover_135", 14, timestamp_calibration_parameters
            },
            {
                "E4",
                "amplitude_clover_135", 15, energy_raw_histogram_clover, {4.102127e+00, 2.303245e-01},
                "time_clover_135", 15, { 0., tdc_resolution },
                "timestamp_clover_135", 15, timestamp_calibration_parameters
            },
        },
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
        cebr,
        energy_histogram_cebr,
        timestamp_difference_histogram
    },
    {"cebr_I",
        {
            {
                "E",
                "integration_long", 4, energy_raw_histogram_cebr, {1.706866e+01+2.685529e+00},
                "channel_time", 4, { 0., tdc_resolution },
                "timestamp_cebr", 4, timestamp_calibration_parameters
            },
        },
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
        cebr,
        energy_histogram_cebr,
        timestamp_difference_histogram
    },
    {"cebr_BB",
        {
            {
                "E",
                "integration_long", 8, energy_raw_histogram_cebr, {2.462225e+01+2.892358e+00},
                "channel_time", 8, { 0., tdc_resolution },
                "timestamp_cebr", 8, timestamp_calibration_parameters
            },
        },
        cebr,
        energy_histogram_cebr,
        timestamp_difference_histogram
    },
    {"cebr_BC",
        {
            {
                "E",
                "integration_long", 9, energy_raw_histogram_cebr, {7.986022e+00+3.196667e+00},
                "channel_time", 9, { 0., tdc_resolution },
                "timestamp_cebr", 9, timestamp_calibration_parameters
            },
        },
        cebr,
        energy_histogram_cebr,
        timestamp_difference_histogram
    },
    {"cebr_BD",
        {
            {
                "E",
                "integration_long", 10, energy_raw_histogram_cebr, {1.622308e+01+3.001918e+00},
                "channel_time", 10, { 0., tdc_resolution },
                "timestamp_cebr", 10, timestamp_calibration_parameters
            },
        },
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
        cebr,
        energy_histogram_cebr,
        timestamp_difference_histogram
    },
};
