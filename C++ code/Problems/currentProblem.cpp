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

/* 248. Strobogrammatic Number III */
class Solution {
private:
    const set<char> symmetricIndividuals{'0', '1', '8'};
    const map<char, char> symmetricPairs{{'6', '9'}, {'9', '6'}};
    
    bool isSymmetricIndividual(const char& c) {
        return symmetricIndividuals.find(c) != symmetricIndividuals.end();
    }
    
    bool isSymmetricPairMember(const char& c) {
        return symmetricPairs.find(c) != symmetricPairs.end() || symmetricIndividuals.find(c) != symmetricIndividuals.end();
    }
    
    char getCorrespondingChar(char c) {
        if (symmetricIndividuals.find(c) != symmetricIndividuals.end()) {
            return c;
        }
        return symmetricPairs.find(c)->second;
    }
    
    int symmetricPairNumGreaterThan(const char& c) {
        if (c == '9') {
            return 0;
        }
        if (c > '5') {
            return 1 + symmetricIndividualNumGreaterThan(c);
        }
        return 2 + symmetricIndividualNumGreaterThan(c);
    }
    
    int symmetricIndividualNumGreaterThan(const char &c) {
        if (c > '7') {
            return 0;
        }
        if (c > '0') {
            return 1;
        }
        return 2;
    }
    
    int calculateNumOfPossibilities(int stringLen, bool isZeroIncluede = false) {
        if (stringLen == 0) return 1;
        
        int numPair = stringLen / 2;
        int num = 1;
        for (int i = 0; i < numPair; ++i) {
            if (i == 0) {
                num *= symmetricPairs.size() + symmetricIndividuals.size() - (isZeroIncluede ? 0 : 1); // cannot be zero at the start
            } else {
                num *= symmetricPairs.size() + symmetricIndividuals.size();
            }
        }
        
        if (stringLen % 2) {
            num *= symmetricIndividuals.size();
        }
        return num;
    }
    
    bool isSymmetric(const string& low) {
        for (int i = 0; i < low.size() / 2; ++i) {
            if (!isSymmetricPairMember(low[i])) {
                return false;
            }
            if (low[low.size() - 1 - i] != getCorrespondingChar(low[i])) {
                return false;
            }
        }
        
        if (low.size() % 2) {
            if (!isSymmetricIndividual(low[low.size() / 2])) {
                return false;
            }
        }
        return true;
    }
    
    // return the number of string numbers no less than low and have the same digit with low
    int calculateNumOfPossibilitiesWithLow(const string& low, bool& hasDigitsSmallerThanLow, int prefix = 0) {
        int stringLen = int(low.length());
        bool isOddLen = stringLen % 2;
        char currentChar = low[prefix];
        char correspondingChar = low[low.size() - 1 - prefix];
        char symmetricDigit = getCorrespondingChar(currentChar);
        
        if (prefix == stringLen / 2) {
            if (isOddLen) {
                return ((!hasDigitsSmallerThanLow && isSymmetricIndividual(currentChar)) ? 1 : 0) + symmetricIndividualNumGreaterThan(currentChar);
            }
            return hasDigitsSmallerThanLow ? 0 : 1;
        }
        
        if (isSymmetricPairMember(currentChar)) {
            if(symmetricDigit < correspondingChar) {
                hasDigitsSmallerThanLow = true;
            } else if (symmetricDigit > correspondingChar) {
                hasDigitsSmallerThanLow = false;
            }
            
            return calculateNumOfPossibilitiesWithLow(low, hasDigitsSmallerThanLow, prefix + 1) + symmetricPairNumGreaterThan(currentChar) * calculateNumOfPossibilities(int(low.size()) - 2 * (prefix + 1), true);
        } else {
            return symmetricPairNumGreaterThan(currentChar) * calculateNumOfPossibilities(int(low.size()) - 2 * (prefix + 1), true);
        }
    }
    
public:
    int strobogrammaticInRange(string low, string high) {
        if (low == high) {
            return isSymmetric(low) ? 1 : 0;
        }
        
        size_t lowStringLen = low.size();
        size_t highStringLen = high.size();
        bool hasDigitsSmallerThanLow = false;
        int numWithLow = calculateNumOfPossibilitiesWithLow(low, hasDigitsSmallerThanLow);
        hasDigitsSmallerThanLow = false;
        int numWithHigh = calculateNumOfPossibilitiesWithLow(high, hasDigitsSmallerThanLow);
        
        if (lowStringLen == highStringLen) {
            return numWithLow - numWithHigh + (isSymmetric(high) ? 1 : 0);
        }
        
        numWithLow += calculateNumOfPossibilities(int(high.size())) - numWithHigh + (isSymmetric(high) ? 1 : 0);
        for (int i = int(low.size()) + 1; i < high.size(); ++i) {
            numWithLow += calculateNumOfPossibilities(i);
        }
        
        return numWithLow;
    }
};

int main() {
    Solution S;
//    S.strobogrammaticInRange("11", "69");
//    S.strobogrammaticInRange("100", "999");
//    S.strobogrammaticInRange("0", "9");
    S.strobogrammaticInRange("100", "1100");
    return 0;
}

