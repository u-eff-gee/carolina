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