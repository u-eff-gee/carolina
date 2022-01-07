#include "coincidence_matrix.hpp"

vector<pair<size_t, size_t>> CoincidenceMatrix::get_coincidence_pairs() const {
    vector<pair<size_t, size_t>> pairs;

    if (!detectors_y.size()) {
        for (size_t n_detector_1 = 0; n_detector_1 < detectors_x.size();
             ++n_detector_1) {
            for (size_t n_detector_2 = n_detector_1 + 1;
                 n_detector_2 < detectors_x.size(); ++n_detector_2) {
                pairs.push_back(
                    {detectors_x[n_detector_1], detectors_x[n_detector_2]});
            }
        }
    } else {
        for (size_t n_detector_1 = 0; n_detector_1 < detectors_x.size();
             ++n_detector_1) {
            for (size_t n_detector_2 = 0; n_detector_2 < detectors_y.size();
                 ++n_detector_2) {
                pairs.push_back(
                    {detectors_x[n_detector_1], detectors_y[n_detector_2]});
            }
        }
    }

    return pairs;
}