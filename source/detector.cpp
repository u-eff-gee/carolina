#include "detector.hpp"

Detector::Detector(
    const string name, const vector<Channel> channels,
    const DetectorGroup group,
    const double addback_coincidence_window = numeric_limits<double>::max())