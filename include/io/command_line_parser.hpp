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