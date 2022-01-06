#pragma once

#include <memory>

using std::make_shared;

#include "analysis.hpp"
#include "coincidence_matrix.hpp"
#include "counter_detector.hpp"
#include "counter_detector_channel.hpp"
#include "energy_sensitive_detector.hpp"
#include "energy_sensitive_detector_channel.hpp"
#include "event_counter.hpp"
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
        shared_ptr<ScalerModule>(new EventCounter<30>()),
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
    {clover, paddle, pulser},
    {make_shared<EnergySensitiveDetector>(
         "clover_1",
         vector<shared_ptr<Channel>>{
             make_shared<EnergySensitiveDetectorChannel>("E1", 1, 0),
             make_shared<EnergySensitiveDetectorChannel>("E2", 1, 1),
             make_shared<EnergySensitiveDetectorChannel>("E3", 1, 2),
             make_shared<EnergySensitiveDetectorChannel>("E4", 1, 3),
         }),
     make_shared<CounterDetector>(
         "paddle",
         vector<shared_ptr<Channel>>{
             make_shared<CounterDetectorChannel>("mirror", 5, 12),
             make_shared<CounterDetectorChannel>("single", 5, 13),
             make_shared<CounterDetectorChannel>("compton", 5, 14)}),
     make_shared<CounterDetector>(
         "mvlc",
         vector<shared_ptr<Channel>>{
             make_shared<CounterDetectorChannel>("pulser", 5, 15)})},
    {});