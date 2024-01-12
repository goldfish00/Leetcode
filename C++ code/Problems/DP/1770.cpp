class Solution {
public:
    int maximumScore(vector<int>& nums, vector<int>& multipliers) {
        vector<int> frontMeme(nums.size(), INT_MIN);
        vector<int> backMeme(nums.size(), INT_MIN);
        // initialize the first row
        frontMeme.front() = nums.front() * multipliers.front();
        backMeme.back() = nums.back() * multipliers.front();
        
        for (int i = 1; i < multipliers.size(); ++i) {
            vector<int> nextFrontMeme(nums.size(), INT_MIN);
            vector<int> nextBackMeme(nums.size(), INT_MIN);
            
            for (int j = 0; j < nums.size(); ++j) {
                if (frontMeme[j] != INT_MIN) { // can reach
                    nextFrontMeme[j + 1] = max(nextFrontMeme[j + 1], frontMeme[j] + (nums[j + 1] * multipliers[i]));
                    
                    int correspondingBackInd = int(nums.size()) - (i - j);
                    nextBackMeme[correspondingBackInd] = max(nextBackMeme[correspondingBackInd], frontMeme[j] + (nums[correspondingBackInd] * multipliers[i]));
                }
                
                if (backMeme[j] != INT_MIN) {
                    nextBackMeme[j - 1] = max(nextBackMeme[j - 1], backMeme[j] + (nums[j - 1] * multipliers[i]));
                    
                    int correspondingFrontInd = i - (int(nums.size()) - j);
                    nextFrontMeme[correspondingFrontInd] = max(nextFrontMeme[correspondingFrontInd], backMeme[j] + (nums[correspondingFrontInd] * multipliers[i]));
                }
            }
            
            frontMeme = nextFrontMeme;
            backMeme = nextBackMeme;
        }
        
        return max(*max_element(frontMeme.begin(), frontMeme.end()), *max_element(backMeme.begin(), backMeme.end()));
    }
};

int main() {
    vector<int> nums{-5,-3,-3,-2,7,1};
    vector<int> multiplier{-10,-5,3,4,6};
    Solution S;
    cout << S.maximumScore(nums, multiplier) << endl;

    return 0;
}

