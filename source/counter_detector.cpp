#include <memory>

using std::dynamic_pointer_cast;

#include "counter_detector.hpp"
#include "counter_detector_channel.hpp"

CounterDetector::CounterDetector(const string name,
                                 const vector<shared_ptr<Channel>> channels)
    : Detector(name, counter, channels) {}

void CounterDetector::set_up_calibrated_branches_for_reading(TTree *tree) {
    for (size_t n_channel = 0; n_channel < channels.size(); ++n_channel) {
        tree->SetBranchStatus((name + "_" + channels[n_channel]->name).c_str(),
                              1);
        tree->SetBranchAddress(
            (name + "_" + channels[n_channel]->name).c_str(),
            &dynamic_pointer_cast<CounterDetectorChannel>(channels[n_channel])
                 ->counts);
    }
}

void CounterDetector::set_up_calibrated_branches_for_writing(TTree *tree) {
    for (size_t n_channel = 0; n_channel < channels.size(); ++n_channel) {
        tree->Branch(
            (name + "_" + channels[n_channel]->name).c_str(),
            &dynamic_pointer_cast<CounterDetectorChannel>(channels[n_channel])
                 ->counts);
    }
}

void CounterDetector::reset_calibrated_leaves() {
    for (size_t n_channel = 0; n_channel < channels.size(); ++n_channel) {
        channels[n_channel]->reset_calibrated_leaves();
    }
}