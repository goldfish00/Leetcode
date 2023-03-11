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

/* 268. Missing Number */
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int upperBound = (int) nums.size();
        int sum = upperBound * (upperBound + 1) / 2;
        for (const int& num : nums) {
            sum -= num;
        }
        return sum;
    }
};
