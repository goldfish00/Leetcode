/* 307. Range Sum Query - Mutable */
/* TLE */
class NumArray {
private:
    vector<int>& numVector;
    vector<int> numSum;
    
public:
    NumArray(vector<int>& nums): numVector(nums) {
        numSum.reserve(nums.size());
        int sum = 0;
        for (const int& n : nums) {
            sum += n;
            numSum.push_back(sum);
        }
    }
    
    void update(int index, int val) {
        if (numVector[index] == val) {
            return;
        }
        
        int diff = val - numVector[index];
        for (int i = index; i < numSum.size(); ++i) {
            numSum[i] += diff;
        }
        numVector[index] = val;
    }
    
    int sumRange(int left, int right) {
        int prev = (left == 0) ? 0 : numSum[left - 1];
        return numSum[right] - prev;
    }
};

int main() {
    vector<int> nums{7,2,7,2,0};
    NumArray n(nums);
    n.update(4, 6);
    n.update(0, 2);
    n.update(0, 9);
    n.update(4, 4);
    cout << n.sumRange(0, 4);
    
    return 0;
}
