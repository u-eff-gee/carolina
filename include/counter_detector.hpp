#pragma once

#include "detector.hpp"

struct CounterDetector final : public Detector {
    CounterDetector(const string name,
                    const vector<shared_ptr<Channel>> channels);

    void activate_branches(TTree *tree) override final;
    void create_branches(TTree *tree) override final;
    void register_branches(TTree *tree) override final;
    void reset() override final;
};