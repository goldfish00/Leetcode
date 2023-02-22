#include <iostream>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>
#include <set>
// unordered_multiset here
#include <unordered_set>
#include <unordered_map>
#include <deque>
#include <set>
#include <map>
#include <algorithm>
#include <assert.h>
#include <numeric>
#include <list>
#include <stack>
#include <queue>
#include <cmath>
using namespace std;

/* 256. Paint House */
/* To save space, we can modify directlly on the costs array, if not otherwise specified that the
    info in costs array should be maintained for later use
 */
class Solution {
public:
    int minCost(vector<vector<int>>& costs) {
        // let costs[i][j] indicate the minimum cost painting all houses from 0 to i and with the i'th house
        // painted in color j
        int numColor = (int)costs[0].size();
        for (int houseIndex = 1; houseIndex < costs.size(); ++houseIndex) {
            for (int colorIndex = 0; colorIndex < numColor; ++colorIndex) {
                int minCosts = INT_MAX;
                for (int prevColorIndex = 0; prevColorIndex < numColor; ++prevColorIndex) {
                    if (prevColorIndex == colorIndex) {
                        continue;
                    }
                    minCosts = min(minCosts, costs[houseIndex - 1][prevColorIndex]);
                }
                costs[houseIndex][colorIndex] += minCosts;
            }
        }
        
        // find minimum cost
        int minCost = INT_MAX;
        for (int colorIndex = 0; colorIndex < numColor; ++colorIndex) {
            minCost = min(minCost, costs.back()[colorIndex]);
        }
        return minCost;
    }
};

int main() {
    Solution S;
    // vector<vector<int>> costs{{17,2,17}, {16,16,5}, {14,3,19}};
    vector<vector<int>> costs{{5,8,6}, {19,14,13}, {7,5,12}, {14,15,17}, {3,20,10}};
    S.minCost(costs);
    return 0;
}

