/* 2588. Count the Number of Beautiful Subarrays */
/* Sliding window: TLE */
class Solution {
private:
    // key: the bit position starting from 0, val: total # of 1s on the position
    unordered_map<int, int> bitPosDict;
    
    void addNumToDict(int n) {
        if (n == 0) {
            return;
        }
        
        int pos = 0;
        while (n != 1) {
            if (n % 2 == 1) {
                ++bitPosDict[pos];
            }
            n >>= 1;
            ++pos;
        }
        ++bitPosDict[pos];
    }
    
    void removeNumFromDict(int n) {
        if (n == 0) {
            return;
        }
        
        int pos = 0;
        while (n != 1) {
            if (n % 2 == 1) {
                --bitPosDict[pos];
            }
            n >>= 1;
            ++pos;
        }
        --bitPosDict[pos];
    }
    
    bool isBeautiful() {
        for (const auto& pair : bitPosDict) {
            if (pair.second % 2 != 0) {
                return false;
            }
        }
        return true;
    }
    
public:
    long long beautifulSubarrays(vector<int>& nums) {
        long long numBeautifulArray = 0;
        // range [frontIt, backIt]
        for (auto frontIt = nums.begin(); frontIt != nums.end(); ++frontIt) {
            bitPosDict.clear();
            addNumToDict(*frontIt);
            if (isBeautiful()) {
                ++numBeautifulArray;
            }
            
            for (auto backIt = frontIt + 1; backIt != nums.end(); ++backIt) {
                addNumToDict(*backIt);
                if (isBeautiful()) {
                    ++numBeautifulArray;
                }
            }
        }
        
        return numBeautifulArray;
    }
};

class Solution {
public:
    long long beautifulSubarrays(vector<int>& nums) {
        unordered_map<long long, long long> resNum{{0, 1}};
        long long res = 0, val = 0;
        
        for (const int& num : nums) {
            val ^= num;
            res += resNum[val]++;
        }
        
        return res;
    }
};

int main() {
    vector<int> nums{4, 3, 1, 2, 4};
    Solution S;
    S.beautifulSubarrays(nums);
    return 0;
}

