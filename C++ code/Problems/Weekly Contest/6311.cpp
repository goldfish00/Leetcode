#include <iostream>
// unordered_multiset here
#include <assert.h>
using namespace std;

/* 6311. Count Total Number of Colored Cells */
class Solution {
public:
    long long coloredCells(int n) {
        if (n == 1) {
            return 1;
        }
        
        int longestLength = 2 * n - 1;
        int subLongestLength = longestLength - 2;
        int numDuplicateRows = (subLongestLength - 1) / 2 + 1;
        return (long long)(subLongestLength + 1) * (long long)numDuplicateRows + longestLength;
    }
};

int main() {
    Solution S;
    assert(1 == S.coloredCells(1));
    assert(5 == S.coloredCells(2));
    assert(13 == S.coloredCells(3));
    assert(25 == S.coloredCells(4));
    return 0;
}
