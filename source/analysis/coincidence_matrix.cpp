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