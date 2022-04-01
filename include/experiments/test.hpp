/*
     This file is part of carolina.

    carolina is free software: you can redistribute it and/or modify it under
   the terms of the GNU General Public License as published by the Free Software
   Foundation, either version 3 of the License, or (at your option) any later
   version.

    carolina is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
    more details.

    You should have received a copy of the GNU General Public License along with
    carolina. If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#include <memory>

using std::make_shared;

#include "analysis_include.hpp"

Analysis analysis(
    {make_shared<MDPP16_SCP>(0x0, "amplitude", "time", "reference_time",
                             "timestamp"),
     make_shared<SIS3316>(0x1), make_shared<V830>(0x2, 5.)},
    {make_shared<EnergySensitiveDetectorGroup>(
         "single", Histogram{65536, -0.125, 16384. - 0.125},
         Histogram{65536, -0.5, 65536. - 0.5},
         Histogram{2000, -1000. - 0.5, 1000. - 0.5},
         Histogram{2000, -1000. - 0.5, 1000. - 0.5}),
     make_shared<EnergySensitiveDetectorGroup>(
         "segmented", Histogram{65536, -0.125, 16384. - 0.125},
         Histogram{65536, -0.5, 65536. - 0.5},
         Histogram{2000, -1000. - 0.5, 1000. - 0.5},
         Histogram{2000, -1000. - 0.5, 1000. - 0.5}),
     make_shared<CounterDetectorGroup>(
         "counter", Histogram{100000, -5., 1e6 - 5.},
         Histogram{65536, 0, numeric_limits<int>::max()})},
    {make_shared<EnergySensitiveDetector>(
         "sin",
         vector<EnergySensitiveDetectorChannel>{
             {"E1", 0, 0,
              calibration_function<const double, const long long>(
                  vector<double>{50., 0.1}),
              calibration_function<const double, const double>(vector<double>{
                  0., 1.}),
              Gate::gate(0., 20.)}},
         0),
     make_shared<EnergySensitiveDetector>(
         "seg",
         vector<EnergySensitiveDetectorChannel>{
             {"E1", 1, 0,
              calibration_function<const double, const long long>("60.,0.6"),
              calibration_function<const double, const double>(vector<double>{
                  0., 1.}),
              Gate::gate(0., 20.)},
             {"E2", 1, 1,
              calibration_function<const double, const long long>("70. 0.7"),
              calibration_function<const double, const double>(vector<double>{
                  0., 1.}),
              Gate::gate(0., 20.)},
             {"E3", 1, 2,
              [](const double amplitude,
                 [[maybe_unused]] const long long n_entry) {
                  return 80. + 0.8 * amplitude;
              },
              calibration_function<const double, const double>(vector<double>{
                  0., 1.}),
              Gate::gate(0., 20.)},
             {"E4", 1, 3,
              [](const double amplitude,
                 [[maybe_unused]] const long long n_entry) {
                  return 90. + 0.9 * amplitude;
              },
              calibration_function<const double, const double>(vector<double>{
                  0., 1.}),
              Gate::gate(0., 20.)}},
         1,
         vector<vector<function<bool(const double)>>>{
             {Gate::gate([](const double time_difference) {
                  return (time_difference > -2.5) && (time_difference < 2.5);
              }),
              Gate::gate(-2.5, 2.5), Gate::gate(-2.5, 2.5)},
             {Gate::gate(-2.5, 2.5), Gate::gate(-2.5, 2.5)},
             {Gate::gate(-2.5, 2.5)}}),
     make_shared<CounterDetector>("cou",
                                  vector<CounterDetectorChannel>{{"cts", 2, 0}},
                                  2),
     make_shared<EnergySensitiveDetector>(
         "seg2",
         vector<EnergySensitiveDetectorChannel>{
             {"E1", 0, 2,
              calibration_function<const double, const long long>(
                  vector<double>{33., 0.33}),
              calibration_function<const double, const double>(vector<double>{
                  0., 1.}),
              Gate::gate(0., 20.)},
             {"E2", 0, 3,
              calibration_function<const double, const long long>(
                  vector<double>{44., 0.44}),
              calibration_function<const double, const double>(vector<double>{
                  0., 1.}),
              [](const double time_vs_reference_time) {
                  return (time_vs_reference_time > 0.) &&
                         (time_vs_reference_time < 20.);
              }}},
         1,
         vector<vector<function<bool(const double)>>>{
             {Gate::gate(-2.5, 2.5)}})},
    {
        {"sin_vs_seg",
         {0},
         {1},
         {200, -5., 2000. - 5.},
         {200, -5., 2000. - 5.}},
        {"all", {0, 1, 3}, {}, {200, -5., 2000. - 5.}, {200, -5., 2000. - 5.}},
    });