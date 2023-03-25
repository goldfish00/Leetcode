#include <iostream>
// unordered_multiset here
#include <unordered_set>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>
#include <assert.h>
#include <set>
#include <unordered_map>
using namespace std;

/* 260. Single Number III */
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int res = 0;
        for (const int& num : nums) {
            res ^= num;
        }
        
        // get the first bit where x and y differs
        int diff = (res == INT_MIN) ? 1 : res & (- res);
        int x = 0, y = 0;
        for (const int& num : nums) {
            if ((num & diff) != 0) {
                x ^= num;
            } else {
                y ^= num;
            }
        }
        return vector<int>{x, y};
    }
};

int main() {
    Solution S;
    vector<int> nums{1,2,1,3,2,5};
    S.singleNumber(nums);
    
    return 0;
}
