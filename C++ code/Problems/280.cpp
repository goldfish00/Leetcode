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

/* 280. Wiggle Sort */
class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        if (nums.size() < 2) {
            return;
        }
        
        if (nums[0] > nums[1]) {
            swap(nums[0], nums[1]);
        }
        
        for (auto it = nums.begin() + 1; it != nums.end();) {
            if (*it < *(it - 1)) {
                swap(*it, *(it - 1));
            }
            
            ++it;
            if (it == nums.end()) {
                return;
            }
            if (*(it - 1) < *it) {
                swap(*(it - 1), *it);
            }
            ++it;
        }
    }
};

