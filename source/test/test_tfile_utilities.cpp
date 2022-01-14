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

#include <cassert>

#include <iostream>

using std::cout;
using std::endl;

#include "tfile_utilities.hpp"

void print_blocks(vector<pair<long long, long long>> blocks) {
    cout << "{" << endl;
    for (auto block : blocks) {
        cout << "\t{ " << block.first << ", " << block.second << " }" << endl;
    }
    cout << "}" << endl;
}

int main() {
    long long first(0), last(29), block_size(10);

    vector<pair<long long, long long>> blocks =
        divide_into_blocks(first, last, block_size);
    print_blocks(blocks);

    assert(blocks.size() == 3);
    assert(blocks[0].first == 0 && blocks[0].second == 9);
    assert(blocks[1].first == 10 && blocks[1].second == 19);
    assert(blocks[2].first == 20 && blocks[2].second == 29);

    last = 28;

    blocks = divide_into_blocks(first, last, block_size);
    print_blocks(blocks);

    assert(blocks.size() == 3);
    assert(blocks[0].first == 0 && blocks[0].second == 9);
    assert(blocks[1].first == 10 && blocks[1].second == 19);
    assert(blocks[2].first == 20 && blocks[2].second == 28);

    last = 30;

    blocks = divide_into_blocks(first, last, block_size);
    print_blocks(blocks);

    assert(blocks.size() == 4);
    assert(blocks[0].first == 0 && blocks[0].second == 9);
    assert(blocks[1].first == 10 && blocks[1].second == 19);
    assert(blocks[2].first == 20 && blocks[2].second == 29);
    assert(blocks[3].first == 30 && blocks[3].second == 30);
}