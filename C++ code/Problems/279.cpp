#include <iostream>
// unordered_multiset here
#include <unordered_set>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>
#include <assert.h>
#include <set>
#include <deque>
#include <unordered_map>
#include <queue>
using namespace std;

/* 279. Perfect Squares */
/* DP */
class Solution {
public:
    int numSquares(int n) {
        vector<int> numSquare(n + 1, 1);

        for (int i = 2; i <= n; ++i) {
            double closestRoot = sqrt(i);
            if (floor(closestRoot) == closestRoot) {
                continue;
            }

            numSquare[i] = i;
            for (int subVal = 1; subVal <= closestRoot; ++subVal) {
                numSquare[i] = min(numSquare[i], numSquare[i - subVal * subVal] + 1);
            }
        }
        return numSquare.back();
    }
};
