#include <iostream>
// unordered_multiset here
#include <unordered_set>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>
using namespace std;

/* 6312. Split With Minimum Sum */
class Solution {
public:
    int splitNum(int num) {
        string s = to_string(num);
        vector<char> chars(s.begin(), s.end());
        sort(chars.begin(), chars.end());
        
        string num1;
        string num2;
        for (int i = 0; i < chars.size(); ++i) {
            if (i % 2 == 1) {
                num1.push_back(chars[i]);
            } else {
                num2.push_back(chars[i]);
            }
        }
        
        return stoi(num1) + stoi(num2);
    }
};

int main() {
    Solution S;
    S.splitNum(876);
    return 0;
}
