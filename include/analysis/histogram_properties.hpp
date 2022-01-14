#pragma once

struct Histogram {
    Histogram(const unsigned int n_bins, const double lower_edge_of_first_bin,
              const double upper_edge_of_last_bin)
        : n_bins(n_bins), lower_edge_of_first_bin(lower_edge_of_first_bin),
          upper_edge_of_last_bin(upper_edge_of_last_bin) {}

    const unsigned int n_bins;
    const double lower_edge_of_first_bin;
    const double upper_edge_of_last_bin;
};