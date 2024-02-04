class Solution {
private:
    vector<long long> genPrefixSum(const vector<int>& nums) {
        vector<long long> prefixSum(nums.size(), 0);
        prefixSum[0] = nums[0];

        for (int i = 1; i < nums.size(); ++i) {
            prefixSum[i] = prefixSum[i - 1] + nums[i];
        }

        return prefixSum;
    }


public:
    int findMaximumLength(vector<int>& nums) {
        vector<long long> prefixSum = genPrefixSum(nums);
        vector<int> res(nums.size(), 0);
        vector<long long> minLastSum(nums.size(), LONG_LONG_MAX);
        res[0] = 1;
        minLastSum[0] = nums[0];

        for (int i = 1; i < nums.size(); ++i) {
            // if greater than the last sum, create a new subarray
            const int& num = nums[i];
            const long long& lastSum = minLastSum[i - 1];
            if (num >= lastSum) {
                res[i] = max(res[i], res[i - 1] + 1);
                minLastSum[i] = num;
            } else if (res[i - 1] == res[i]) {
                minLastSum[i] = min(minLastSum[i], minLastSum[i - 1] + num);
            } else if (res[i - 1] > res[i]) {
                res[i] = res[i - 1];
                minLastSum[i] = minLastSum[i - 1] + num;
            }

            // create a new array from index i
            const long long& lastPrefixSum = prefixSum[i - 1];
            if (prefixSum.back() - lastPrefixSum < lastSum) { // impossible to generate a new subarray from here
                continue;
            }

            int high = (int) nums.size() - 1;
            int low = i;
            // find the minimum high where pSum[high] - pSum[i - 1] >= lastSum
            while (high > low + 1) {
                int mid = low + (high - low) / 2;
                if (prefixSum[mid] - lastPrefixSum < lastSum) {
                    low = mid;
                } else {
                    high = mid;
                }
            }

            int newNumArr = res[i - 1] + 1;
            if (newNumArr > res[high]) {
                res[high] = newNumArr;
                minLastSum[high] = prefixSum[high] - lastPrefixSum;
            } else if (newNumArr == res[high]) {
                minLastSum[high] = min(minLastSum[high], prefixSum[high] - lastPrefixSum);
            }
        }

        return res.back();
    }
};
