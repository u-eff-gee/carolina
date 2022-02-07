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

/**
 * Calibrated using Run #12 with an 11B target.
 */

#pragma once

#include <memory>

using std::make_shared;

#include "analysis_include.hpp"

EnergySensitiveDetectorGroup clover{
    "clover",
    {65536, -0.125, 16383.875},
    {65536, -0.5, 65535.5},
    {8192, -4096 - 0.5, 4096 - 0.5},
    {8192, (-4096 - 0.5) * 0.125, (4096 - 0.5) * 0.125}};
EnergySensitiveDetectorGroup coaxial{
    "coaxial",
    {65536, -0.125, 16383.875},
    {65536, -0.5, 65535.5},
    {8192, -4096 - 0.5, 4096 - 0.5},
    {8192, (-4096 - 0.5) * 0.125, (4096 - 0.5) * 0.125}};

CounterDetectorGroup paddle{
    "paddle", {100000, -5., 1e6 - 5.}, {65536, 0, numeric_limits<int>::max()}};

CounterDetectorGroup pulser{
    "pulser", {100000, -5., 1e6 - 5.}, {65536, 0, numeric_limits<int>::max()}};

const double tdc_resolution =
    0.024; // in nanoseconds, tdc resolution in nanoseconds per bin

Analysis analysis(
    {
        make_shared<MDPP16>("clover_90.amplitude", "clover_90.channel_time",
                            "clover_90.trigger_time",
                            "clover_90.module_timestamp", tdc_resolution),
        make_shared<MDPP16>("clover_135.amplitude", "clover_135.channel_time",
                            "clover_135.trigger_time",
                            "clover_135.module_timestamp", tdc_resolution),
        make_shared<MDPP16>("zero_degree.amplitude", "zero_degree.channel_time",
                            "zero_degree.trigger_time",
                            "zero_degree.module_timestamp", tdc_resolution),
        make_shared<V830>(5.),
    },
    {make_shared<EnergySensitiveDetectorGroup>(clover),
     make_shared<EnergySensitiveDetectorGroup>(clover),
     make_shared<EnergySensitiveDetectorGroup>(clover),
     make_shared<EnergySensitiveDetectorGroup>(clover),
     make_shared<EnergySensitiveDetectorGroup>(clover),
     make_shared<EnergySensitiveDetectorGroup>(clover),
     make_shared<EnergySensitiveDetectorGroup>(clover),
     make_shared<EnergySensitiveDetectorGroup>(coaxial),
     make_shared<CounterDetectorGroup>(paddle),
     make_shared<CounterDetectorGroup>(pulser)},
    {make_shared<EnergySensitiveDetector>(
         "clover_1",
         vector<shared_ptr<Channel>>{
             //  Channel E1 of clover_1 had a problem.
             //  make_shared<EnergySensitiveDetectorChannel>("E1", 0, 0), //
             make_shared<EnergySensitiveDetectorChannel>(
                 "E2", 0, 1,
                 [](const double amplitude,
                    [[maybe_unused]] const long long n_entry) {
                     return -0.3598015485992462 +
                            0.1825041020575225 * amplitude;
                 }),
             make_shared<EnergySensitiveDetectorChannel>(
                 "E3", 0, 2,
                 [](const double amplitude,
                    [[maybe_unused]] const long long n_entry) {
                     return 1.1285102669841232 +
                            0.18543983586953972 * amplitude;
                 }),
             make_shared<EnergySensitiveDetectorChannel>(
                 "E4", 0, 3,
                 [](const double amplitude,
                    [[maybe_unused]] const long long n_entry) {
                     return 0.30119284324035167 +
                            0.1816971209069334 * amplitude;
                 }),
         }),
     make_shared<EnergySensitiveDetector>(
         "clover_3",
         vector<shared_ptr<Channel>>{
             make_shared<EnergySensitiveDetectorChannel>(
                 "E1", 0, 4,
                 [](const double amplitude,
                    [[maybe_unused]] const long long n_entry) {
                     return 1.1193743567054817 + 0.1811298496047643 * amplitude;
                 }),
             make_shared<EnergySensitiveDetectorChannel>(
                 "E2", 0, 5,
                 [](const double amplitude,
                    [[maybe_unused]] const long long n_entry) {
                     return -0.9316469006819835 +
                            0.19603241575895103 * amplitude;
                 }),
             make_shared<EnergySensitiveDetectorChannel>(
                 "E3", 0, 6,
                 [](const double amplitude,
                    [[maybe_unused]] const long long n_entry) {
                     return 0.04245603145766492 +
                            0.1984336531192391 * amplitude;
                 }),
             make_shared<EnergySensitiveDetectorChannel>(
                 "E4", 0, 7,
                 [](const double amplitude,
                    [[maybe_unused]] const long long n_entry) {
                     return -1.5916297201472274 +
                            0.18144776260947365 * amplitude;
                 }),
         }),
     make_shared<EnergySensitiveDetector>(
         "clover_5",
         vector<shared_ptr<Channel>>{
             make_shared<EnergySensitiveDetectorChannel>(
                 "E1", 0, 8,
                 [](const double amplitude,
                    [[maybe_unused]] const long long n_entry) {
                     return 1.158847500354262 + 0.18231283015185604 * amplitude;
                 }),
             make_shared<EnergySensitiveDetectorChannel>(
                 "E2", 0, 9,
                 [](const double amplitude,
                    [[maybe_unused]] const long long n_entry) {
                     return -1.0503166444472778 +
                            0.18561078921517024 * amplitude;
                 }),
             make_shared<EnergySensitiveDetectorChannel>(
                 "E3", 0, 10,
                 [](const double amplitude,
                    [[maybe_unused]] const long long n_entry) {
                     return 2.3910490221748635 +
                            0.18400403366768034 * amplitude;
                 }),
             make_shared<EnergySensitiveDetectorChannel>(
                 "E4", 0, 11,
                 [](const double amplitude,
                    [[maybe_unused]] const long long n_entry) {
                     return 1.0040420982077802 + 0.1828995415624086 * amplitude;
                 }),
         }),
     make_shared<EnergySensitiveDetector>(
         "clover_7",
         vector<shared_ptr<Channel>>{
             make_shared<EnergySensitiveDetectorChannel>(
                 "E1", 0, 12,
                 [](const double amplitude,
                    [[maybe_unused]] const long long n_entry) {
                     return 0.8793847182835113 +
                            0.18126529895812243 * amplitude;
                 }),
             make_shared<EnergySensitiveDetectorChannel>(
                 "E2", 0, 13,
                 [](const double amplitude,
                    [[maybe_unused]] const long long n_entry) {
                     return 0.34608675089924446 +
                            0.18618175187244485 * amplitude;
                 }),
             make_shared<EnergySensitiveDetectorChannel>(
                 "E3", 0, 14,
                 [](const double amplitude,
                    [[maybe_unused]] const long long n_entry) {
                     return 0.39408921500189115 +
                            0.18425441582736204 * amplitude;
                 }),
             make_shared<EnergySensitiveDetectorChannel>(
                 "E4", 0, 15,
                 [](const double amplitude,
                    [[maybe_unused]] const long long n_entry) {
                     return 0.889940645683658 + 0.1924646533458434 * amplitude;
                 }),
         }),
     make_shared<EnergySensitiveDetector>(
         "clover_B1",
         vector<shared_ptr<Channel>>{
             // Not possible to calibrate B1 with run 12, because the dynamic
             // range is limited.
             make_shared<EnergySensitiveDetectorChannel>("E1", 1, 0),
             make_shared<EnergySensitiveDetectorChannel>("E2", 1, 1),
             make_shared<EnergySensitiveDetectorChannel>("E3", 1, 2),
             make_shared<EnergySensitiveDetectorChannel>("E4", 1, 3),
         }),
     make_shared<EnergySensitiveDetector>(
         "clover_B3",
         vector<shared_ptr<Channel>>{
             make_shared<EnergySensitiveDetectorChannel>(
                 "E1", 1, 4,
                 [](const double amplitude,
                    [[maybe_unused]] const long long n_entry) {
                     return -0.9684184902043503 +
                            0.18433384267875397 * amplitude;
                 }),
             make_shared<EnergySensitiveDetectorChannel>(
                 "E2", 1, 5,
                 [](const double amplitude,
                    [[maybe_unused]] const long long n_entry) {
                     return -1.4963486454990107 +
                            0.19060749681307643 * amplitude;
                 }),
             make_shared<EnergySensitiveDetectorChannel>(
                 "E3", 1, 6,
                 [](const double amplitude,
                    [[maybe_unused]] const long long n_entry) {
                     return -1.2707497268994474 +
                            0.18402504241365275 * amplitude;
                 }),
             make_shared<EnergySensitiveDetectorChannel>(
                 "E4", 1, 7,
                 [](const double amplitude,
                    [[maybe_unused]] const long long n_entry) {
                     return -3.1981647623388842 +
                            0.18489578219536695 * amplitude;
                 }),
         }),
     make_shared<EnergySensitiveDetector>(
         "clover_B5",
         vector<shared_ptr<Channel>>{
             make_shared<EnergySensitiveDetectorChannel>(
                 "E1", 1, 8,
                 [](const double amplitude,
                    [[maybe_unused]] const long long n_entry) {
                     return -1.5782216486477774 +
                            0.18492872608801472 * amplitude;
                 }),
             make_shared<EnergySensitiveDetectorChannel>(
                 "E2", 1, 9,
                 [](const double amplitude,
                    [[maybe_unused]] const long long n_entry) {
                     return -2.659455472594448 + 0.1860033497806845 * amplitude;
                 }),
             make_shared<EnergySensitiveDetectorChannel>(
                 "E3", 1, 10,
                 [](const double amplitude,
                    [[maybe_unused]] const long long n_entry) {
                     return -0.4607715984780424 +
                            0.18232772477459938 * amplitude;
                 }),
             make_shared<EnergySensitiveDetectorChannel>(
                 "E4", 1, 11,
                 [](const double amplitude,
                    [[maybe_unused]] const long long n_entry) {
                     return -1.1101848329048816 +
                            0.18628566101500282 * amplitude;
                 }),
         }),
     make_shared<EnergySensitiveDetector>(
         "zero_degree",
         vector<shared_ptr<Channel>>{
             make_shared<EnergySensitiveDetectorChannel>("E", 2, 0),
         }),
     make_shared<CounterDetector>(
         "paddle",
         vector<shared_ptr<Channel>>{
             make_shared<CounterDetectorChannel>("mirror", 3, 12),
             make_shared<CounterDetectorChannel>("single", 3, 13),
             make_shared<CounterDetectorChannel>("compton", 3, 14)}),
     make_shared<CounterDetector>(
         "mvlc",
         vector<shared_ptr<Channel>>{
             make_shared<CounterDetectorChannel>("pulser", 3, 15)})},
    {});