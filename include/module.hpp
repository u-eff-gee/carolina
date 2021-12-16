#pragma once

#include "TTree.h"

struct Module {
    virtual void activate_branches(TTree *tree) = 0;
    virtual void register_branches(TTree *tree) = 0;
};