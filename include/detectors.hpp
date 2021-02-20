#include "detector.hpp"

double amplitude_clover_90[16];
double time_clover_90[16];
double amplitude_clover_135[16];
double time_clover_135[16];

vector<Detector> detectors{
    {"clover_1",
        {
            {
                "E1",
                amplitude_clover_90[0], [](const double amplitude){ return 1.900275e-01+1.917388e-01*amplitude; },
                time_clover_90[0], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E2",
                amplitude_clover_90[1], [](const double amplitude){ return 1.545498e+00+2.211394e-01*amplitude; },
                time_clover_90[1], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E3",
                amplitude_clover_90[2], [](const double amplitude){ return 1.035867e+00+2.248673e-01*amplitude; },
                time_clover_90[2], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E4",
                amplitude_clover_90[3], [](const double amplitude){ return 5.149064e-01+2.435422e-01*amplitude; },
                time_clover_90[3], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"clover_3",
        {
            {
                "E1",
                amplitude_clover_90[4], [](const double amplitude){ return 2.536829e-01+2.099880e-01*amplitude; },
                time_clover_90[4], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E2",
                amplitude_clover_90[5], [](const double amplitude){ return 1.008303e+00+2.259096e-01*amplitude; },
                time_clover_90[5], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E3",
                amplitude_clover_90[6], [](const double amplitude){ return 1.307505e+00+2.322131e-01*amplitude; },
                time_clover_90[6], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E4",
                amplitude_clover_90[7], [](const double amplitude){ return 3.072265e+00, 2.112261e-01*amplitude; },
                time_clover_90[7], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"clover_5",
        {
            {
                "E1",
                amplitude_clover_90[8], [](const double amplitude){ return 2.581180e+00+2.261114e-01*amplitude; },
                time_clover_90[8], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E2",
                amplitude_clover_90[9], [](const double amplitude){ return 3.664919e+00+2.295588e-01*amplitude; },
                time_clover_90[9], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E3",
                amplitude_clover_90[10], [](const double amplitude){ return 6.638253e-01+2.218850e-01*amplitude; },
                time_clover_90[10], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E4",
                amplitude_clover_90[11], [](const double amplitude){ return 2.108145e+00+2.200050e-01*amplitude; },
                time_clover_90[11], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"clover_7",
        {
            {
                "E1",
                amplitude_clover_90[12], [](const double amplitude){ return 6.210141e-01+2.280010e-01*amplitude; },
                time_clover_90[12], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E2",
                amplitude_clover_90[13], [](const double amplitude){ return 2.019043e+00+2.248544e-01*amplitude; },
                time_clover_90[13], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E3",
                amplitude_clover_90[14], [](const double amplitude){ return 7.522685e-01+2.336105e-01*amplitude; },
                time_clover_90[14], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E4",
                amplitude_clover_90[15], [](const double amplitude){ return 2.149718e+00+2.288512e-01*amplitude; },
                time_clover_90[15], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"clover_B1",
        {
            {
                "E1",
                amplitude_clover_135[0], [](const double amplitude){ return 2.202665e+00+1.648858e-01*amplitude; },
                time_clover_135[0], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E2",
                amplitude_clover_135[1], [](const double amplitude){ return 1.632657e+00+1.624665e-01*amplitude; },
                time_clover_135[1], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E3",
                amplitude_clover_135[2], [](const double amplitude){ return 4.079384e+00+2.019305e-01*amplitude; },
                time_clover_135[2], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E4",
                amplitude_clover_135[3], [](const double amplitude){ return 2.574769e+00, 1.998568e-01*amplitude; },
                time_clover_135[3], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"clover_B4",
        {
            {
                "E1",
                amplitude_clover_135[4], [](const double amplitude){ return 1.904587e+00+2.258024e-01*amplitude; },
                time_clover_135[4], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E2",
                amplitude_clover_135[5], [](const double amplitude){ return -1.698854e+00+1.070244e+00*amplitude; },
                time_clover_135[5], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E3",
                amplitude_clover_135[6], [](const double amplitude){ return 3.246940e+00+2.327411e-01*amplitude; },
                time_clover_135[6], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E4",
                amplitude_clover_135[7], [](const double amplitude){ return 2.700682e+00+2.240005e-01*amplitude; },
                time_clover_135[7], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"clover_B5",
        {
            {
                "E1",
                amplitude_clover_135[8], [](const double amplitude){ return 1.252735e+00+2.275357e-01*amplitude; },
                time_clover_135[8], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E2",
                amplitude_clover_135[9], [](const double amplitude){ return 1.199525e+00+2.297999e-01*amplitude; },
                time_clover_135[9], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E3",
                amplitude_clover_135[10], [](const double amplitude){ return 2.205312e+00+2.228535e-01*amplitude; },
                time_clover_135[10], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E4",
                amplitude_clover_135[11], [](const double amplitude){ return 3.060200e+00+2.270398e-01*amplitude; },
                time_clover_135[11], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
    {"clover_B6",
        {
            {
                "E1",
                amplitude_clover_135[12], [](const double amplitude){ return 2.877948e+00+2.218650e-01*amplitude; },
                time_clover_135[12], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E2",
                amplitude_clover_135[13], [](const double amplitude){ return 1.711854e+00+2.252766e-01*amplitude; },
                time_clover_135[13], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E3",
                amplitude_clover_135[14], [](const double amplitude){ return 1.119861e+00, 2.239316e-01*amplitude; },
                time_clover_135[14], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
            {
                "E4",
                amplitude_clover_135[15], [](const double amplitude){ return 3.652745e+00, 2.303696e-01*amplitude; },
                time_clover_135[15], [](const double uncalibrated_time){ return uncalibrated_time; }
            },
        },
    },
};