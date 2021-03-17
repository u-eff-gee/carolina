#include <utility>

using std::pair;

#include "detector.hpp"

DetectorGroup clover{"clover"};
DetectorGroup cebr{"cebr"};

vector<DetectorGroup> detector_groups {clover, cebr};

vector<pair<string, unsigned int>> branches{
	{"amplitude_clover_90", 16},
	{"amplitude_clover_135", 16},
	{"integration_long", 16},
	{"time_clover_90", 16},
	{"time_clover_135", 16},
	{"channel_time", 16},
};

const unsigned int n_bins_energy_clover = 65536;
const double min_energy_clover = 0.5;
const double max_energy_clover = 10000.5;
const unsigned int n_bins_energy_cebr = 4096;
const double min_energy_cebr = 0.5;
const double max_energy_cebr = 10000.5;

const double tdc_resolution = 0.098; // Nanoseconds per bin

vector<Detector> detectors{
    {"clover_1",
        {
            {
                "E1",
                "amplitude_clover_90", 0, {n_bins_energy_clover, min_energy_clover, max_energy_clover}, {8.195428e-01, 1.917486e-01},
                "time_clover_90", 0, { tdc_resolution }
            },
            {
                "E2",
                "amplitude_clover_90", 1, {n_bins_energy_clover, min_energy_clover, max_energy_clover}, {4.511201e+00, 2.209234e-01},
                "time_clover_90", 1, { tdc_resolution }
            },
            {
                "E3",
                "amplitude_clover_90", 2, {n_bins_energy_clover, min_energy_clover, max_energy_clover}, {4.082621e+00, 2.246197e-01},
                "time_clover_90", 2, { tdc_resolution }
            },
            {
                "E4",
                "amplitude_clover_90", 3, {n_bins_energy_clover, min_energy_clover, max_energy_clover}, {3.356518e00, 2.433405e-01},
                "time_clover_90", 3, { tdc_resolution }
            },
        },
        clover
    },
    {"clover_3",
        {
            {
                "E1",
                "amplitude_clover_90", 4, {n_bins_energy_clover, min_energy_clover, max_energy_clover}, {2.616710e+00, 2.098547e-01},
                "time_clover_90", 4, { tdc_resolution }
            },
            {
                "E2",
                "amplitude_clover_90", 5, {n_bins_energy_clover, min_energy_clover, max_energy_clover}, {2.581603e+00, 2.257879e-01},
                "time_clover_90", 5, { tdc_resolution }
            },
            {
                "E3",
                "amplitude_clover_90", 6, {n_bins_energy_clover, min_energy_clover, max_energy_clover}, {3.241107e+00, 2.320975e-01},
                "time_clover_90", 6, { tdc_resolution }
            },
            {
                "E4",
                "amplitude_clover_90", 7, {n_bins_energy_clover, min_energy_clover, max_energy_clover}, {3.239621e+00, 2.112736e-01},
                "time_clover_90", 7, { tdc_resolution }
            },
        },
        clover
    },
   {"clover_5",
        {
            {
                "E1",
                "amplitude_clover_90", 8, {n_bins_energy_clover, min_energy_clover, max_energy_clover}, {3.819561e+00, 2.260582e-01},
                "time_clover_90", 8, { tdc_resolution }
            },
            {
                "E2",
                "amplitude_clover_90", 9, {n_bins_energy_clover, min_energy_clover, max_energy_clover}, {4.040720e+00, 2.296258e-01},
                "time_clover_90", 9, { tdc_resolution }
            },
            {
                "E3",
                "amplitude_clover_90", 10, {n_bins_energy_clover, min_energy_clover, max_energy_clover}, {2.864699e+00, 2.217378e-01},
                "time_clover_90", 10, { tdc_resolution }
            },
            {
                "E4",
                "amplitude_clover_90", 11, {n_bins_energy_clover, min_energy_clover, max_energy_clover}, {3.711482e+00, 2.199104e-01},
                "time_clover_90", 11, { tdc_resolution }
            },
        },
        clover
    },
   {"clover_7",
        {
            {
                "E1",
                "amplitude_clover_90", 12, {n_bins_energy_clover, min_energy_clover, max_energy_clover}, {3.234694e+00, 2.278309e-01},
                "time_clover_90", 12, { tdc_resolution }
            },
            {
                "E2",
                "amplitude_clover_90", 13, {n_bins_energy_clover, min_energy_clover, max_energy_clover}, {3.483455e+00, 2.243242e-01},
                "time_clover_90", 13, { tdc_resolution }
            },
            {
                "E3",
                "amplitude_clover_90", 14, {n_bins_energy_clover, min_energy_clover, max_energy_clover}, {3.412767e+00, 2.334142e-01},
                "time_clover_90", 14, { tdc_resolution }
            },
            {
                "E4",
                "amplitude_clover_90", 15, {n_bins_energy_clover, min_energy_clover, max_energy_clover}, {3.972959e+00, 2.287037e-01},
                "time_clover_90", 15, { tdc_resolution }
            },
        },
        clover
    },
   {"clover_B1",
        {
            {
                "E1",
                "amplitude_clover_135", 0, {n_bins_energy_clover, min_energy_clover, max_energy_clover}, {2.287037e-01, 1.648521e-01},
                "time_clover_135", 0, { tdc_resolution }
            },
            {
                "E2",
                "amplitude_clover_135", 1, {n_bins_energy_clover, min_energy_clover, max_energy_clover}, {2.297035e+00, 1.629191e-01},
                "time_clover_135", 1, { tdc_resolution }
            },
            {
                "E3",
                "amplitude_clover_135", 2, {n_bins_energy_clover, min_energy_clover, max_energy_clover}, {4.445848e+00, 2.020955e-01},
                "time_clover_135", 2, { tdc_resolution }
            },
            {
                "E4",
                "amplitude_clover_135", 3, {n_bins_energy_clover, min_energy_clover, max_energy_clover}, {3.211260e+00, 1.998439e-01},
                "time_clover_135", 3, { tdc_resolution }
            },
        },
        clover
    },
    {"clover_B4",
        {
            {
                "E1",
                "amplitude_clover_135", 4, {n_bins_energy_clover, min_energy_clover, max_energy_clover}, {2.719021e+00, 2.258225e-01},
                "time_clover_135", 4, { tdc_resolution }
            },
            {
                "E2",
                "amplitude_clover_135", 5, {n_bins_energy_clover, min_energy_clover, max_energy_clover}, {-4.628883e-01, 1.068767e+00},
                "time_clover_135", 5, { tdc_resolution }
            },
            {
                "E3",
                "amplitude_clover_135", 6, {n_bins_energy_clover, min_energy_clover, max_energy_clover}, {4.020829e+00, 2.328474e-01},
                "time_clover_135", 6, { tdc_resolution }
            },
            {
                "E4",
                "amplitude_clover_135", 7, {n_bins_energy_clover, min_energy_clover, max_energy_clover}, {3.418135e+00, 2.239762e-01},
                "time_clover_135", 7, { tdc_resolution }
            },
        },
        clover
    },
    {"clover_B5",
        {
            {
                "E1",
                "amplitude_clover_135", 8, {n_bins_energy_clover, min_energy_clover, max_energy_clover}, {2.822781e+00, 2.274120e-01},
                "time_clover_135", 8, { tdc_resolution }
            },
            {
                "E2",
                "amplitude_clover_135", 9, {n_bins_energy_clover, min_energy_clover, max_energy_clover}, {2.945326e+00, 2.296954e-01},
                "time_clover_135", 9, { tdc_resolution }
            },
            {
                "E3",
                "amplitude_clover_135", 10, {n_bins_energy_clover, min_energy_clover, max_energy_clover}, {2.915758e+00, 2.228363e-01},
                "time_clover_135", 10, { tdc_resolution }
            },
            {
                "E4",
                "amplitude_clover_135", 11, {n_bins_energy_clover, min_energy_clover, max_energy_clover}, {3.046281e+00, 2.270979e-01},
                "time_clover_135", 11, { tdc_resolution }
            },
        },
        clover
    },
    {"clover_B6",
        {
            {
                "E1",
                "amplitude_clover_135", 12, {n_bins_energy_clover, min_energy_clover, max_energy_clover}, {3.278164e+00, 2.218043e-01},
                "time_clover_135", 12, { tdc_resolution }
            },
            {
                "E2",
                "amplitude_clover_135", 13, {n_bins_energy_clover, min_energy_clover, max_energy_clover}, {3.039850e+00, 2.251673e-01},
                "time_clover_135", 13, { tdc_resolution }
            },
            {
                "E3",
                "amplitude_clover_135", 14, {n_bins_energy_clover, min_energy_clover, max_energy_clover}, {3.206270e+00, 2.237607e-01},
                "time_clover_135", 14, { tdc_resolution }
            },
            {
                "E4",
                "amplitude_clover_135", 15, {n_bins_energy_clover, min_energy_clover, max_energy_clover}, {4.102127e+00, 2.303245e-01},
                "time_clover_135", 15, { tdc_resolution }
            },
        },
        clover
    },
    {"cebr_B",
        {
            {
                "E",
                "integration_long", 0, {n_bins_energy_cebr, min_energy_cebr, max_energy_cebr}, {7.970388e+00, 2.910997e+00},
                "channel_time", 0, { tdc_resolution }
            },
        },
        cebr
    },
    {"cebr_C",
        {
            {
                "E",
                "integration_long", 1, {n_bins_energy_cebr, min_energy_cebr, max_energy_cebr}, {1.806513e+01, 2.864689e+00},
                "channel_time", 1, { tdc_resolution }
            },
        },
        cebr
    },
    {"cebr_E",
        {
            {
                "E",
                "integration_long", 2, {n_bins_energy_cebr, min_energy_cebr, max_energy_cebr}, {1.431229e+01, 3.107743e+00},
                "channel_time", 2, { tdc_resolution }
            },
        },
        cebr
    },
    {"cebr_F",
        {
            {
                "E",
                "integration_long", 3, {n_bins_energy_cebr, min_energy_cebr, max_energy_cebr}, {1.299113e+01, 2.958187e+00},
                "channel_time", 3, { tdc_resolution }
            },
        },
        cebr
    },
    {"cebr_I",
        {
            {
                "E",
                "integration_long", 4, {n_bins_energy_cebr, min_energy_cebr, max_energy_cebr}, {1.706866e+01+2.685529e+00},
                "channel_time", 4, { tdc_resolution }
            },
        },
        cebr
    },
    {"cebr_M",
        {
            {
                "E",
                "integration_long", 5, {n_bins_energy_cebr, min_energy_cebr, max_energy_cebr}, {1.681380e+01, 2.793310e+00},
                "channel_time", 5, { tdc_resolution }
            },
        },
        cebr
    },
    {"cebr_BB",
        {
            {
                "E",
                "integration_long", 8, {n_bins_energy_cebr, min_energy_cebr, max_energy_cebr}, {2.462225e+01+2.892358e+00},
                "channel_time", 8, { tdc_resolution }
            },
        },
        cebr
    },
    {"cebr_BC",
        {
            {
                "E",
                "integration_long", 9, {n_bins_energy_cebr, min_energy_cebr, max_energy_cebr}, {7.986022e+00+3.196667e+00},
                "channel_time", 9, { tdc_resolution }
            },
        },
        cebr
    },
    {"cebr_BD",
        {
            {
                "E",
                "integration_long", 10, {n_bins_energy_cebr, min_energy_cebr, max_energy_cebr}, {1.622308e+01+3.001918e+00},
                "channel_time", 10, { tdc_resolution }
            },
        },
        cebr
    },
    {"cebr_BK",
        {
            {
                "E",
                "integration_long", 11, {n_bins_energy_cebr, min_energy_cebr, max_energy_cebr}, {2.331539e+01, 2.609833e+00},
                "channel_time", 11, { tdc_resolution }
            },
        },
        cebr
    },
    {"cebr_BL",
        {
            {
                "E",
                "integration_long", 12, {n_bins_energy_cebr, min_energy_cebr, max_energy_cebr}, {1.418627e+01, 3.085454e+00},
                "channel_time", 12, { tdc_resolution }
            },
        },
        cebr
    },
    {"cebr_BM",
        {
            {
                "E",
                "integration_long", 13, {n_bins_energy_cebr, min_energy_cebr, max_energy_cebr}, {1.626798e+01, 2.907252e+00},
                "channel_time", 13, { tdc_resolution }
            },
        },
        cebr
    },
};
