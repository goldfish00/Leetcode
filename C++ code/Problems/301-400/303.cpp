/* 303. Range Sum Query - Immutable */
class NumArray {
private:
    // sum[i] is the sum of 0 to i
    vector<long long> sum;
    
public:
    NumArray(vector<int>& nums) {
        sum.reserve(nums.size());
        long long curSum = 0;
        
        for (const int& n : nums) {
            curSum += n;
            sum.push_back(curSum);
        }
    }
    
    
    int sumRange(int left, int right) {
        if (left == 0) {
            return (int)sum[right];
        }
        return (int)(sum[right] - sum[left - 1]);
    }
};
