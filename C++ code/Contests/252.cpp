#include <iostream>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>
#include <set>
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
using namespace std;

/* 1952. Three Divisors *//*
class Solution {
private:
    vector<bool> arePrimes;
    
    // binary search
    bool isSquare(int n, int& root) {
        if (n == 1) return true;
        int left = 1;
        int right = n;
        int middle = left + (right - left) / 2;
        int square = middle * middle;
        while (square != n) {
            if (middle == right || middle == left) return false;
            if (left + 1 == right) return false;
            if (square < n) {
                left = middle;
                middle = left + (right - left) / 2;
                square = middle * middle;
            }
            else {
                right = middle;
                middle = left + (right - left) / 2;
                square = middle * middle;
            }
        }
        root = middle;
        return true;
    }
    
    bool isPrime(int n) {
        if (n < 2) return false;
        arePrimes = vector<bool>(n, true);
        arePrimes[0] = false;
        for (int i = 1; i < n; ++i) {
            if (!arePrimes[i]) continue;
            int nonPrime = 2 * (i + 1);
            while (nonPrime <= n) {
                arePrimes[nonPrime - 1] = false;
                nonPrime += i + 1;
            }
        }
        return arePrimes.back();
    }
    
public:
    bool isThree(int n) {
        int root = 0;
        if (!isSquare(n, root)) return false;
        return isPrime(root);
    }
};*/


/* 1953. Maximum Number of Weeks for Which You Can Work *//*
class Solution {
public:
    long long numberOfWeeks(vector<int>& milestones) {
        if (milestones.size() == 1) return 1;
        
    }
};*/

/* 1954. Minimum Garden Perimeter to Collect Enough Apples */
class Solution {
private:
    long long getIncrement(long long length) {
        return (1 + length) * length / 2;
    }
    
public:
    long long minimumPerimeter(long long neededApples) {
        long long incrementX = neededApples >> 3;
        if (neededApples % 8 != 0){
            ++incrementX;
        }
        long long higher = incrementX;
        if (getIncrement(higher) == incrementX) return 8 * higher;
        
        long long lower = 0;
        long long middle = lower + 1 + (higher - lower) / 2;
        while (true) {
            long long increment = getIncrement(middle);
            if (increment < incrementX) {
                lower = middle;
                middle = lower + (higher - lower) / 2;
                continue;
            }
            if (increment == incrementX) return 8 * middle;
            // check the left neighbor
            increment -= middle;
            if (increment < incrementX) return 8 * middle;
            else if (increment == incrementX) return 8 * (middle - 1);
            else {
                higher = middle - 1;
                middle = lower + (higher - lower) / 2;
            }
        }
    }
};


int main(){
    Solution s;
    cout << s.minimumPerimeter(13);
}
