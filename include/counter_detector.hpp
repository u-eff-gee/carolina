#pragma once

#include "detector.hpp"

struct CounterDetector final : public Detector {
    CounterDetector(const string name,
                    const vector<shared_ptr<Channel>> channels);

    void set_up_calibrated_branches_for_reading(TTree *tree) override final;
    void set_up_calibrated_branches_for_writing(TTree *tree) override final;
    void reset_calibrated_leaves() override final;
};