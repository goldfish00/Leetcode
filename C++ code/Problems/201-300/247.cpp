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

/* 247. Strobogrammatic Number II */
class Solution {
private:
    set<char> symmetricIndividuals{'0', '1', '8'};
    map<char, char> symmetricPairs{{'6', '9'}, {'9', '6'}};
    
    char getCorrespondingChar(char c) {
        if (symmetricIndividuals.find(c) != symmetricIndividuals.end()) {
            return c;
        }
        return symmetricPairs[c];
    }
        
    size_t calculateNumOfPossibilities(int n) {
        int numPair = n / 2;
        size_t num = 1;
        for (int i = 0; i < numPair; ++i) {
            if (i == 0) {
                num *= symmetricPairs.size() + symmetricIndividuals.size() - 1; // cannot be zero at the start
            } else {
                num *= symmetricPairs.size() + symmetricIndividuals.size();
            }
        }
        
        if (n % 2) {
            num *= symmetricIndividuals.size();
        }
        return num;
    }
    
    void genResults(string &result, vector<string>& results, int n) {
        if (result.size() == (n / 2)) {
            int halfLength = n / 2;
            bool isOdd = n % 2;
            if (isOdd) {
                result.push_back('0');
            }
            
            for (int i = 0; i < halfLength; ++i) {
                char c = result[halfLength - 1 - i];
                result.push_back(getCorrespondingChar(c));
            }
            
            if (isOdd) {
                for(const auto& c : symmetricIndividuals) {
                    result[halfLength] = c;
                    results.push_back(result);
                }
            } else {
                results.push_back(result);
            }
            
            result.erase(result.begin() + halfLength, result.end());
            return;
        }
        
        for (const auto& c : symmetricIndividuals) {
            if (result.empty() && c == '0') {
                continue;
            }
            
            result.push_back(c);
            genResults(result, results, n);
            result.pop_back();
        }
        
        for (const auto& pair : symmetricPairs) {
            result.push_back(pair.first);
            genResults(result, results, n);
            result.pop_back();
        }
    }
    
public:
    vector<string> findStrobogrammatic(int n) {
        vector<string> results;
        results.reserve(calculateNumOfPossibilities(n));
        string result;
        result.reserve(n);
        genResults(result, results, n);
        
        return results;
    }
};

int main() {
    Solution S;
    S.findStrobogrammatic(2);
    return 0;
}


