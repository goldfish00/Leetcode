/* 319. Bulb Switcher */
/**
 * Observation:
 * 1. The first builb is always on
 * 2. The priime bulbs will be off
 * 3. Depends on the number of factors for a given index. If the number of factors is even (e.g. for primes numbers, only 1 and itself)
 *          then it is off; if the number of factors is odd, then it is on
 */

// TLE
class Solution {
public:
    int bulbSwitch(int n) {
        if (n == 0) {
            return 0;
        }
        
        vector<int> numFactorsMap(n, 1);
        for (int factor = 2; factor <= n; ++factor) {
            int multiple = factor;
            while (multiple <= n) {
                ++numFactorsMap[multiple - 1];
                multiple += factor;
            }
        }
        
        int result = 0;
        for (const int& num : numFactorsMap) {
            if (num % 2 == 1) {
                ++result;
            }
        }
        return result;
    }
};

// Just calculate the number of squares
class Solution {
public:
    int bulbSwitch(int n) {
        int result = 0;
        
        int possibleSqrt = 1;
        while (pow(possibleSqrt, 2) <= n) {
            ++result;
            ++possibleSqrt;
        }
        
        return result;
    }
};

// Or simpler
class Solution {
public:
    int bulbSwitch(int n) {
        return sqrt(n);
    }
};

