/* 313. Super Ugly Number */
class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        priority_queue<int, vector<int>, greater<int>> nextNumbers;
        nextNumbers.push(1);
        
        int lastUglyNumber = 0;
        int currentLargest = 1;
        
        while (n != 0) {
            if (lastUglyNumber !=  0) {
                for (const int& prime : primes) {
                    if (INT_MAX / prime < lastUglyNumber) {
                        continue;
                    }
                    
                    int nextNum = prime * lastUglyNumber;
                    if (nextNum > currentLargest) {
                        if (nextNumbers.size() >= primes.size() * n) {
                            continue;
                        }
                        currentLargest = nextNum;
                    }
                    
                    nextNumbers.push(nextNum);
                }
            }
            
            while (nextNumbers.top() == lastUglyNumber) {
                nextNumbers.pop();
            }
            
            lastUglyNumber = nextNumbers.top();
            nextNumbers.pop();
            --n;
        }
        
        return lastUglyNumber;
    }
};

int main() {
    vector<int> primes{2,3,5};
    Solution S;
    S.nthSuperUglyNumber(25, primes);
    
    return 0;
}
