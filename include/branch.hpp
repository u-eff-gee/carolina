#pragma once

#include <string>

using std::string;

struct Branch{
    const string name;
    const unsigned int n_leaves;
    const unsigned int n_dependent_leaves;
    const bool keep_previous;
};