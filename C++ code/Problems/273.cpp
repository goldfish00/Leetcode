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
#include <queue>
using namespace std;

/* 273. Integer to English Words */
class Solution {
public:
    string numberToWords(int num) {
        if (num == 0) return "Zero";
        
        const unordered_map<int, string> numWord{
            {1, "One"},
            {2, "Two"},
            {3, "Three"},
            {4, "Four"},
            {5, "Five"},
            {6, "Six"},
            {7, "Seven"},
            {8, "Eight"},
            {9, "Nine"},
            {10, "Ten"},
            {11, "Eleven"},
            {12, "Twelve"},
            {13, "Thirteen"},
            {14, "Fourteen"},
            {15, "Fifteen"},
            {16, "Sixteen"},
            {17, "Seventeen"},
            {18, "Eighteen"},
            {19, "Nineteen"},
            {20, "Twenty"},
            {30, "Thirty"},
            {40, "Forty"},
            {50, "Fifty"},
            {60, "Sixty"},
            {70, "Seventy"},
            {80, "Eighty"},
            {90, "Ninety"}
        };
        
        const unordered_map<int, string> base10Names{
            {3, "Thousand"},
            {6, "Million"},
            {9, "Billion"}
        };
        
        deque<int> numByThreeDigits;
        while (num != 0) {
            numByThreeDigits.push_front(num % 1000);
            num = num / 1000;
        }
        
        string result;
        while (!numByThreeDigits.empty()) {
            int currentNum = numByThreeDigits.front();
            numByThreeDigits.pop_front();
            if (currentNum == 0) {
                continue;
            }
            
            if (!result.empty()) {
                result.push_back(' ');
            }
            
            if (currentNum > 99) {
                int hundredDigit = currentNum / 100;
                result += numWord.find(hundredDigit)->second;
                result += " Hundred";
                currentNum = currentNum % 100;
                if (currentNum != 0) {
                    result.push_back(' ');
                }
            }
            
            if (currentNum != 0) {
                if (currentNum <= 20) {
                    result += numWord.find(currentNum)->second;
                } else {
                    int lastDigit = currentNum % 10;
                    result += numWord.find(currentNum - lastDigit)->second;
                    if (currentNum % 10 != 0) {
                        result.push_back(' ');
                        result += numWord.find(lastDigit)->second;
                    }
                }
            }
            
            if (!numByThreeDigits.empty()) {
                result.push_back(' ');
                result += base10Names.find((int)(3 * numByThreeDigits.size()))->second;
            }
        }
        
        return result;
    }
};

int main() {
    Solution S;
    cout << S.numberToWords(1000) << endl;
    return 0;
}
