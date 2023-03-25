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

/* 249. Group Shifted Strings */
class Solution {
private:
    int findGap(const char& c1, const char& c2) {
        int gap = (int) c1 - (int) c2;
        if (gap < 0) {
            return gap + 26;
        }
        return gap;
    }
    
    void findGroupsWithBacktrack(const vector<string>& strings, vector<vector<string>>& results, int index) {
        if (index + 1 == strings[0].size()) {
            results.push_back(strings);
            return;
        }
        if (strings.size() == 1) {
            results.push_back(strings);
            return;
        }
        
        // divide strings by the gap between string[index] and string[index] + 1
        unordered_map<int, vector<string>> dictByGap;
        for (const auto& s : strings) {
            dictByGap[findGap(s[index + 1], s[index])].push_back(s);
        }
        
        for (const auto& pair: dictByGap) {
            findGroupsWithBacktrack(pair.second, results, index + 1);
        }
    }
    
public:
    vector<vector<string>> groupStrings(vector<string>& strings) {
        vector<vector<string>> results;
        
        unordered_map<int, vector<string>> dictByLength;
        for (const auto& s : strings) {
            dictByLength[(int)s.size()].push_back(s);
        }
        
        for (const auto& pairs : dictByLength) {
            findGroupsWithBacktrack(pairs.second, results, 0);
        }
        
        return results;
    }
};

int main() {
    Solution S;
    
    return 0;
}



