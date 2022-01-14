#pragma once

#include <memory>

using std::make_shared;

#include "analysis_include.hpp"

EnergySensitiveDetectorGroup single{"single",
                                    {65536, -0.125, 16384. - 0.125},
                                    {65536, -0.5, 65536. - 0.5},
                                    {2000, -1000. - 0.5, 1000. - 0.5},
                                    {2000, -1000. - 0.5, 1000. - 0.5}};
EnergySensitiveDetectorGroup segmented{
    "segmented",
    {65536, -0.125, 16384. - 0.125},
    {65536, -0.5 * pow(2, 8), (65536. * -0.5) * pow(2, 8)},
    {2000, -1000. - 0.5, 1000. - 0.5},
    {2000, -1000. - 0.5, 1000. - 0.5}};
CounterDetectorGroup scaler{
    "counter", {100000, -5., 1e6 - 5.}, {65536, 0, numeric_limits<int>::max()}};

Analysis analysis(
    {make_shared<MDPP16>("amplitude", "time", "timestamp", 0.024),
     make_shared<SIS3316>(0.125), make_shared<V830>(5.)},
    {make_shared<EnergySensitiveDetectorGroup>(single),
     make_shared<EnergySensitiveDetectorGroup>(segmented),
     make_shared<CounterDetectorGroup>(scaler)},
    {make_shared<EnergySensitiveDetector>(
         "sin",
         vector<shared_ptr<Channel>>{
             make_shared<EnergySensitiveDetectorChannel>("E1", 0, 0)}),
     make_shared<EnergySensitiveDetector>(
         "seg",
         vector<shared_ptr<Channel>>{
             make_shared<EnergySensitiveDetectorChannel>("E1", 1, 0),
             make_shared<EnergySensitiveDetectorChannel>("E2", 1, 1),
             make_shared<EnergySensitiveDetectorChannel>("E3", 1, 2),
             make_shared<EnergySensitiveDetectorChannel>("E4", 1, 3)}),
     make_shared<CounterDetector>(
         "cou",
         vector<shared_ptr<Channel>>{
             make_shared<CounterDetectorChannel>("cts", 2, 0)})},
    {{"sin_vs_seg", {0}, {1}, {200, -5., 2000. - 5.}, {200, -5., 2000. - 5.}}});