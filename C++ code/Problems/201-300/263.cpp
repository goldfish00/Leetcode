#include <iostream>
// unordered_multiset here
#include <unordered_set>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>
#include <assert.h>
#include <set>
#include <unordered_map>
using namespace std;

/* 263. Ugly Number */
class Solution {
private:
    bool isMultipleOf2(int n) {
        return n % 2 == 0;
    }
    
    bool isMutipleOf3(int n) {
        return n % 3 == 0;
    }
    
    bool isMutipleOf5(int n) {
        return n % 5 == 0;
    }
    
public:
    bool isUgly(int n) {
        if (n == 0) {
            return false;
        }
        while (true) {
            if (n == 1) {
                return true;
            }
            if (isMultipleOf2(n)) {
                n = n / 2;
                continue;
            }
            if (isMutipleOf3(n)) {
                n = n / 3;
                continue;
            }
            if (isMutipleOf5(n)) {
                n = n / 5;
                continue;
            }
            return false;
        }
    }
};
