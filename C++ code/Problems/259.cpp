#include <vector>
#include <assert.h>
#include <set>
#include <unordered_map>
using namespace std;

/* 259. 3Sum Smaller */
/* backtrack *//* TLE */
class Solution {
private:
    void findWithBacktrack(const vector<int>& nums, int target, int startingIndex, int numLeft, int& count) {
        if (numLeft == 0) { //base
            if (target > 0) {
                ++count;
            }
            return;
        }
        if (startingIndex == nums.size()) {
            return;
        }
        
        for (int i = startingIndex; i < nums.size(); ++i) {
            if (nums[i] > 0 && nums[i] >= target) {
                return;
            }
            findWithBacktrack(nums, target - nums[i], i + 1, numLeft - 1, count);
        }
    }
    
public:
    int threeSumSmaller(vector<int>& nums, int target) {
        if (nums.size() < 3) {
            return 0;
        }
        
        sort(nums.begin(), nums.end());
        
        int count = 0;
        findWithBacktrack(nums, target, 0, 3, count);
        return count;
    }
};

int main() {
    vector<int> nums(200, 30);
    
    Solution S;
    S.threeSumSmaller(nums, 1);
    return 0;
}

