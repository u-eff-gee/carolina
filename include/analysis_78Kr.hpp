#pragma once

#include "analysis.hpp"
#include "coincidence_matrix.hpp"
#include "energy_sensitive_detector.hpp"
#include "event_counter.hpp"
#include "mdpp16.hpp"
#include "v830.hpp"

DetectorGroup clover{.name = "clover",
                     .energy_histogram_properties = {65536, -0.125, 16383.875},
                     .energy_raw_histogram_properties = {65536, -0.5, 65535.5},
                     .time_difference_histogram_properties = {
                         8192, -4096. * 0.125, 4096. * 0.125}};
DetectorGroup coaxial{.name = "coaxial",
                      .energy_histogram_properties = {65536, -0.125, 16383.875},
                      .energy_raw_histogram_properties = {65536, -0.5, 65535.5},
                      .time_difference_histogram_properties = {
                          8192, -4096. * 0.125, 4096. * 0.125}};
DetectorGroup nai{
    .name = "nai",
    .energy_histogram_properties = {16384, -0.5, 16383.5},
    .energy_raw_histogram_properties = {16384, -0.03125, 1023.96875},
    .time_difference_histogram_properties = {8192, -4096. * 0.125,
                                             4096. * 0.125}};
DetectorGroup fission_chamber{
    .name = "fission_chamber",
    .energy_histogram_properties = {65536, -0.125, 16383.875},
    .energy_raw_histogram_properties = {65536, -0.5, 65535.5},
    .time_difference_histogram_properties = {8192, -4096. * 0.125,
                                             4096. * 0.125}};

DetectorGroup paddle{.name = "paddle",
                     .energy_histogram_properties = {1, 0., 1.},
                     .energy_raw_histogram_properties = {1, 0., 1.},
                     .time_difference_histogram_properties = {1, 0., 1.}};

DetectorGroup pulser{.name = "pulser",
                     .energy_histogram_properties = {1, 0., 1.},
                     .energy_raw_histogram_properties = {1, 0., 1.},
                     .time_difference_histogram_properties = {1, 0., 1.}};

const double tdc_resolution =
    0.024; // in nanoseconds, tdc resolution in nanoseconds per bin

Analysis analysis(
    {
        shared_ptr<ScalerModule>(new EventCounter<30>()),
        shared_ptr<DigitizerModule>(
            new MDPP16("amplitude_cross", "channel_time_cross",
                       "module_timestamp_cross", tdc_resolution)),
        shared_ptr<DigitizerModule>(
            new MDPP16("amplitude_back", "channel_time_back",
                       "module_timestamp_back", tdc_resolution)),
        shared_ptr<DigitizerModule>(
            new MDPP16("amplitude_beam", "channel_time_beam",
                       "module_timestamp_beam", tdc_resolution)),
        shared_ptr<DigitizerModule>(
            new MDPP16("integration_long_qdc", "channel_time_qdc",
                       "module_timestamp_qdc", tdc_resolution)),
        shared_ptr<ScalerModule>(new V830(5.)),
    },
    {clover, clover, clover, clover, clover, coaxial, coaxial, clover,
     fission_chamber, fission_chamber, coaxial, nai, paddle, paddle, paddle,
     pulser},
    {shared_ptr<EnergySensitiveDetector>(new EnergySensitiveDetector(
         "clover_1",
         {{"E1", 1, 0, 0, 0,

           []([[maybe_unused]] const int n_entry, const double amplitude) {
               return amplitude;
           },

           []([[maybe_unused]] const double energy) { return 1.; },

           []([[maybe_unused]] const double time_vs_time_RF) { return true; },
           5.},
          {"E2", 1, 1, 0, 1,

           []([[maybe_unused]] const int n_entry, const double amplitude) {
               return amplitude;
           },

           []([[maybe_unused]] const double energy) { return 1.; },

           []([[maybe_unused]] const double time_vs_time_RF) { return true; },
           5.},
          {"E3", 1, 2, 0, 2,

           []([[maybe_unused]] const int n_entry, const double amplitude) {
               return amplitude;
           },

           []([[maybe_unused]] const double energy) { return 1.; },

           []([[maybe_unused]] const double time_vs_time_RF) { return true; },
           5.},
          {"E4", 1, 3, 0, 3,

           []([[maybe_unused]] const int n_entry, const double amplitude) {
               return amplitude;
           },

           []([[maybe_unused]] const double energy) { return 1.; },

           []([[maybe_unused]] const double time_vs_time_RF) { return true; },
           5.}})),
     shared_ptr<EnergySensitiveDetector>(new EnergySensitiveDetector(
         "clover_3",
         {
             {"E1", 1, 4, 0, 4,

              []([[maybe_unused]] const int n_entry, const double amplitude) {
                  return amplitude;
              },

              []([[maybe_unused]] const double energy) { return 1.; },

              []([[maybe_unused]] const double time_vs_time_RF) {
                  return true;
              },
              5.},
             {"E2", 1, 5, 0, 5,

              []([[maybe_unused]] const int n_entry, const double amplitude) {
                  return amplitude;
              },

              []([[maybe_unused]] const double energy) { return 1.; },

              []([[maybe_unused]] const double time_vs_time_RF) {
                  return true;
              },
              5.},
             {"E3", 1, 6, 0, 6,

              []([[maybe_unused]] const int n_entry, const double amplitude) {
                  return amplitude;
              },

              []([[maybe_unused]] const double energy) { return 1.; },

              []([[maybe_unused]] const double time_vs_time_RF) {
                  return true;
              },
              5.},
             {"E4", 1, 7, 0, 7,

              []([[maybe_unused]] const int n_entry, const double amplitude) {
                  return amplitude;
              },

              []([[maybe_unused]] const double energy) { return 1.; },

              []([[maybe_unused]] const double time_vs_time_RF) {
                  return true;
              },
              5.},
         })),
     shared_ptr<EnergySensitiveDetector>(new EnergySensitiveDetector(
         "clover_5",
         {
             {"E1", 1, 8, 0, 8,

              []([[maybe_unused]] const int n_entry, const double amplitude) {
                  return amplitude;
              },

              []([[maybe_unused]] const double energy) { return 1.; },

              []([[maybe_unused]] const double time_vs_time_RF) {
                  return true;
              },
              5.},
             {"E2", 1, 9, 0, 9,

              []([[maybe_unused]] const int n_entry, const double amplitude) {
                  return amplitude;
              },

              []([[maybe_unused]] const double energy) { return 1.; },

              []([[maybe_unused]] const double time_vs_time_RF) {
                  return true;
              },
              5.},
             {"E3", 1, 10, 0, 10,

              []([[maybe_unused]] const int n_entry, const double amplitude) {
                  return amplitude;
              },

              []([[maybe_unused]] const double energy) { return 1.; },

              []([[maybe_unused]] const double time_vs_time_RF) {
                  return true;
              },
              5.},
             {"E4", 1, 11, 0, 11,

              []([[maybe_unused]] const int n_entry, const double amplitude) {
                  return amplitude;
              },

              []([[maybe_unused]] const double energy) { return 1.; },

              []([[maybe_unused]] const double time_vs_time_RF) {
                  return true;
              },
              5.},
         })),
     shared_ptr<EnergySensitiveDetector>(new EnergySensitiveDetector(
         "clover_7",
         {
             {"E1", 1, 12, 0, 12,

              []([[maybe_unused]] const int n_entry, const double amplitude) {
                  return amplitude;
              },

              []([[maybe_unused]] const double energy) { return 1.; },

              []([[maybe_unused]] const double time_vs_time_RF) {
                  return true;
              },
              5.},
             {"E2", 1, 13, 0, 13,

              []([[maybe_unused]] const int n_entry, const double amplitude) {
                  return amplitude;
              },

              []([[maybe_unused]] const double energy) { return 1.; },

              []([[maybe_unused]] const double time_vs_time_RF) {
                  return true;
              },
              5.},
             {"E3", 1, 14, 0, 14,

              []([[maybe_unused]] const int n_entry, const double amplitude) {
                  return amplitude;
              },

              []([[maybe_unused]] const double energy) { return 1.; },

              []([[maybe_unused]] const double time_vs_time_RF) {
                  return true;
              },
              5.},
             {"E4", 1, 15, 0, 15,

              []([[maybe_unused]] const int n_entry, const double amplitude) {
                  return amplitude;
              },

              []([[maybe_unused]] const double energy) { return 1.; },

              []([[maybe_unused]] const double time_vs_time_RF) {
                  return true;
              },
              5.},
         })),
     shared_ptr<EnergySensitiveDetector>(new EnergySensitiveDetector(
         "clover_B1",
         {
             {"E1", 2, 0, 0, 16,

              []([[maybe_unused]] const int n_entry, const double amplitude) {
                  return amplitude;
              },

              []([[maybe_unused]] const double energy) { return 1.; },

              []([[maybe_unused]] const double time_vs_time_RF) {
                  return true;
              },
              5.},
             {"E2", 2, 1, 0, 17,

              []([[maybe_unused]] const int n_entry, const double amplitude) {
                  return amplitude;
              },

              []([[maybe_unused]] const double energy) { return 1.; },

              []([[maybe_unused]] const double time_vs_time_RF) {
                  return true;
              },
              5.},
             {"E3", 2, 2, 0, 18,

              []([[maybe_unused]] const int n_entry, const double amplitude) {
                  return amplitude;
              },

              []([[maybe_unused]] const double energy) { return 1.; },

              []([[maybe_unused]] const double time_vs_time_RF) {
                  return true;
              },
              5.},
             {"E4", 2, 3, 0, 19,

              []([[maybe_unused]] const int n_entry, const double amplitude) {
                  return amplitude;
              },

              []([[maybe_unused]] const double energy) { return 1.; },

              []([[maybe_unused]] const double time_vs_time_RF) {
                  return true;
              },
              5.},
         })),
     shared_ptr<EnergySensitiveDetector>(new EnergySensitiveDetector(
         "coaxial_B2",
         {
             {"E", 2, 4, 0, 20,

              []([[maybe_unused]] const int n_entry, const double amplitude) {
                  return amplitude;
              },

              []([[maybe_unused]] const double energy) { return 1.; },

              []([[maybe_unused]] const double time_vs_time_RF) {
                  return true;
              },
              5.},
         })),
     shared_ptr<EnergySensitiveDetector>(new EnergySensitiveDetector(
         "coaxial_B4",
         {
             {"E", 2, 8, 0, 21,

              []([[maybe_unused]] const int n_entry, const double amplitude) {
                  return amplitude;
              },

              []([[maybe_unused]] const double energy) { return 1.; },

              []([[maybe_unused]] const double time_vs_time_RF) {
                  return true;
              },
              5.},
         })),
     shared_ptr<EnergySensitiveDetector>(new EnergySensitiveDetector(
         "clover_B5",
         {
             {"E1", 2, 12, 0, 22,

              []([[maybe_unused]] const int n_entry, const double amplitude) {
                  return amplitude;
              },

              []([[maybe_unused]] const double energy) { return 1.; },

              []([[maybe_unused]] const double time_vs_time_RF) {
                  return true;
              },
              5.},
             {"E2", 2, 13, 0, 23,

              []([[maybe_unused]] const int n_entry, const double amplitude) {
                  return amplitude;
              },

              []([[maybe_unused]] const double energy) { return 1.; },

              []([[maybe_unused]] const double time_vs_time_RF) {
                  return true;
              },
              5.},
             {"E3", 2, 14, 0, 24,

              []([[maybe_unused]] const int n_entry, const double amplitude) {
                  return amplitude;
              },

              []([[maybe_unused]] const double energy) { return 1.; },

              []([[maybe_unused]] const double time_vs_time_RF) {
                  return true;
              },
              5.},
             {"E4", 2, 15, 0, 25,

              []([[maybe_unused]] const int n_entry, const double amplitude) {
                  return amplitude;
              },

              []([[maybe_unused]] const double energy) { return 1.; },

              []([[maybe_unused]] const double time_vs_time_RF) {
                  return true;
              },
              5.},
         })),
     shared_ptr<EnergySensitiveDetector>(new EnergySensitiveDetector(
         "fission_chamber_1",
         {
             {"E", 3, 12, 0, 26,

              []([[maybe_unused]] const int n_entry, const double amplitude) {
                  return amplitude;
              },

              []([[maybe_unused]] const double energy) { return 1.; },

              []([[maybe_unused]] const double time_vs_time_RF) {
                  return true;
              },
              5.},
         })),
     shared_ptr<EnergySensitiveDetector>(new EnergySensitiveDetector(
         "fission_chamber_2",
         {
             {"E", 3, 13, 0, 27,

              []([[maybe_unused]] const int n_entry, const double amplitude) {
                  return amplitude;
              },

              []([[maybe_unused]] const double energy) { return 1.; },

              []([[maybe_unused]] const double time_vs_time_RF) {
                  return true;
              },
              5.},
         })),
     shared_ptr<EnergySensitiveDetector>(new EnergySensitiveDetector(
         "zero_degree",
         {
             {"E", 3, 15, 0, 28,

              []([[maybe_unused]] const int n_entry, const double amplitude) {
                  return amplitude;
              },

              []([[maybe_unused]] const double energy) { return 1.; },

              []([[maybe_unused]] const double time_vs_time_RF) {
                  return true;
              },
              5.},
         })),
     shared_ptr<EnergySensitiveDetector>(new EnergySensitiveDetector(
         "molly",
         {
             {"E", 4, 15, 0, 29,

              []([[maybe_unused]] const int n_entry, const double amplitude) {
                  return amplitude;
              },

              []([[maybe_unused]] const double energy) { return 1.; },

              []([[maybe_unused]] const double time_vs_time_RF) {
                  return true;
              },
              5.},
         }))},
    {});