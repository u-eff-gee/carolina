#pragma once

#include <boost/program_options.hpp>

namespace po = boost::program_options;

class CommandLineParser {
  public:
    CommandLineParser();

    void operator()(int argc, char *argv[], int &status);
    po::variables_map get_variables_map() const { return vm; };

    po::options_description desc;

  private:
    po::positional_options_description p;
    po::variables_map vm;
};