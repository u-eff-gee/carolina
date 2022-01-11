#pragma once

#include <string>

using std::string;

#include <boost/program_options.hpp>

#include "TChain.h"

namespace po = boost::program_options;

class CommandLineParser {
  public:
    CommandLineParser();

    void operator()(int argc, char *argv[], int &status);
    po::variables_map get_variables_map() const { return vm; };
    TChain *set_up_tree(long long &first, long long &last,
                        const bool log_file = false) const;

    po::options_description desc;

  private:
    po::positional_options_description p;
    po::variables_map vm;
};