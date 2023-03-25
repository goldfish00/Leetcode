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

/* 246. Strobogrammatic Number */
class Solution {
private:
    bool isSymmetric(int num) {
        return num == 1 || num == 8 || num == 0;
    }
    
    bool isSymmetric(int a, int b) {
        if (a > b) {
            swap(a, b);
        }
        
        if (isSymmetric(a)) {
            return b == a;
        }
        
        if (a == 6) {
            return b == 9;
        }
        
        return false;
    }
    
    bool isSymmetric(char a, char b) {
        return isSymmetric(a - '0', b - '0');
    }
    
    bool isSymmetric(char c) {
        return isSymmetric(c - '0');
    }
    
public:
    bool isStrobogrammatic(string num) {
        for (auto startIt = num.begin(), endIt = num.end() - 1; ; ++startIt, --endIt) {
            if (startIt == endIt) {
                return isSymmetric(*startIt);
            }
            if (!isSymmetric(*startIt, *endIt)) {
                return false;
            }
            if (startIt + 1 == endIt) {
                return true;
            }
        }
        return true;
    }
};

int main() {
    Solution S;
    S.isStrobogrammatic("69");
    return 0;
}

