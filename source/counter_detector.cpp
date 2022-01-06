#include <memory>

using std::dynamic_pointer_cast;

#include "counter_detector.hpp"
#include "counter_detector_channel.hpp"

CounterDetector::CounterDetector(const string name,
                                 const vector<shared_ptr<Channel>> channels)
    : Detector(name, counter, channels) {}

void CounterDetector::activate_branches(TTree *tree) {
    for (size_t n_channel = 0; n_channel < channels.size(); ++n_channel) {
        tree->SetBranchStatus((name + "_" + channels[n_channel]->name).c_str(),
                              1);
    }
}

void CounterDetector::create_branches(TTree *tree) {
    for (size_t n_channel = 0; n_channel < channels.size(); ++n_channel) {
        tree->Branch(
            (name + "_" + channels[n_channel]->name).c_str(),
            &dynamic_pointer_cast<CounterDetectorChannel>(channels[n_channel])
                 ->counts);
    }
}

void CounterDetector::register_branches(TTree *tree) {
    for (size_t n_channel = 0; n_channel < channels.size(); ++n_channel) {
        tree->SetBranchAddress(
            (name + "_" + channels[n_channel]->name).c_str(),
            &dynamic_pointer_cast<CounterDetectorChannel>(channels[n_channel])
                 ->counts);
    }
}

void CounterDetector::reset() {
    for (size_t n_channel = 0; n_channel < channels.size(); ++n_channel) {
        channels[n_channel]->reset();
    }
}