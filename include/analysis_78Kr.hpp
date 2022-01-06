#pragma once

#include <memory>

using std::make_shared;

#include "analysis.hpp"
#include "coincidence_matrix.hpp"
#include "counter_detector.hpp"
#include "counter_detector_channel.hpp"
#include "energy_sensitive_detector.hpp"
#include "energy_sensitive_detector_channel.hpp"
#include "mdpp16.hpp"
#include "v830.hpp"

DetectorGroup clover{.name = "clover",
                     .histogram_properties = {65536, -0.125, 16383.875},
                     .raw_histogram_properties = {65536, -0.5, 65535.5}};
DetectorGroup coaxial{.name = "coaxial",
                      .histogram_properties = {65536, -0.125, 16383.875},
                      .raw_histogram_properties = {65536, -0.5, 65535.5}};
DetectorGroup nai{.name = "nai",
                  .histogram_properties = {16384, -0.5, 16383.5},
                  .raw_histogram_properties = {16384, -0.03125, 1023.96875}};
DetectorGroup fission_chamber{
    .name = "fission_chamber",
    .histogram_properties = {65536, -0.125, 16383.875},
    .raw_histogram_properties = {65536, -0.5, 65535.5}};

DetectorGroup paddle{
    .name = "paddle",
    .histogram_properties = {1, 0., 1.},
    .raw_histogram_properties = {65536, 0, numeric_limits<int>::max()}};

DetectorGroup pulser{
    .name = "pulser",
    .histogram_properties = {1, 0., 1.},
    .raw_histogram_properties = {65536, 0, numeric_limits<int>::max()}};

const double tdc_resolution =
    0.024; // in nanoseconds, tdc resolution in nanoseconds per bin

Analysis analysis(
    {
        make_shared<MDPP16>("amplitude_cross", "channel_time_cross",
                            "module_timestamp_cross", tdc_resolution),
        make_shared<MDPP16>("amplitude_back", "channel_time_back",
                            "module_timestamp_back", tdc_resolution),
        make_shared<MDPP16>("amplitude_beam", "channel_time_beam",
                            "module_timestamp_beam", tdc_resolution),
        make_shared<MDPP16>("integration_long_qdc", "channel_time_qdc",
                            "module_timestamp_qdc", tdc_resolution),
        make_shared<V830>(5.),
    },
    {clover, clover, clover, clover, clover, coaxial, coaxial, clover,
     fission_chamber, coaxial, paddle, pulser},
    {make_shared<EnergySensitiveDetector>(
         "clover_1",
         vector<shared_ptr<Channel>>{
             make_shared<EnergySensitiveDetectorChannel>("E1", 0, 0),
             make_shared<EnergySensitiveDetectorChannel>("E2", 0, 1),
             make_shared<EnergySensitiveDetectorChannel>("E3", 0, 2),
             make_shared<EnergySensitiveDetectorChannel>("E4", 0, 3),
         }),
     make_shared<EnergySensitiveDetector>(
         "clover_3",
         vector<shared_ptr<Channel>>{
             make_shared<EnergySensitiveDetectorChannel>("E1", 0, 4),
             make_shared<EnergySensitiveDetectorChannel>("E2", 0, 5),
             make_shared<EnergySensitiveDetectorChannel>("E3", 0, 6),
             make_shared<EnergySensitiveDetectorChannel>("E4", 0, 7),
         }),
     make_shared<EnergySensitiveDetector>(
         "clover_5",
         vector<shared_ptr<Channel>>{
             make_shared<EnergySensitiveDetectorChannel>("E1", 0, 8),
             make_shared<EnergySensitiveDetectorChannel>("E2", 0, 9),
             make_shared<EnergySensitiveDetectorChannel>("E3", 0, 10),
             make_shared<EnergySensitiveDetectorChannel>("E4", 0, 11),
         }),
     make_shared<EnergySensitiveDetector>(
         "clover_7",
         vector<shared_ptr<Channel>>{
             make_shared<EnergySensitiveDetectorChannel>("E1", 0, 12),
             make_shared<EnergySensitiveDetectorChannel>("E2", 0, 13),
             make_shared<EnergySensitiveDetectorChannel>("E3", 0, 14),
             make_shared<EnergySensitiveDetectorChannel>("E4", 0, 15),
         }),
     make_shared<EnergySensitiveDetector>(
         "clover_B1",
         vector<shared_ptr<Channel>>{
             make_shared<EnergySensitiveDetectorChannel>("E1", 1, 0),
             make_shared<EnergySensitiveDetectorChannel>("E2", 1, 1),
             make_shared<EnergySensitiveDetectorChannel>("E3", 1, 2),
             make_shared<EnergySensitiveDetectorChannel>("E4", 1, 3),
         }),
     make_shared<EnergySensitiveDetector>(
         "coaxial_B2",
         vector<shared_ptr<Channel>>{
             make_shared<EnergySensitiveDetectorChannel>("E1", 1, 4),
         }),
     make_shared<EnergySensitiveDetector>(
         "coaxial_B4",
         vector<shared_ptr<Channel>>{
             make_shared<EnergySensitiveDetectorChannel>("E1", 1, 8),
         }),
     make_shared<EnergySensitiveDetector>(
         "clover_B5",
         vector<shared_ptr<Channel>>{
             make_shared<EnergySensitiveDetectorChannel>("E1", 1, 12),
             make_shared<EnergySensitiveDetectorChannel>("E2", 1, 13),
             make_shared<EnergySensitiveDetectorChannel>("E3", 1, 14),
             make_shared<EnergySensitiveDetectorChannel>("E4", 1, 15),
         }),
     make_shared<EnergySensitiveDetector>(
         "fission_chamber",
         vector<shared_ptr<Channel>>{
             make_shared<EnergySensitiveDetectorChannel>("E1", 2, 12),
             make_shared<EnergySensitiveDetectorChannel>("E2", 2, 13),
         }),
     make_shared<EnergySensitiveDetector>(
         "zero_degree",
         vector<shared_ptr<Channel>>{
             make_shared<EnergySensitiveDetectorChannel>("E", 2, 15),
         }),
     make_shared<CounterDetector>(
         "paddle",
         vector<shared_ptr<Channel>>{
             make_shared<CounterDetectorChannel>("mirror", 4, 12),
             make_shared<CounterDetectorChannel>("single", 4, 13),
             make_shared<CounterDetectorChannel>("compton", 4, 14)}),
     make_shared<CounterDetector>(
         "mvlc",
         vector<shared_ptr<Channel>>{
             make_shared<CounterDetectorChannel>("pulser", 4, 15)})},
    {});