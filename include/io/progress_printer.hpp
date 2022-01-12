#pragma once

#include <string>

using std::string;

class ProgressPrinter {

  public:
    ProgressPrinter(const long long first, const long long last,
                    const double update_increment = 0.01,
                    const string unit_singular = "event",
                    const string unit_plural = "events");

    void operator()(const long long index);

  private:
    char *get_time_string() const;

    const time_t start_time;
    const long long first, last, n_entries;
    const double inverse_n_entries, update_increment;
    double current_percentage;
};