//
//  main.cpp
//  leetcode
//
//  Created by Junyi Huang on 1/23/24.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <string.h>
using namespace std;

class Solution {
public:
    int minimumTimeToInitialState(string word, int k) {
        // word.reserve(word.size() * 2 - k + 1);
        size_t originalSize = word.size();
        
        // word.push_back('@');
        // for (int i = k; i < originalSize; ++i) {
        //     word.push_back(word[i]);
        // }
        
        vector<int> prefixMatch(word.size());
        for (int i = 1; i < prefixMatch.size(); ++i) {
            int lastMatch = i;
            while (lastMatch != 0) {
                lastMatch = prefixMatch[lastMatch - 1];
                if (word[i] == word[lastMatch]) {
                    prefixMatch[i] = lastMatch + 1;
                    break;
                }
            }
            
            if (prefixMatch[i] == 1 && i % k != 0) {
                prefixMatch[i] = 0;
            }
        }
        
        return (int(originalSize) - prefixMatch.back() + k - 1) / k;
    }
};

int main(int argc, const char * argv[]) {
    Solution S;
    cout << S.minimumTimeToInitialState("baba", 3);
    
    return 0;
}
