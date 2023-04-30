/* 322. Coin Change */
// DP

// vector performs better than unordered map
//class Solution {
//public:
//    int coinChange(vector<int>& coins, int amount) {
//        sort(coins.begin(), coins.end());
//        while (!coins.empty() && coins.back() > amount) {
//            coins.pop_back();
//        }
//
//        vector<int> numCoins(amount + 1, -1);
//        numCoins.front() = 0;
//
//        // initialize the first coin
//        for (int possibility = coins.front(), num = 1; possibility <= amount; possibility += coins.front(), ++num) {
//            numCoins[possibility] = num;
//        }
//
//        for (int coinIndex = 1; coinIndex < coins.size(); ++coinIndex) {
//            const int& coinVal = coins[coinIndex];
//
//            numCoins[coinVal] = 1;
//            for (int target = coinVal + 1; target <= amount; ++target) {
//                if (numCoins[target - coinVal] != -1) {
//                    if (numCoins[target] == -1) {
//                        numCoins[target] = 1 + numCoins[target - coinVal];
//                    } else {
//                        numCoins[target] = min(numCoins[target], 1 + numCoins[target - coinVal]);
//                    }
//                }
//            }
//        }
//
//        return numCoins.back();
//    }
//};

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        sort(coins.begin(), coins.end());
        while (!coins.empty() && coins.back() > amount) {
            coins.pop_back();
        }
        
        // key: value of coins, value: nums coins
        unordered_map<int, int> valueNumsDict;
        
        // initialize the first coin
        for (int possibility = 0, num = 0; possibility <= amount; possibility += coins.front(), ++num) {
            valueNumsDict[possibility] = num;
        }
        
        for (int coinIndex = 1; coinIndex < coins.size(); ++coinIndex) {
            const int& coinVal = coins[coinIndex];
            valueNumsDict[coinVal] = 1;
            
            for (int target = coinVal + 1; target <= amount; ++target) {
                auto prevIt = valueNumsDict.find(target - coinVal);
                if (prevIt == valueNumsDict.end()) {
                    continue;
                }
                
                auto curIt = valueNumsDict.find(target);
                int curNum = 1 + prevIt->second;
                if (curIt == valueNumsDict.end()) {
                    valueNumsDict.insert({target, curNum});
                } else if (curIt->second > curNum) {
                    curIt->second = curNum;
                }
            }
        }
        
        auto it = valueNumsDict.find(amount);
        if (it == valueNumsDict.end()) {
            return -1;
        }
        return it->second;
    }
};

int main() {
    Solution S;
    vector<int> coins{2, 3, 100};
    cout << S.coinChange(coins, 109) << endl;
    
    return 0;
}
