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
const double max_energy_clover = 65536.;
const unsigned int n_bins_energy_cebr = 4096;
const double max_energy_cebr = 4096.;

vector<Detector> detectors{
    {"clover_1",
        {
            {
                "E1",
                branches[0].second[0], {n_bins_energy_clover, 0., max_energy_clover}, [](const double amplitude){ return amplitude; },
                branches[3].second[0], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E2",
                branches[0].second[1], {n_bins_energy_clover, 0., max_energy_clover}, [](const double amplitude){ return amplitude; },
                branches[3].second[1], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E3",
                branches[0].second[2], {n_bins_energy_clover, 0., max_energy_clover}, [](const double amplitude){ return amplitude; },
                branches[3].second[2], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E4",
                branches[0].second[3], {n_bins_energy_clover, 0., max_energy_clover}, [](const double amplitude){ return amplitude; },
                branches[3].second[3], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"clover_3",
        {
            {
                "E1",
                branches[0].second[4], {n_bins_energy_clover, 0., max_energy_clover}, [](const double amplitude){ return amplitude; },
                branches[3].second[4], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E2",
                branches[0].second[5], {n_bins_energy_clover, 0., max_energy_clover}, [](const double amplitude){ return amplitude; },
                branches[3].second[5], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E3",
                branches[0].second[6], {n_bins_energy_clover, 0., max_energy_clover}, [](const double amplitude){ return amplitude; },
                branches[3].second[6], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E4",
                branches[0].second[7], {n_bins_energy_clover, 0., max_energy_clover}, [](const double amplitude){ return amplitude; },
                branches[3].second[7], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"clover_5",
        {
            {
                "E1",
                branches[0].second[8], {n_bins_energy_clover, 0., max_energy_clover}, [](const double amplitude){ return amplitude; },
                branches[3].second[8], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E2",
                branches[0].second[9], {n_bins_energy_clover, 0., max_energy_clover}, [](const double amplitude){ return amplitude; },
                branches[3].second[9], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E3",
                branches[0].second[10], {n_bins_energy_clover, 0., max_energy_clover}, [](const double amplitude){ return amplitude; },
                branches[3].second[10], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E4",
                branches[0].second[11], {n_bins_energy_clover, 0., max_energy_clover}, [](const double amplitude){ return amplitude; },
                branches[3].second[11], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"clover_7",
        {
            {
                "E1",
                branches[0].second[12], {n_bins_energy_clover, 0., max_energy_clover}, [](const double amplitude){ return amplitude; },
                branches[3].second[12], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E2",
                branches[0].second[13], {n_bins_energy_clover, 0., max_energy_clover}, [](const double amplitude){ return amplitude; },
                branches[3].second[13], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E3",
                branches[0].second[14], {n_bins_energy_clover, 0., max_energy_clover}, [](const double amplitude){ return amplitude; },
                branches[3].second[14], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E4",
                branches[0].second[15], {n_bins_energy_clover, 0., max_energy_clover}, [](const double amplitude){ return amplitude; },
                branches[3].second[15], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"clover_B1",
        {
            {
                "E1",
                branches[1].second[0], {n_bins_energy_clover, 0., max_energy_clover}, [](const double amplitude){ return amplitude; },
                branches[4].second[0], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E2",
                branches[1].second[1], {n_bins_energy_clover, 0., max_energy_clover}, [](const double amplitude){ return amplitude; },
                branches[4].second[1], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E3",
                branches[1].second[2], {n_bins_energy_clover, 0., max_energy_clover}, [](const double amplitude){ return amplitude; },
                branches[4].second[2], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E4",
                branches[1].second[3], {n_bins_energy_clover, 0., max_energy_clover}, [](const double amplitude){ return amplitude; },
                branches[4].second[3], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"clover_B4",
        {
            {
                "E1",
                branches[1].second[4], {n_bins_energy_clover, 0., max_energy_clover}, [](const double amplitude){ return amplitude; },
                branches[4].second[4], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E2",
                branches[1].second[5], {n_bins_energy_clover, 0., max_energy_clover}, [](const double amplitude){ return amplitude; },
                branches[4].second[5], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E3",
                branches[1].second[6], {n_bins_energy_clover, 0., max_energy_clover}, [](const double amplitude){ return amplitude; },
                branches[4].second[6], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E4",
                branches[1].second[7], {n_bins_energy_clover, 0., max_energy_clover}, [](const double amplitude){ return amplitude; },
                branches[4].second[7], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"clover_B5",
        {
            {
                "E1",
                branches[1].second[8], {n_bins_energy_clover, 0., max_energy_clover}, [](const double amplitude){ return amplitude; },
                branches[4].second[8], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E2",
                branches[1].second[9], {n_bins_energy_clover, 0., max_energy_clover}, [](const double amplitude){ return amplitude; },
                branches[4].second[9], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E3",
                branches[1].second[10], {n_bins_energy_clover, 0., max_energy_clover}, [](const double amplitude){ return amplitude; },
                branches[4].second[10], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E4",
                branches[1].second[11], {n_bins_energy_clover, 0., max_energy_clover}, [](const double amplitude){ return amplitude; },
                branches[4].second[11], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"clover_B6",
        {
            {
                "E1",
                branches[1].second[12], {n_bins_energy_clover, 0., max_energy_clover}, [](const double amplitude){ return amplitude; },
                branches[4].second[12], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E2",
                branches[1].second[13], {n_bins_energy_clover, 0., max_energy_clover}, [](const double amplitude){ return amplitude; },
                branches[4].second[13], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E3",
                branches[1].second[14], {n_bins_energy_clover, 0., max_energy_clover}, [](const double amplitude){ return amplitude; },
                branches[4].second[14], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E4",
                branches[1].second[15], {n_bins_energy_clover, 0., max_energy_clover}, [](const double amplitude){ return amplitude; },
                branches[4].second[15], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"cebr_B",
        {
            {
                "E",
                branches[2].second[0], {n_bins_energy_cebr, 0., max_energy_cebr}, [](const double amplitude){ return amplitude; },
                branches[5].second[0], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"cebr_C",
        {
            {
                "E",
                branches[2].second[1], {n_bins_energy_cebr, 0., max_energy_cebr}, [](const double amplitude){ return amplitude; },
                branches[5].second[1], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"cebr_E",
        {
            {
                "E",
                branches[2].second[2], {n_bins_energy_cebr, 0., max_energy_cebr}, [](const double amplitude){ return amplitude; },
                branches[5].second[2], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"cebr_F",
        {
            {
                "E",
                branches[2].second[3], {n_bins_energy_cebr, 0., max_energy_cebr}, [](const double amplitude){ return amplitude; },
                branches[5].second[3], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"cebr_I",
        {
            {
                "E",
                branches[2].second[4], {n_bins_energy_cebr, 0., max_energy_cebr}, [](const double amplitude){ return amplitude; },
                branches[5].second[4], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"cebr_M",
        {
            {
                "E",
                branches[2].second[5], {n_bins_energy_cebr, 0., max_energy_cebr}, [](const double amplitude){ return amplitude; },
                branches[5].second[5], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"cebr_BB",
        {
            {
                "E",
                branches[2].second[8], {n_bins_energy_cebr, 0., max_energy_cebr}, [](const double amplitude){ return amplitude; },
                branches[5].second[8], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"cebr_BC",
        {
            {
                "E",
                branches[2].second[9], {n_bins_energy_cebr, 0., max_energy_cebr}, [](const double amplitude){ return amplitude; },
                branches[5].second[9], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"cebr_BD",
        {
            {
                "E",
                branches[2].second[10], {n_bins_energy_cebr, 0., max_energy_cebr}, [](const double amplitude){ return amplitude; },
                branches[5].second[10], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"cebr_BK",
        {
            {
                "E",
                branches[2].second[11], {n_bins_energy_cebr, 0., max_energy_cebr}, [](const double amplitude){ return amplitude; },
                branches[5].second[11], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"cebr_BL",
        {
            {
                "E",
                branches[2].second[12], {n_bins_energy_cebr, 0., max_energy_cebr}, [](const double amplitude){ return amplitude; },
                branches[5].second[12], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"cebr_BM",
        {
            {
                "E",
                branches[2].second[13], {n_bins_energy_cebr, 0., max_energy_cebr}, [](const double amplitude){ return amplitude; },
                branches[5].second[13], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
};
