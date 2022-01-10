#include "detector.hpp"

Detector::Detector(const string name, const DetectorType type,
                   const vector<shared_ptr<Channel>> channels)
    : name(name), type(type), channels(channels){};