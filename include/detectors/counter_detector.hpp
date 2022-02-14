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

#include "detector.hpp"

struct CounterDetector final : public Detector {
    CounterDetector(const string name,
                    const vector<shared_ptr<Channel>> channels,
                    const shared_ptr<CounterDetectorGroup> group);

    void set_up_calibrated_branches_for_reading(TTree *tree) override final;
    void set_up_calibrated_branches_for_writing(TTree *tree) override final;
    void reset_calibrated_leaves() override final;
};