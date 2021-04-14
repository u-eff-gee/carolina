/**
 * Energy calibration for clover channels from run 487, using background lines.
 */
#pragma once

#include "mdpp16.hpp"
#include "detector.hpp"

const double coincidence_window = 200.;

DetectorGroup clover{
    "clover",
    coincidence_window,
    {16384, 0., 16384.},
    {65536, 0., 65536.},
    {1000, -500., 500.},
    {2048, 0., 16384.}
};
DetectorGroup cebr{
    "cebr",
    coincidence_window,
    {4096, 0., 16384.},
    {4096, 0., 4096.},
    {1000, -500., 500.},
    {512, 0., 16384.}
};
vector<DetectorGroup> groups = {clover, cebr};

const double tdc_resolution = 0.098; // in nanoseconds, tdc resolution in nanoseconds per bin

vector<MDPP16> modules = {
    {{"amplitude_clover_90"}, {"time_clover_90"}, {"timestamp_clover_90"}, tdc_resolution},
    {{"amplitude_clover_135"}, {"time_clover_135"}, {"timestamp_clover_135"}, tdc_resolution},
    {{"integration_long"}, {"channel_time"}, {"timestamp_cebr"}, tdc_resolution},
};

const vector<double> timestamp_calibration_parameters{0., 1./16.}; // in microseconds, inverse of the VME clock frequency, which is 16 MHz

vector<Detector> detectors{
    {"clover_1",
        {
            {
                "E1", modules[0],  0, {-1.485047e+00, 2.901548e-01, -1.016733e-07}
            },
            {
                "E2", modules[0],  1, {-1.272707e+00, 3.343115e-01, -1.360288e-07},
            },
            {
                "E3", modules[0],  2, {-7.617836e-01, 3.404271e-01, -1.078742e-07},
            },
            {
                "E4", modules[0],  3, {1.001582e-01, 3.681067e-01, -9.131797e-08},
            },
        },
        clover,
    },
    {"clover_3",
        {
            {
                "E1", modules[0],  4, {5.186644e+00, 3.181802e-01},
            },
            {
                "E2", modules[0],  5, {3.594272e-01, 3.414518e-01},
            },
            {
                "E3", modules[0],  6, {3.970839e+00, 3.519584e-01},
            },
            {
                "E4", modules[0],  7, {4.794616e+00, 3.205708e-01},
            },
        },
        clover,
    },
    {"clover_5",
        {
            {
                "E1", modules[0],  8, {2.408986e+00, 3.421157e-01},
            },
            {
                "E2", modules[0],  9, {4.161841e+00, 3.471642e-01},
            },
            {
                "E3", modules[0], 10, {2.964035e+00, 3.360415e-01},
            },
            {
                "E4", modules[0], 11, {3.063589e+00, 3.330917e-01},
            },
        },
        clover,
    },
    {"clover_7",
        {
            {
                "E1", modules[0], 12, {2.192697e+00, 3.430912e-01},
            },
            {
                "E2", modules[0], 13, {3.672990e+00, 3.392175e-01},
            },
            {
                "E3", modules[0], 14, {2.950477e+00, 3.511651e-01},
            },
            {
                "E4", modules[0], 15, {4.216275e+00, 3.446497e-01},
            },
        },
        clover,
    },
    {"clover_B1",
        {
            {
                "E1", modules[1],  0, {3.188829e+00, 1.969612e-01},
            },
            {
                "E2", modules[1],  1, {3.660195e+00, 1.980626e-01},
            },
            {
                "E3", modules[1],  2, {3.551523e+00, 2.015126e-01},
            },
            {
                "E4", modules[1],  3, {2.700718e+00, 1.974208e-01},
            },
        },
        clover,
    },
    {"clover_B4",
        {
            {
                "E1", modules[1],  4, {1.238283e+00, 3.417338e-01},
            },
            {
                "E2", modules[1],  5, {5.688416e+00, 1.064333e+00},
            },
            {
                "E3", modules[1],  6, {2.980456e+00, 3.519861e-01},
            },
            {
                "E4", modules[1],  7, {2.887370e+00, 3.390173e-01},
            },
        },
        clover,
    },
    {"clover_B5",
        {
            {
                "E1", modules[1],  8, {2.605859e+00,3.458897e-01},
            },
            {
                "E2", modules[1],  9, {1.205310e+00, 3.492821e-01},
            },
            {
                "E3", modules[1], 10, {1.373708e+00, 3.392059e-01},
            },
            {
                "E4", modules[1], 11, {1.694657e+00, 3.457768e-01},
            },
        },
        clover,
    },
    {"clover_B6",
        {
            {
                "E1", modules[1], 12, {1.082980e+00, 3.380270e-01},
            },
            {
                "E2", modules[1], 13, {8.868178e-01, 3.429586e-01},
            },
            {
                "E3", modules[1], 14, {2.499840e+00, 3.416498e-01},
            },
            {
                "E4", modules[1], 15, {4.175447e+00, 3.506034e-01},
            },
        },
        clover,
    },
    {"cebr_B",
        {
            {
                "E", modules[2],  0, {0., 1.}
            },
        },
        cebr
    },
    {"cebr_C",
        {
            {
                "E", modules[2],  1, {0., 1.}
            }
        },
        cebr
    },
    {"cebr_E",
        {
            {
                "E", modules[2],  2, {0., 1.}
            }
        },
        cebr
    },
    {"cebr_F",
        {
            {
                "E", modules[2],  3, {0., 1.}
            }
        },
        cebr
    },
    {"cebr_I",
        {
            {
                "E", modules[2],  4, {0., 1.}
            }
        },
        cebr
    },
    {"cebr_M",
        {
            {
                "E", modules[2],  5, {0., 1.}
            }
        },
        cebr
    },
    {"cebr_BB",
        {
            {
                "E", modules[2],  8, {0., 1.}
            }
        },
        cebr
    },
    {"cebr_BC",
        {
            {
                "E", modules[2],  9, {0., 1.}
            }
        },
        cebr
    },
    {"cebr_BD",
        {
            {
                "E", modules[2], 10, {0., 1.}
            }
        },
        cebr
    },
    {"cebr_BK",
        {
            {
                "E", modules[2], 11, {0., 1.}
            }
        },
        cebr
    },
    {"cebr_BL",
        {
            {
                "E", modules[2], 12, {0., 1.}
            }
        },
        cebr
    },
    {"cebr_BM",
        {
            {
                "E", modules[2], 13, {0., 1.}
            }
        },
        cebr
    },
};
