#include "detector.hpp"

Detector::Detector(const string name, vector<shared_ptr<Channel>> channels)
    : name(name), channels(channels){};