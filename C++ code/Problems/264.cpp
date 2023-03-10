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

/* 264. Ugly Number II */
struct UglyNumberInfo {
public:
    int multiple;
    int uglyNumber;
    int referenceIndex;
};

// for pq, if less, the greatest will be on the top
class UglyNumberInfoGreater {
public:
    bool operator()(const UglyNumberInfo& leftInfo, const UglyNumberInfo& rightInfo) {
        return leftInfo.uglyNumber > rightInfo.uglyNumber;
    }
};

class Solution {
private:
    void update(const vector<int>& uglyNumbers, UglyNumberInfo& info) {
        ++info.referenceIndex;
        info.uglyNumber = info.multiple * uglyNumbers[info.referenceIndex];
    }
        
public:
    int nthUglyNumber(int n) {
        vector<int> uglyNumbers{1};
        priority_queue<UglyNumberInfo, vector<UglyNumberInfo>, UglyNumberInfoGreater> pq;
        pq.push(UglyNumberInfo{2, 2, 0});
        pq.push(UglyNumberInfo{3, 3, 0});
        pq.push(UglyNumberInfo{5, 5, 0});

        while (uglyNumbers.size() < n) {
            UglyNumberInfo info = pq.top();
            pq.pop();
            if (info.uglyNumber > uglyNumbers.back()) {
                uglyNumbers.push_back(info.uglyNumber);
            }
            update(uglyNumbers, info);
            pq.push(info);
        }

        return uglyNumbers.back();
    }
};

int main() {
    Solution S;
    S.nthUglyNumber(10);
    return 0;
}
