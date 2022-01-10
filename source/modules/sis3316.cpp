#include <string>

using std::to_string;

#include "sis3316.hpp"

void SIS3316::set_up_raw_branches(TTree *tree) {

    tree->SetBranchStatus("ADC1CH1MAXE1", 1);
    tree->SetBranchStatus("ADC1CH1MAXE2", 1);
    tree->SetBranchStatus("LABRL1T", 1);
    tree->SetBranchStatus("ADC1CH5MAXE1", 1);
    tree->SetBranchStatus("ADC1CH5MAXE2", 1);
    tree->SetBranchStatus("LABRL2T", 1);
    tree->SetBranchStatus("ADC1CH9MAXE1", 1);
    tree->SetBranchStatus("ADC1CH9MAXE2", 1);
    tree->SetBranchStatus("LABRL3T", 1);
    tree->SetBranchStatus("ADC1CH13MAXE1", 1);
    tree->SetBranchStatus("ADC1CH13MAXE2", 1);
    tree->SetBranchStatus("LABRL4T", 1);

    tree->SetBranchStatus("ADC3CH1MAXE1", 1);
    tree->SetBranchStatus("ADC3CH1MAXE2", 1);
    tree->SetBranchStatus("HPGEL1T", 1);
    tree->SetBranchStatus("ADC3CH5MAXE1", 1);
    tree->SetBranchStatus("ADC3CH5MAXE2", 1);
    tree->SetBranchStatus("HPGEL2T", 1);
    tree->SetBranchStatus("ADC3CH9MAXE1", 1);
    tree->SetBranchStatus("ADC3CH9MAXE2", 1);
    tree->SetBranchStatus("HPGEL3T", 1);
    tree->SetBranchStatus("ADC3CH13MAXE1", 1);
    tree->SetBranchStatus("ADC3CH13MAXE2", 1);
    tree->SetBranchStatus("HPGEL4T", 1);

    tree->SetBranchStatus("TRIGT11", 1);

    tree->SetBranchAddress("ADC1CH1MAXE1", &amplitude_e1.leaves[0]);
    tree->SetBranchAddress("ADC1CH1MAXE2", &amplitude_e2.leaves[0]);
    tree->SetBranchAddress("LABRL1T", &time.leaves[0]);
    tree->SetBranchAddress("ADC1CH5MAXE1", &amplitude_e1.leaves[1]);
    tree->SetBranchAddress("ADC1CH5MAXE2", &amplitude_e2.leaves[1]);
    tree->SetBranchAddress("LABRL2T", &time.leaves[1]);
    tree->SetBranchAddress("ADC1CH9MAXE1", &amplitude_e1.leaves[2]);
    tree->SetBranchAddress("ADC1CH9MAXE2", &amplitude_e2.leaves[2]);
    tree->SetBranchAddress("LABRL3T", &time.leaves[2]);
    tree->SetBranchAddress("ADC1CH13MAXE1", &amplitude_e1.leaves[3]);
    tree->SetBranchAddress("ADC1CH13MAXE2", &amplitude_e2.leaves[3]);
    tree->SetBranchAddress("LABRL4T", &time.leaves[3]);

    tree->SetBranchAddress("ADC3CH1MAXE1", &amplitude_e1.leaves[4]);
    tree->SetBranchAddress("ADC3CH1MAXE2", &amplitude_e2.leaves[4]);
    tree->SetBranchAddress("HPGEL1T", &time.leaves[4]);
    tree->SetBranchAddress("ADC3CH5MAXE1", &amplitude_e1.leaves[5]);
    tree->SetBranchAddress("ADC3CH5MAXE2", &amplitude_e2.leaves[5]);
    tree->SetBranchAddress("HPGEL2T", &time.leaves[5]);
    tree->SetBranchAddress("ADC3CH9MAXE1", &amplitude_e1.leaves[6]);
    tree->SetBranchAddress("ADC3CH9MAXE2", &amplitude_e2.leaves[6]);
    tree->SetBranchAddress("HPGEL3T", &time.leaves[6]);
    tree->SetBranchAddress("ADC3CH13MAXE1", &amplitude_e1.leaves[7]);
    tree->SetBranchAddress("ADC3CH13MAXE2", &amplitude_e2.leaves[7]);
    tree->SetBranchAddress("HPGEL4T", &time.leaves[7]);

    tree->SetBranchAddress("TRIGT11", &time_RF.leaves[0]);
}