using namespace std;

/* 258. Add Digits */
class Solution {
public:
    int addDigits(int num) {
        while (num > 9) {
            int nextNum = 0;
            while (num / 10 != 0) {
                nextNum += num % 10;
                num = num / 10;
            }
            num += nextNum;
        }
        
        return num;
    }
};
