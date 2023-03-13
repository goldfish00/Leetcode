/* 6316. Rearrange Array to Maximize Prefix Score */
class Solution {
public:
    int maxScore(vector<int>& nums) {
        sort(nums.begin(), nums.end(), greater<int>());
        long long sum = 0;
        int numCount = 0;
        for (const int& num : nums) {
            if (sum > -num) {
                sum += num;
                ++numCount;
            } else {
                break;
            }
        }
        return numCount;
    }
};
