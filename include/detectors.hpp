#include <utility>

using std::pair;

#include "detector.hpp"

vector<pair<string, double*>> branches{
	{"amplitude_clover_90", new double[16]},
	{"amplitude_clover_135", new double[16]},
	{"integration_long", new double[16]},
	{"time_clover_90", new double[16]},
	{"time_clover_135", new double[16]},
	{"channel_time", new double[16]},
};

const unsigned int n_bins_energy_clover = 65536;
const double min_energy_clover = 0.5;
const double max_energy_clover = 10000.5;
const unsigned int n_bins_energy_cebr = 4096;
const double min_energy_cebr = 0.5;
const double max_energy_cebr = 10000.5;

vector<Detector> detectors{
    {"clover_1",
        {
            {
                "E1",
                branches[0].second[0], {n_bins_energy_clover, min_energy_clover, max_energy_clover}, [](const double amplitude){ return 8.195428e-01+1.917486e-01*amplitude; },
                branches[3].second[0], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E2",
                branches[0].second[1], {n_bins_energy_clover, min_energy_clover, max_energy_clover}, [](const double amplitude){ return 4.511201e+00+2.209234e-01*amplitude; },
                branches[3].second[1], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E3",
                branches[0].second[2], {n_bins_energy_clover, min_energy_clover, max_energy_clover}, [](const double amplitude){ return 4.082621e+00+2.246197e-01*amplitude; },
                branches[3].second[2], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E4",
                branches[0].second[3], {n_bins_energy_clover, min_energy_clover, max_energy_clover}, [](const double amplitude){ return 3.356518e+00+2.433405e-01*amplitude; },
                branches[3].second[3], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"clover_3",
        {
            {
                "E1",
                branches[0].second[4], {n_bins_energy_clover, min_energy_clover, max_energy_clover}, [](const double amplitude){ return 2.616710e+00+2.098547e-01*amplitude; },
                branches[3].second[4], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E2",
                branches[0].second[5], {n_bins_energy_clover, min_energy_clover, max_energy_clover}, [](const double amplitude){ return 2.581603e+00+2.257879e-01*amplitude; },
                branches[3].second[5], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E3",
                branches[0].second[6], {n_bins_energy_clover, min_energy_clover, max_energy_clover}, [](const double amplitude){ return 3.241107e+00+2.320975e-01*amplitude; },
                branches[3].second[6], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E4",
                branches[0].second[7], {n_bins_energy_clover, min_energy_clover, max_energy_clover}, [](const double amplitude){ return 3.239621e+00+2.112736e-01*amplitude; },
                branches[3].second[7], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"clover_5",
        {
            {
                "E1",
                branches[0].second[8], {n_bins_energy_clover, min_energy_clover, max_energy_clover}, [](const double amplitude){ return 3.819561e+00+2.260582e-01*amplitude; },
                branches[3].second[8], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E2",
                branches[0].second[9], {n_bins_energy_clover, min_energy_clover, max_energy_clover}, [](const double amplitude){ return 4.040720e+00+2.296258e-01*amplitude; },
                branches[3].second[9], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E3",
                branches[0].second[10], {n_bins_energy_clover, min_energy_clover, max_energy_clover}, [](const double amplitude){ return 2.864699e+00+2.217378e-01*amplitude; },
                branches[3].second[10], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E4",
                branches[0].second[11], {n_bins_energy_clover, min_energy_clover, max_energy_clover}, [](const double amplitude){ return 3.711482e+00+2.199104e-01*amplitude; },
                branches[3].second[11], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"clover_7",
        {
            {
                "E1",
                branches[0].second[12], {n_bins_energy_clover, min_energy_clover, max_energy_clover}, [](const double amplitude){ return 3.234694e+00+2.278309e-01*amplitude; },
                branches[3].second[12], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E2",
                branches[0].second[13], {n_bins_energy_clover, min_energy_clover, max_energy_clover}, [](const double amplitude){ return 3.483455e+00+2.243242e-01*amplitude; },
                branches[3].second[13], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E3",
                branches[0].second[14], {n_bins_energy_clover, min_energy_clover, max_energy_clover}, [](const double amplitude){ return 3.412767e+00+2.334142e-01*amplitude; },
                branches[3].second[14], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E4",
                branches[0].second[15], {n_bins_energy_clover, min_energy_clover, max_energy_clover}, [](const double amplitude){ return 3.972959e+00+2.287037e-01*amplitude; },
                branches[3].second[15], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"clover_B1",
        {
            {
                "E1",
                branches[1].second[0], {n_bins_energy_clover, min_energy_clover, max_energy_clover}, [](const double amplitude){ return 2.287037e-01+1.648521e-01*amplitude; },
                branches[4].second[0], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E2",
                branches[1].second[1], {n_bins_energy_clover, min_energy_clover, max_energy_clover}, [](const double amplitude){ return 2.297035e+00+1.629191e-01*amplitude; },
                branches[4].second[1], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E3",
                branches[1].second[2], {n_bins_energy_clover, min_energy_clover, max_energy_clover}, [](const double amplitude){ return 4.445848e+00+2.020955e-01*amplitude; },
                branches[4].second[2], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E4",
                branches[1].second[3], {n_bins_energy_clover, min_energy_clover, max_energy_clover}, [](const double amplitude){ return 3.211260e+00+1.998439e-01*amplitude; },
                branches[4].second[3], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"clover_B4",
        {
            {
                "E1",
                branches[1].second[4], {n_bins_energy_clover, min_energy_clover, max_energy_clover}, [](const double amplitude){ return 2.719021e+00+2.258225e-01*amplitude; },
                branches[4].second[4], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E2",
                branches[1].second[5], {n_bins_energy_clover, min_energy_clover, max_energy_clover}, [](const double amplitude){ return -4.628883e-01+1.068767e+00*amplitude; },
                branches[4].second[5], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E3",
                branches[1].second[6], {n_bins_energy_clover, min_energy_clover, max_energy_clover}, [](const double amplitude){ return 4.020829e+00+2.328474e-01*amplitude; },
                branches[4].second[6], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E4",
                branches[1].second[7], {n_bins_energy_clover, min_energy_clover, max_energy_clover}, [](const double amplitude){ return 3.418135e+00+2.239762e-01*amplitude; },
                branches[4].second[7], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"clover_B5",
        {
            {
                "E1",
                branches[1].second[8], {n_bins_energy_clover, min_energy_clover, max_energy_clover}, [](const double amplitude){ return 2.822781e+00+2.274120e-01*amplitude; },
                branches[4].second[8], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E2",
                branches[1].second[9], {n_bins_energy_clover, min_energy_clover, max_energy_clover}, [](const double amplitude){ return 2.945326e+00+2.296954e-01*amplitude; },
                branches[4].second[9], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E3",
                branches[1].second[10], {n_bins_energy_clover, min_energy_clover, max_energy_clover}, [](const double amplitude){ return 2.915758e+00+2.228363e-01*amplitude; },
                branches[4].second[10], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E4",
                branches[1].second[11], {n_bins_energy_clover, min_energy_clover, max_energy_clover}, [](const double amplitude){ return 3.046281e+00+2.270979e-01*amplitude; },
                branches[4].second[11], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"clover_B6",
        {
            {
                "E1",
                branches[1].second[12], {n_bins_energy_clover, min_energy_clover, max_energy_clover}, [](const double amplitude){ return 3.278164e+00+2.218043e-01*amplitude; },
                branches[4].second[12], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E2",
                branches[1].second[13], {n_bins_energy_clover, min_energy_clover, max_energy_clover}, [](const double amplitude){ return 3.039850e+00+2.251673e-01*amplitude; },
                branches[4].second[13], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E3",
                branches[1].second[14], {n_bins_energy_clover, min_energy_clover, max_energy_clover}, [](const double amplitude){ return 3.206270e+00+2.237607e-01*amplitude; },
                branches[4].second[14], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E4",
                branches[1].second[15], {n_bins_energy_clover, min_energy_clover, max_energy_clover}, [](const double amplitude){ return 4.102127e+00+2.303245e-01*amplitude; },
                branches[4].second[15], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"cebr_B",
        {
            {
                "E",
                branches[2].second[0], {n_bins_energy_cebr, min_energy_cebr, max_energy_cebr}, [](const double amplitude){ return 7.970388e+00+2.910997e+00*amplitude; },
                branches[5].second[0], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"cebr_C",
        {
            {
                "E",
                branches[2].second[1], {n_bins_energy_cebr, min_energy_cebr, max_energy_cebr}, [](const double amplitude){ return 1.806513e+01+2.864689e+00*amplitude; },
                branches[5].second[1], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"cebr_E",
        {
            {
                "E",
                branches[2].second[2], {n_bins_energy_cebr, min_energy_cebr, max_energy_cebr}, [](const double amplitude){ return 1.431229e+01+3.107743e+00*amplitude; },
                branches[5].second[2], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"cebr_F",
        {
            {
                "E",
                branches[2].second[3], {n_bins_energy_cebr, min_energy_cebr, max_energy_cebr}, [](const double amplitude){ return 1.299113e+01+2.958187e+00*amplitude; },
                branches[5].second[3], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"cebr_I",
        {
            {
                "E",
                branches[2].second[4], {n_bins_energy_cebr, min_energy_cebr, max_energy_cebr}, [](const double amplitude){ return 1.706866e+01+2.685529e+00*amplitude; },
                branches[5].second[4], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"cebr_M",
        {
            {
                "E",
                branches[2].second[5], {n_bins_energy_cebr, min_energy_cebr, max_energy_cebr}, [](const double amplitude){ return 1.681380e+01+2.793310e+00*amplitude; },
                branches[5].second[5], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"cebr_BB",
        {
            {
                "E",
                branches[2].second[8], {n_bins_energy_cebr, min_energy_cebr, max_energy_cebr}, [](const double amplitude){ return 2.462225e+01+2.892358e+00*amplitude; },
                branches[5].second[8], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"cebr_BC",
        {
            {
                "E",
                branches[2].second[9], {n_bins_energy_cebr, min_energy_cebr, max_energy_cebr}, [](const double amplitude){ return 7.986022e+00+3.196667e+00*amplitude; },
                branches[5].second[9], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"cebr_BD",
        {
            {
                "E",
                branches[2].second[10], {n_bins_energy_cebr, min_energy_cebr, max_energy_cebr}, [](const double amplitude){ return 1.622308e+01+3.001918e+00*amplitude; },
                branches[5].second[10], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"cebr_BK",
        {
            {
                "E",
                branches[2].second[11], {n_bins_energy_cebr, min_energy_cebr, max_energy_cebr}, [](const double amplitude){ return 2.331539e+01+2.609833e+00*amplitude; },
                branches[5].second[11], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"cebr_BL",
        {
            {
                "E",
                branches[2].second[12], {n_bins_energy_cebr, min_energy_cebr, max_energy_cebr}, [](const double amplitude){ return 1.418627e+01+3.085454e+00*amplitude; },
                branches[5].second[12], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"cebr_BM",
        {
            {
                "E",
                branches[2].second[13], {n_bins_energy_cebr, min_energy_cebr, max_energy_cebr}, [](const double amplitude){ return 1.626798e+01+2.907252e+00*amplitude; },
                branches[5].second[13], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
};
