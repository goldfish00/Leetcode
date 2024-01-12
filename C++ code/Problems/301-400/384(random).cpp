/* 384. Shuffle an Array */
class Solution {
private:
    // Seed with a real random value, if available
    random_device r;
    default_random_engine e1;
    uniform_int_distribution<int> uniform_dist;
    
    const vector<int>& originalNums;
    vector<int> shuffledNums;
    bool hasShuffled;

public:
    Solution(vector<int>& nums): originalNums(nums), shuffledNums(nums) {
        e1 = default_random_engine(r());
        uniform_dist = uniform_int_distribution<int>(0, int(nums.size()) - 1);
        hasShuffled = false;
    }
    
    vector<int> reset() {
        if (!hasShuffled) {
            return shuffledNums;
        }
        
        shuffledNums = vector<int>(originalNums);
        return shuffledNums;
    }
    
    vector<int> shuffle() {
        hasShuffled = true;
        
        for (int i = 0; i < shuffledNums.size(); ++i) {
            int toSwapInd = uniform_dist(e1);
            swap(shuffledNums[i], shuffledNums[toSwapInd]);
        }
        
        return shuffledNums;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * vector<int> param_1 = obj->reset();
 * vector<int> param_2 = obj->shuffle();
 */
