#pragma once

#include "TTree.h"

struct Module {
    virtual void set_up_raw_branches(TTree *tree) = 0;
};