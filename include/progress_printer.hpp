#pragma once

class ProgressPrinter{

public:
    ProgressPrinter(const long ne, const double ui);

    void operator()(const long index);

private:
    char* get_time_string() const;

    const time_t start_time;
    const long n_entries;
    const double inverse_n_entries;
    const double update_increment;
    double current_percentage;
};