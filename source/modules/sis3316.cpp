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

#include <limits>

using std::numeric_limits;

#include <string>

using std::to_string;

#include "sis3316.hpp"

void SIS3316::reset_raw_amplitude_leaves() {
    for (size_t n_leaf = 0; n_leaf < 8; ++n_leaf) {
        amplitude_e1.leaves[n_leaf] = numeric_limits<double>::quiet_NaN();
        amplitude_e2.leaves[n_leaf] = numeric_limits<double>::quiet_NaN();
    }
}

void SIS3316::reset_raw_time_leaves() {
    for (size_t n_leaf = 0; n_leaf < 8; ++n_leaf) {
        time.leaves[n_leaf] = numeric_limits<double>::quiet_NaN();
    }
}

void SIS3316::reset_raw_reference_time_leaves() {
    reference_time.leaves[0] = numeric_limits<double>::quiet_NaN();
}

void SIS3316::reset_raw_timestamp_leaves() {}

void SIS3316::set_up_raw_amplitude_branches_for_reading(TTree *tree) {
    tree->SetBranchStatus("ADC1CH1MAXE1", 1);
    tree->SetBranchStatus("ADC1CH1MAXE2", 1);
    tree->SetBranchStatus("ADC1CH5MAXE1", 1);
    tree->SetBranchStatus("ADC1CH5MAXE2", 1);
    tree->SetBranchStatus("ADC1CH9MAXE1", 1);
    tree->SetBranchStatus("ADC1CH9MAXE2", 1);
    tree->SetBranchStatus("ADC1CH13MAXE1", 1);
    tree->SetBranchStatus("ADC1CH13MAXE2", 1);

    tree->SetBranchStatus("ADC3CH1MAXE1", 1);
    tree->SetBranchStatus("ADC3CH1MAXE2", 1);
    tree->SetBranchStatus("ADC3CH5MAXE1", 1);
    tree->SetBranchStatus("ADC3CH5MAXE2", 1);
    tree->SetBranchStatus("ADC3CH9MAXE1", 1);
    tree->SetBranchStatus("ADC3CH9MAXE2", 1);
    tree->SetBranchStatus("ADC3CH13MAXE1", 1);
    tree->SetBranchStatus("ADC3CH13MAXE2", 1);

    tree->SetBranchAddress("ADC1CH1MAXE1", &amplitude_e1.leaves[0]);
    tree->SetBranchAddress("ADC1CH1MAXE2", &amplitude_e2.leaves[0]);
    tree->SetBranchAddress("ADC1CH5MAXE1", &amplitude_e1.leaves[1]);
    tree->SetBranchAddress("ADC1CH5MAXE2", &amplitude_e2.leaves[1]);
    tree->SetBranchAddress("ADC1CH9MAXE1", &amplitude_e1.leaves[2]);
    tree->SetBranchAddress("ADC1CH9MAXE2", &amplitude_e2.leaves[2]);
    tree->SetBranchAddress("ADC1CH13MAXE1", &amplitude_e1.leaves[3]);
    tree->SetBranchAddress("ADC1CH13MAXE2", &amplitude_e2.leaves[3]);

    tree->SetBranchAddress("ADC3CH1MAXE1", &amplitude_e1.leaves[4]);
    tree->SetBranchAddress("ADC3CH1MAXE2", &amplitude_e2.leaves[4]);
    tree->SetBranchAddress("ADC3CH5MAXE1", &amplitude_e1.leaves[5]);
    tree->SetBranchAddress("ADC3CH5MAXE2", &amplitude_e2.leaves[5]);
    tree->SetBranchAddress("ADC3CH9MAXE1", &amplitude_e1.leaves[6]);
    tree->SetBranchAddress("ADC3CH9MAXE2", &amplitude_e2.leaves[6]);
    tree->SetBranchAddress("ADC3CH13MAXE1", &amplitude_e1.leaves[7]);
    tree->SetBranchAddress("ADC3CH13MAXE2", &amplitude_e2.leaves[7]);
}

void SIS3316::set_up_raw_time_branches_for_reading(TTree *tree) {
    tree->SetBranchStatus("LABRL1T", 1);
    tree->SetBranchStatus("LABRL2T", 1);
    tree->SetBranchStatus("LABRL3T", 1);
    tree->SetBranchStatus("LABRL4T", 1);

    tree->SetBranchStatus("HPGEL1T", 1);
    tree->SetBranchStatus("HPGEL2T", 1);
    tree->SetBranchStatus("HPGEL3T", 1);
    tree->SetBranchStatus("HPGEL4T", 1);

    tree->SetBranchAddress("LABRL1T", &time.leaves[0]);
    tree->SetBranchAddress("LABRL2T", &time.leaves[1]);
    tree->SetBranchAddress("LABRL3T", &time.leaves[2]);
    tree->SetBranchAddress("LABRL4T", &time.leaves[3]);

    tree->SetBranchAddress("HPGEL1T", &time.leaves[4]);
    tree->SetBranchAddress("HPGEL2T", &time.leaves[5]);
    tree->SetBranchAddress("HPGEL3T", &time.leaves[6]);
    tree->SetBranchAddress("HPGEL4T", &time.leaves[7]);
}

void SIS3316::set_up_raw_reference_time_branches_for_reading(TTree *tree) {
    tree->SetBranchStatus("TRIGT11", 1);
    tree->SetBranchAddress("TRIGT11", &reference_time.leaves[0]);
}

void SIS3316::set_up_raw_timestamp_branches_for_reading(TTree *tree) {
    tree->SetBranchStatus("TS", 1);
    tree->SetBranchAddress("TS", &timestamp.leaves[0]);
}

void SIS3316::set_up_raw_amplitude_branches_for_writing(TTree *tree) {
    tree->Branch("ADC1CH1MAXE1", &amplitude_e1.leaves[0]);
    tree->Branch("ADC1CH1MAXE2", &amplitude_e2.leaves[0]);
    tree->Branch("ADC1CH5MAXE1", &amplitude_e1.leaves[1]);
    tree->Branch("ADC1CH5MAXE2", &amplitude_e2.leaves[1]);
    tree->Branch("ADC1CH9MAXE1", &amplitude_e1.leaves[2]);
    tree->Branch("ADC1CH9MAXE2", &amplitude_e2.leaves[2]);
    tree->Branch("ADC1CH13MAXE1", &amplitude_e1.leaves[3]);
    tree->Branch("ADC1CH13MAXE2", &amplitude_e2.leaves[3]);
    tree->Branch("ADC3CH1MAXE1", &amplitude_e1.leaves[4]);
    tree->Branch("ADC3CH1MAXE2", &amplitude_e2.leaves[4]);
    tree->Branch("ADC3CH5MAXE1", &amplitude_e1.leaves[5]);
    tree->Branch("ADC3CH5MAXE2", &amplitude_e2.leaves[5]);
    tree->Branch("ADC3CH9MAXE1", &amplitude_e1.leaves[6]);
    tree->Branch("ADC3CH9MAXE2", &amplitude_e2.leaves[6]);
    tree->Branch("ADC3CH13MAXE1", &amplitude_e1.leaves[7]);
    tree->Branch("ADC3CH13MAXE2", &amplitude_e2.leaves[7]);
}

void SIS3316::set_up_raw_time_branches_for_writing(TTree *tree) {
    tree->Branch("LABRL1T", &time.leaves[0]);
    tree->Branch("LABRL2T", &time.leaves[1]);
    tree->Branch("LABRL3T", &time.leaves[2]);
    tree->Branch("LABRL4T", &time.leaves[3]);

    tree->Branch("HPGEL1T", &time.leaves[4]);
    tree->Branch("HPGEL2T", &time.leaves[5]);
    tree->Branch("HPGEL3T", &time.leaves[6]);
    tree->Branch("HPGEL4T", &time.leaves[7]);
}

void SIS3316::set_up_raw_reference_time_branches_for_writing(TTree *tree) {
    tree->Branch("TRIGT11", &reference_time.leaves[0]);
}

void SIS3316::set_up_raw_timestamp_branches_for_writing(TTree *tree) {
    tree->Branch("TS", &timestamp.leaves[0]);
}