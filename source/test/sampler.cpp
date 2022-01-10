#include <iostream>

using std::cout;
using std::endl;

#include <memory>

using std::dynamic_pointer_cast;

#include "TFile.h"
#include "TTree.h"

#include "sampler.hpp"

int main() {
    TFile *output_file = new TFile("output.root", "RECREATE");
    TTree *tree = new TTree("test", "test");

    analysis.set_up_raw_branches_for_writing(tree);

    for (size_t n_detector = 0; n_detector < analysis.detectors.size();
         ++n_detector) {
        if (analysis.detectors[n_detector]->type == energy_sensitive) {
            for (size_t n_channel = 0;
                 n_channel < analysis.detectors[n_detector]->channels.size();
                 ++n_channel) {
                analysis.set_amplitude(n_detector, n_channel, 1.);
            }
        }
    }

    tree->Fill();

    tree->Write();
    output_file->Close();
}