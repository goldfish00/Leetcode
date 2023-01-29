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

/* 245. Shortest Word Distance III */
class Solution {
private:
    int shortestDistance(const vector<string>& wordsDict, const string& word1, const string& word2) {
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
    
    int shortestDistance(const vector<string>& wordsDict, const string& word) {
        int prevIndex = -1;
        int minDistance = int(wordsDict.size());
        
        for (int i = 0; i < wordsDict.size(); ++i) {
            if (wordsDict[i] == word) {
                if (prevIndex >= 0) {
                    minDistance = min(minDistance, i - prevIndex);
                }
                prevIndex = i;
            }
        }
        return minDistance;
    }
    
public:
    int shortestWordDistance(vector<string>& wordsDict, string word1, string word2) {
        if (word2 == word1) {
            return shortestDistance(wordsDict, word1);
        }
        return shortestDistance(wordsDict, word1, word2);
    }
};

int main() {
   
    return 0;
}
