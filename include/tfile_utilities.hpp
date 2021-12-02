#pragma once

#include <string>

using std::string;
using std::to_string;

#include "TFile.h"
#include "TKey.h"

string find_tree_in_file(const string filename, const string tree_name = "");