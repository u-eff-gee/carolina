#include <string>

using std::string;

struct DetectorGroup{
    const string name;
    const HistogramProperties energy_histogram_properties;
    const HistogramProperties time_difference_histogram_properties;
};