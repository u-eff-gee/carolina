#pragma once

#include "TTree.h"

struct Module {
    virtual void set_up_raw_branches_for_reading(TTree *tree) = 0;
    virtual void set_up_raw_branches_for_writing(TTree *tree) = 0;
};