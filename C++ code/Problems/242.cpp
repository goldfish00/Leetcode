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

/* 242. Valid Anagram */
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.length() != t.length()) {
            return false;
        }
        
        if (s.empty() && t.empty()) {
            return true;
        }
        
        unordered_map<char, int> sWordDict; // where key is the letter and value if the time of occurrence
        for (const auto& c : s) {
            ++sWordDict[c];
        }
        
        for (const auto& c : t) {
            // if the letter does not occur in string s
            if (sWordDict.find(c) == sWordDict.end()) {
                return false;
            }
            // if the number of occurrences is consumed already
            if (sWordDict[c] == 0) {
                return false;
            }
            --sWordDict[c];
        }
        return true;
    }
};

int main() {
    return 0;
}
