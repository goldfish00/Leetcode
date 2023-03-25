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

/* 254. Factor Combinations */ /* Backtrack */
class Solution {
private:
    void findWithBacktrack(int n, vector<int>& factors, vector<vector<int>>& results) {
        if (!factors.empty()) {
            factors.push_back(n);
            results.push_back(factors);
            factors.pop_back();
        }
        
        int upperBound = sqrt(n);
        int lowerBound = factors.empty() ? 2 : factors.back();
        for (int i = lowerBound; i <= upperBound; ++i) {
            if (n % i == 0) {
                factors.push_back(i);
                findWithBacktrack(n / i, factors, results);
                factors.pop_back();
            }
        }
    }
    
public:
    vector<vector<int>> getFactors(int n) {
        vector<vector<int>> results;
        if (n < 2) {
            return results;
        }
                
        vector<int> factors;
        findWithBacktrack(n, factors, results);
        
        return results;
    }
};

int main() {
    Solution S;
    S.getFactors(32);
    
    return 0;
}
