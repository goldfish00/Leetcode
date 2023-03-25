#include <iostream>
// unordered_multiset here
#include <unordered_set>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>
#include <assert.h>
#include <set>
#include <deque>
#include <unordered_map>
using namespace std;

/* 265. Paint House II */
class Solution {
public:
    int minCostII(vector<vector<int>>& costs) {
        size_t numHouses = costs.size();
        size_t numColors = costs[0].size();
        for (int i = 1; i < numHouses; ++i) {
            int prevHouse = i - 1;
            // find the two indices of the smallest costs <index, cost>
            deque<pair<int, int>> twoSmallestCost;
            // given that k >= 2
            twoSmallestCost.push_front({0, costs[prevHouse][0]});
            if (costs[prevHouse][1] > costs[prevHouse][0]) {
                twoSmallestCost.push_back({1, costs[prevHouse][1]});
            } else {
                twoSmallestCost.push_front({1, costs[prevHouse][1]});
            }
            
            for (int j = 2; j < numColors; ++j) {
                int cost = costs[prevHouse][j];
                if (cost < twoSmallestCost.front().second) {
                    twoSmallestCost.pop_back();
                    twoSmallestCost.push_front({j, costs[prevHouse][j]});
                } else if (cost < twoSmallestCost.back().second) {
                    twoSmallestCost.pop_back();
                    twoSmallestCost.push_back({j, costs[prevHouse][j]});
                }
            }
            
            // update the current house painting cost
            for (int j = 0; j < numColors; ++j) {
                if (j == twoSmallestCost.front().first) {
                    costs[i][j] += twoSmallestCost.back().second;
                    continue;
                }
                costs[i][j] += twoSmallestCost.front().second;
            }
        }
        
        return *min_element(costs.back().begin(), costs.back().end());
    }
};

int main() {
//    vector<vector<int>> costs{
//        {3,20,7,7,16,8,7,12,11,19,1},
//        {10,14,3,3,9,13,4,12,14,13,1}, // 4
//        {10,1,14,11,1,16,2,7,16,7,19}, // 5
//        {13,20,17,15,3,13,8,10,7,8,9}, // 8
//        {4,14,18,15,11,9,19,3,15,12,15}, // 11
//        {14,12,16,19,2,12,13,3,11,10,9},// 13
//        {18,12,10,16,19,9,18,4,14,2,4} //15
//    };
    vector<vector<int>> costs{
        {10,15,12,14,18,5}, // 5
        {5,12,18,13,15,8}, // 10
        {4,7,4,2,10,18}, // 12
        {20,9,9,19,20,5}, // 17
        {10,15,10,15,16,20}, // 27
        {9,6,11,10,12,11}, // 33
        {7,10,6,12,20,8}, // 39
        {3,4,4,18,10,2} // 41
    };
    Solution S;
    S.minCostII(costs);
    return 0;
}
