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
#include <map>
using namespace std;

/* 2594. Minimum Time to Repair Cars */
//class Solution {
//public:
//    long long repairCars(vector<int>& ranks, int cars) {
//        map<int, int> numRankMap;
//        for (const int& rank : ranks) {
//            ++numRankMap[rank];
//        }
//
//    }
//};
//
//int main() {
//    vector<int> ranks{3,3,1,2,1,1,3,2,1};
//    Solution S;
//    cout << S.repairCars(ranks, 58) << endl;
//    return 0;
//}
