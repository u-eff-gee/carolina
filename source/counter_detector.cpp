#include "counter_detector.hpp"

CounterDetector::CounterDetector(const string name,
                                 const vector<shared_ptr<Channel>> channels)
    : Detector(name, channels) {}