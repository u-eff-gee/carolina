#pragma once

#include <limits>

using std::numeric_limits;

#include "coincidence_matrix.hpp"
#include "detector.hpp"
#include "detector_setup.hpp"
#include "mdpp16.hpp"

DetectorGroup clover{.name = "clover",
                     .energy_histogram_properties = {65536, -0.125, 16383.875},
                     .energy_raw_histogram_properties = {65536, -0.5, 65535.5},
                     .time_difference_histogram_properties = {
                         8192, -4096. * 0.125, 4096. * 0.125}};
const vector<DetectorGroup> detector_groups = {clover};

const double tdc_resolution =
    0.024; // in nanoseconds, tdc resolution in nanoseconds per bin

const vector<shared_ptr<Module>> modules = {
    shared_ptr<Module>(new MDPP16("amplitude_cross", "channel_time_cross",
                                  "module_timestamp_cross", tdc_resolution)),
    shared_ptr<Module>(new MDPP16("amplitude_back", "channel_time_back",
                                  "module_timestamp_back", tdc_resolution)),
};

vector<Detector> detectors{
    {
        .name = "clover_1",
        {
            {.name = "E1",
             .module = modules[0],
             .leaf = 0,
             .energy_calibration_parameters = {{numeric_limits<int>::max(),
                                                {0., 1.}}},
             .time_calibration =
                 []([[maybe_unused]] const double energy) { return 1.; },
             .time_vs_time_RF_gate =
                 []([[maybe_unused]] const double time_vs_time_RF) {
                     return true;
                 },
             .amplitude_threshold = 5.},
            {.name = "E2",
             .module = modules[0],
             .leaf = 1,
             .energy_calibration_parameters = {{numeric_limits<int>::max(),
                                                {0., 1.}}},
             .time_calibration =
                 []([[maybe_unused]] const double energy) { return 1.; },
             .time_vs_time_RF_gate =
                 []([[maybe_unused]] const double time_vs_time_RF) {
                     return true;
                 },
             .amplitude_threshold = 5.},
            {.name = "E3",
             .module = modules[0],
             .leaf = 2,
             .energy_calibration_parameters = {{numeric_limits<int>::max(),
                                                {0., 1.}}},
             .time_calibration =
                 []([[maybe_unused]] const double energy) { return 1.; },
             .time_vs_time_RF_gate =
                 []([[maybe_unused]] const double time_vs_time_RF) {
                     return true;
                 },
             .amplitude_threshold = 5.},
            {.name = "E4",
             .module = modules[0],
             .leaf = 3,
             .energy_calibration_parameters = {{numeric_limits<int>::max(),
                                                {0., 1.}}},
             .time_calibration =
                 []([[maybe_unused]] const double energy) { return 1.; },
             .time_vs_time_RF_gate =
                 []([[maybe_unused]] const double time_vs_time_RF) {
                     return true;
                 },
             .amplitude_threshold = 5.},
        },
        clover,
    },
    {
        .name = "clover_3",
        {
            {.name = "E1",
             .module = modules[0],
             .leaf = 4,
             .energy_calibration_parameters = {{numeric_limits<int>::max(),
                                                {0., 1.}}},
             .time_calibration =
                 []([[maybe_unused]] const double energy) { return 1.; },
             .time_vs_time_RF_gate =
                 []([[maybe_unused]] const double time_vs_time_RF) {
                     return true;
                 },
             .amplitude_threshold = 5.},
            {.name = "E2",
             .module = modules[0],
             .leaf = 5,
             .energy_calibration_parameters = {{numeric_limits<int>::max(),
                                                {0., 1.}}},
             .time_calibration =
                 []([[maybe_unused]] const double energy) { return 1.; },
             .time_vs_time_RF_gate =
                 []([[maybe_unused]] const double time_vs_time_RF) {
                     return true;
                 },
             .amplitude_threshold = 5.},
            {.name = "E3",
             .module = modules[0],
             .leaf = 6,
             .energy_calibration_parameters = {{numeric_limits<int>::max(),
                                                {0., 1.}}},
             .time_calibration =
                 []([[maybe_unused]] const double energy) { return 1.; },
             .time_vs_time_RF_gate =
                 []([[maybe_unused]] const double time_vs_time_RF) {
                     return true;
                 },
             .amplitude_threshold = 5.},
            {.name = "E4",
             .module = modules[0],
             .leaf = 7,
             .energy_calibration_parameters = {{numeric_limits<int>::max(),
                                                {0., 1.}}},
             .time_calibration =
                 []([[maybe_unused]] const double energy) { return 1.; },
             .time_vs_time_RF_gate =
                 []([[maybe_unused]] const double time_vs_time_RF) {
                     return true;
                 },
             .amplitude_threshold = 5.},
        },
        clover,
    },
    {
        .name = "clover_5",
        {
            {.name = "E1",
             .module = modules[0],
             .leaf = 8,
             .energy_calibration_parameters = {{numeric_limits<int>::max(),
                                                {0., 1.}}},
             .time_calibration =
                 []([[maybe_unused]] const double energy) { return 1.; },
             .time_vs_time_RF_gate =
                 []([[maybe_unused]] const double time_vs_time_RF) {
                     return true;
                 },
             .amplitude_threshold = 5.},
            {.name = "E2",
             .module = modules[0],
             .leaf = 9,
             .energy_calibration_parameters = {{numeric_limits<int>::max(),
                                                {0., 1.}}},
             .time_calibration =
                 []([[maybe_unused]] const double energy) { return 1.; },
             .time_vs_time_RF_gate =
                 []([[maybe_unused]] const double time_vs_time_RF) {
                     return true;
                 },
             .amplitude_threshold = 5.},
            {.name = "E3",
             .module = modules[0],
             .leaf = 10,
             .energy_calibration_parameters = {{numeric_limits<int>::max(),
                                                {0., 1.}}},
             .time_calibration =
                 []([[maybe_unused]] const double energy) { return 1.; },
             .time_vs_time_RF_gate =
                 []([[maybe_unused]] const double time_vs_time_RF) {
                     return true;
                 },
             .amplitude_threshold = 5.},
            {.name = "E4",
             .module = modules[0],
             .leaf = 11,
             .energy_calibration_parameters = {{numeric_limits<int>::max(),
                                                {0., 1.}}},
             .time_calibration =
                 []([[maybe_unused]] const double energy) { return 1.; },
             .time_vs_time_RF_gate =
                 []([[maybe_unused]] const double time_vs_time_RF) {
                     return true;
                 },
             .amplitude_threshold = 5.},
        },
        clover,
    },
    {
        .name = "clover_7",
        {
            {.name = "E1",
             .module = modules[0],
             .leaf = 12,
             .energy_calibration_parameters = {{numeric_limits<int>::max(),
                                                {0., 1.}}},
             .time_calibration =
                 []([[maybe_unused]] const double energy) { return 1.; },
             .time_vs_time_RF_gate =
                 []([[maybe_unused]] const double time_vs_time_RF) {
                     return true;
                 },
             .amplitude_threshold = 5.},
            {.name = "E2",
             .module = modules[0],
             .leaf = 13,
             .energy_calibration_parameters = {{numeric_limits<int>::max(),
                                                {0., 1.}}},
             .time_calibration =
                 []([[maybe_unused]] const double energy) { return 1.; },
             .time_vs_time_RF_gate =
                 []([[maybe_unused]] const double time_vs_time_RF) {
                     return true;
                 },
             .amplitude_threshold = 5.},
            {.name = "E3",
             .module = modules[0],
             .leaf = 14,
             .energy_calibration_parameters = {{numeric_limits<int>::max(),
                                                {0., 1.}}},
             .time_calibration =
                 []([[maybe_unused]] const double energy) { return 1.; },
             .time_vs_time_RF_gate =
                 []([[maybe_unused]] const double time_vs_time_RF) {
                     return true;
                 },
             .amplitude_threshold = 5.},
            {.name = "E4",
             .module = modules[0],
             .leaf = 15,
             .energy_calibration_parameters = {{numeric_limits<int>::max(),
                                                {0., 1.}}},
             .time_calibration =
                 []([[maybe_unused]] const double energy) { return 1.; },
             .time_vs_time_RF_gate =
                 []([[maybe_unused]] const double time_vs_time_RF) {
                     return true;
                 },
             .amplitude_threshold = 5.},
        },
        clover,
    },
    {
        .name = "clover_B1",
        {
            {.name = "E1",
             .module = modules[1],
             .leaf = 0,
             .energy_calibration_parameters = {{numeric_limits<int>::max(),
                                                {0., 1.}}},
             .time_calibration =
                 []([[maybe_unused]] const double energy) { return 1.; },
             .time_vs_time_RF_gate =
                 []([[maybe_unused]] const double time_vs_time_RF) {
                     return true;
                 },
             .amplitude_threshold = 5.},
            {.name = "E2",
             .module = modules[1],
             .leaf = 1,
             .energy_calibration_parameters = {{numeric_limits<int>::max(),
                                                {0., 1.}}},
             .time_calibration =
                 []([[maybe_unused]] const double energy) { return 1.; },
             .time_vs_time_RF_gate =
                 []([[maybe_unused]] const double time_vs_time_RF) {
                     return true;
                 },
             .amplitude_threshold = 5.},
            {.name = "E3",
             .module = modules[1],
             .leaf = 2,
             .energy_calibration_parameters = {{numeric_limits<int>::max(),
                                                {0., 1.}}},
             .time_calibration =
                 []([[maybe_unused]] const double energy) { return 1.; },
             .time_vs_time_RF_gate =
                 []([[maybe_unused]] const double time_vs_time_RF) {
                     return true;
                 },
             .amplitude_threshold = 5.},
            {.name = "E4",
             .module = modules[1],
             .leaf = 3,
             .energy_calibration_parameters = {{numeric_limits<int>::max(),
                                                {0., 1.}}},
             .time_calibration =
                 []([[maybe_unused]] const double energy) { return 1.; },
             .time_vs_time_RF_gate =
                 []([[maybe_unused]] const double time_vs_time_RF) {
                     return true;
                 },
             .amplitude_threshold = 5.},
        },
        clover,
    },
    {
        .name = "clover_B2",
        {
            {.name = "E1",
             .module = modules[1],
             .leaf = 4,
             .energy_calibration_parameters = {{numeric_limits<int>::max(),
                                                {0., 1.}}},
             .time_calibration =
                 []([[maybe_unused]] const double energy) { return 1.; },
             .time_vs_time_RF_gate =
                 []([[maybe_unused]] const double time_vs_time_RF) {
                     return true;
                 },
             .amplitude_threshold = 5.},
            {.name = "E2",
             .module = modules[1],
             .leaf = 5,
             .energy_calibration_parameters = {{numeric_limits<int>::max(),
                                                {0., 1.}}},
             .time_calibration =
                 []([[maybe_unused]] const double energy) { return 1.; },
             .time_vs_time_RF_gate =
                 []([[maybe_unused]] const double time_vs_time_RF) {
                     return true;
                 },
             .amplitude_threshold = 5.},
            {.name = "E3",
             .module = modules[1],
             .leaf = 6,
             .energy_calibration_parameters = {{numeric_limits<int>::max(),
                                                {0., 1.}}},
             .time_calibration =
                 []([[maybe_unused]] const double energy) { return 1.; },
             .time_vs_time_RF_gate =
                 []([[maybe_unused]] const double time_vs_time_RF) {
                     return true;
                 },
             .amplitude_threshold = 5.},
            {.name = "E4",
             .module = modules[1],
             .leaf = 7,
             .energy_calibration_parameters = {{numeric_limits<int>::max(),
                                                {0., 1.}}},
             .time_calibration =
                 []([[maybe_unused]] const double energy) { return 1.; },
             .time_vs_time_RF_gate =
                 []([[maybe_unused]] const double time_vs_time_RF) {
                     return true;
                 },
             .amplitude_threshold = 5.},
        },
        clover,
    },
    {
        .name = "clover_B4",
        {
            {.name = "E1",
             .module = modules[1],
             .leaf = 8,
             .energy_calibration_parameters = {{numeric_limits<int>::max(),
                                                {0., 1.}}},
             .time_calibration =
                 []([[maybe_unused]] const double energy) { return 1.; },
             .time_vs_time_RF_gate =
                 []([[maybe_unused]] const double time_vs_time_RF) {
                     return true;
                 },
             .amplitude_threshold = 5.},
            {.name = "E2",
             .module = modules[1],
             .leaf = 9,
             .energy_calibration_parameters = {{numeric_limits<int>::max(),
                                                {0., 1.}}},
             .time_calibration =
                 []([[maybe_unused]] const double energy) { return 1.; },
             .time_vs_time_RF_gate =
                 []([[maybe_unused]] const double time_vs_time_RF) {
                     return true;
                 },
             .amplitude_threshold = 5.},
            {.name = "E3",
             .module = modules[1],
             .leaf = 10,
             .energy_calibration_parameters = {{numeric_limits<int>::max(),
                                                {0., 1.}}},
             .time_calibration =
                 []([[maybe_unused]] const double energy) { return 1.; },
             .time_vs_time_RF_gate =
                 []([[maybe_unused]] const double time_vs_time_RF) {
                     return true;
                 },
             .amplitude_threshold = 5.},
            {.name = "E4",
             .module = modules[1],
             .leaf = 11,
             .energy_calibration_parameters = {{numeric_limits<int>::max(),
                                                {0., 1.}}},
             .time_calibration =
                 []([[maybe_unused]] const double energy) { return 1.; },
             .time_vs_time_RF_gate =
                 []([[maybe_unused]] const double time_vs_time_RF) {
                     return true;
                 },
             .amplitude_threshold = 5.},
        },
        clover,
    },
    {
        .name = "clover_B5",
        {
            {.name = "E1",
             .module = modules[1],
             .leaf = 12,
             .energy_calibration_parameters = {{numeric_limits<int>::max(),
                                                {0., 1.}}},
             .time_calibration =
                 []([[maybe_unused]] const double energy) { return 1.; },
             .time_vs_time_RF_gate =
                 []([[maybe_unused]] const double time_vs_time_RF) {
                     return true;
                 },
             .amplitude_threshold = 5.},
            {.name = "E2",
             .module = modules[1],
             .leaf = 13,
             .energy_calibration_parameters = {{numeric_limits<int>::max(),
                                                {0., 1.}}},
             .time_calibration =
                 []([[maybe_unused]] const double energy) { return 1.; },
             .time_vs_time_RF_gate =
                 []([[maybe_unused]] const double time_vs_time_RF) {
                     return true;
                 },
             .amplitude_threshold = 5.},
            {.name = "E3",
             .module = modules[1],
             .leaf = 14,
             .energy_calibration_parameters = {{numeric_limits<int>::max(),
                                                {0., 1.}}},
             .time_calibration =
                 []([[maybe_unused]] const double energy) { return 1.; },
             .time_vs_time_RF_gate =
                 []([[maybe_unused]] const double time_vs_time_RF) {
                     return true;
                 },
             .amplitude_threshold = 5.},
            {.name = "E4",
             .module = modules[1],
             .leaf = 15,
             .energy_calibration_parameters = {{numeric_limits<int>::max(),
                                                {0., 1.}}},
             .time_calibration =
                 []([[maybe_unused]] const double energy) { return 1.; },
             .time_vs_time_RF_gate =
                 []([[maybe_unused]] const double time_vs_time_RF) {
                     return true;
                 },
             .amplitude_threshold = 5.},
        },
        clover,
    },
};

const vector<CoincidenceMatrix> coincidence_matrices{};

DetectorSetup detector_setup(modules, detector_groups, detectors, coincidence_matrices);