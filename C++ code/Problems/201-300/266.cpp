#include <unordered_map>
using namespace std;

/* 266. Palindrome Permutation */
class Solution {
private:
    bool isOdd(int num) {
        return num % 2 == 1;
    }
    
public:
    bool canPermutePalindrome(string s) {
        unordered_map<char, int> charNumDict;
        for (const char& c : s) {
            ++charNumDict[c];
        }
        
        bool hasOddCharNum = false;
        for (const auto& pair : charNumDict) {
            if (isOdd(pair.second)) {
                if (hasOddCharNum) {
                    return false;
                }
                hasOddCharNum = true;
                if (!isOdd((int)s.size())) {
                    return false;
                }
            }
        }
        return true;
    }
};

