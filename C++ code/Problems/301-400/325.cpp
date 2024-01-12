/* 325. Maximum Size Subarray Sum Equals k */
// DP
// TLE
//class Solution {
//public:
//    int maxSubArrayLen(vector<int>& nums, int k) {
//        // key: sum, val: max len
//        unordered_map<int, int> hasEleLenDict;
//        int res = 0;
//
//        for (const int& num : nums) {
//            unordered_map<int, int> updatedHasEleLenDict;
//            for (const auto& pair : hasEleLenDict) {
//                updatedHasEleLenDict.insert({pair.first + num, pair.second + 1});
//            }
//            swap(hasEleLenDict, updatedHasEleLenDict);
//            if (hasEleLenDict.find(num) == hasEleLenDict.end()) {
//                hasEleLenDict[num] = 1;
//            }
//
//            auto it = hasEleLenDict.find(k);
//            if (it != hasEleLenDict.end()) {
//                res = max(res, it->second);
//            }
//        }
//
//        return res;
//    }
//};

class Solution {
public:
    int maxSubArrayLen(vector<int>& nums, int k) {
        long long prefixSum = 0;
        int longestSubArrayLen = 0;
        unordered_map<long long, int> sumIndexDict{{0, -1}};
        
        int index = 0;
        for (const int& num : nums) {
            prefixSum += num;
            
            auto it = sumIndexDict.find(prefixSum - k);
            if (it != sumIndexDict.end()) {
                longestSubArrayLen = max(longestSubArrayLen, index - it->second);
            }
            
            if (sumIndexDict.find(prefixSum) == sumIndexDict.end()) {
                sumIndexDict[prefixSum] = index;
            }
            
            ++index;
        }
        
        return longestSubArrayLen;
    }
};

int main() {
    vector<int> nums{1,-1,5,-2,3};
    
    Solution S;
    S.maxSubArrayLen(nums, 3);
    return 0;
}
