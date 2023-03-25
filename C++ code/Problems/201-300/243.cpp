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

/* 243. Shortest Word Distance */
class Solution {
public:
    int shortestDistance(vector<string>& wordsDict, string word1, string word2) {
        deque<int> word1Indices;
        deque<int> word2Indices;
        
        for (int i = 0; i < wordsDict.size(); ++i) {
            if (wordsDict[i] == word1) {
                word1Indices.push_back(i);
                continue;
            }
            if (wordsDict[i] == word2) {
                word2Indices.push_back(i);
            }
        }
        
        int smallestDistance = int(wordsDict.size());
        for (const auto& i : word1Indices) {
            auto it = upper_bound(word2Indices.begin(), word2Indices.end(), i);
            if (it != word2Indices.end()) {
                smallestDistance = min(abs(*it - i), smallestDistance);
            }
            if (it != word2Indices.begin()) {
                smallestDistance = min(abs(*(it - 1) - i), smallestDistance);
            }
        }
        return smallestDistance;
    }
};

int main() {
    Solution S;
    vector<string> wordsDict{"practice", "makes", "perfect", "coding", "makes"};
    S.shortestDistance(wordsDict, "makes", "practice");
    
    return 0;
}
