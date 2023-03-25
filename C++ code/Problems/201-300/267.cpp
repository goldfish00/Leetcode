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


/* 267. Palindrome Permutation II */
class Solution {
private:
    bool isOdd(int num) {
        return num % 2 == 1;
    }
    
    string completePalindrome(const deque<char>& result, bool isOdd = false) {
        int strLen = (int)result.size() * 2 + (isOdd ? -1 : 0);
        string s(result.begin(), result.end());
        s.resize(strLen);
        for(auto frontIt = s.begin(), backIt = s.end() - 1; frontIt < backIt; ++frontIt, --backIt) {
            *backIt = *frontIt;
        }
        return s;
    }
    
    void findWithBacktrack(unordered_map<char, int>& charNumDict, deque<char>& result, vector<string>& results, char oddNumChar, const int halfLen) {
        if (result.size() == halfLen){ // base
            if (oddNumChar != '.') {
                result.push_back(oddNumChar);
                results.push_back(completePalindrome(result, true));
                result.pop_back();
            } else {
                results.push_back(completePalindrome(result));
            }
            return;
        }
        
        for (auto it = charNumDict.begin(); it != charNumDict.end(); ++it) {
            if (it -> second == 0) {
                continue;
            }
            
            it->second -= 2;
            result.push_back(it->first);
            findWithBacktrack(charNumDict, result, results, oddNumChar, halfLen);
            result.pop_back();
            it->second += 2;
        }
    }
    
public:
    vector<string> generatePalindromes(string s) {
        unordered_map<char, int> charNumDict;
        for (const auto& c : s) {
            ++charNumDict[c];
        }
        
        bool hasOddNum = false;
        char oddNumChar = '.';
        for (auto& pair : charNumDict) {
            if (isOdd(pair.second)) {
                if (hasOddNum || !isOdd((int)s.size())) {
                    return vector<string>();
                }

                hasOddNum = true;
                oddNumChar = pair.first;
                --pair.second;
            }
        }
        
        vector<string> results;
        deque<char> result;
        findWithBacktrack(charNumDict, result, results, oddNumChar, int(s.size() / 2));
        return results;
    }
};

int main() {
    Solution S;
    S.generatePalindromes("aabbcd");
    return 0;
}

