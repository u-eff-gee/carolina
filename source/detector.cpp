#include "detector.hpp"

Detector::Detector(const string name, const vector<Channel> channels,
                   const DetectorGroup group,
                   const double addback_coincidence_window)
    : name(name), channels(channels), group(group),
      addback_coincidence_window(addback_coincidence_window) {
    added_back = vector<bool>(channels.size(), false);
    addback_energies = vector<double>(channels.size(), 0.);
    addback_times = vector<double>(channels.size(), 0.);
}

void Detector::addback() {
    for (size_t n_c = 0; n_c < channels.size(); ++n_c) {
        added_back[n_c] = false;
        addback_energies[n_c] = 0.;
    }

    size_t maximum_energy_deposition_index = 0;

    for (size_t n_c_0 = 0; n_c_0 < channels.size(); ++n_c_0) {
        if (channels[n_c_0].energy_calibrated != 0. && !added_back[n_c_0]) {
            addback_energies[n_c_0] = channels[n_c_0].energy_calibrated;
            addback_times[n_c_0] = channels[n_c_0].time_calibrated;
            maximum_energy_deposition_index = n_c_0;

            for (size_t n_c_1 = n_c_0 + 1; n_c_1 < channels.size(); ++n_c_1) {
                if (channels[n_c_1].energy_calibrated > 0.) {
                    if (!added_back[n_c_1] &&
                        fabs(channels[n_c_1].time_calibrated -
                             channels[n_c_0].time_calibrated) <
                            addback_coincidence_window) {
                        addback_energies[n_c_0] +=
                            channels[n_c_1].energy_calibrated;
                        added_back[n_c_1] = true;
                        if (channels[n_c_1].energy_calibrated >
                            channels[n_c_0].energy_calibrated) {
                            maximum_energy_deposition_index = n_c_1;
                        }
                    }
                } else {
                    added_back[n_c_1] = true;
                }
            }
            addback_times[n_c_0] =
                channels[maximum_energy_deposition_index].time_calibrated;
        }
        added_back[n_c_0] = true;
    }
}