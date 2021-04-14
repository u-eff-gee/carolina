#pragma once

#include <string>

using std::string;

template<class T, size_t n_leaves>
struct Branch{
    Branch(string name):name(name){}
    const string name;
    T leaves[n_leaves];
};