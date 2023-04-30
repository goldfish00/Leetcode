#include <iostream>
#include <sstream>
#include <string>
// unordered_multiset here
#include <unordered_set>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>
#include <assert.h>
#include <set>
#include <deque>
#include <queue>
#include <unordered_map>
#include <queue>
#include <map>
#include <numeric>
#include <list>
#include <forward_list>
using namespace std;

/* 289. Game of Life */
//class Solution {
//private:
//
//public:
//    void gameOfLife(vector<vector<int>>& board) {
//        size_t numRow = board.size();
//        size_t numColumn = board[0].size();
//
//
//    }
//};

/* 291. Word Pattern II */
//class Solution {
//public:
//    bool wordPatternMatch(string pattern, string s) {
//
//    }
//};

/* 294. Flip Game II */
//class Solution {
//public:
//    bool canWin(string currentState) {
//
//    }
//};

/* 312. Burst Balloons */
//class Solution {
//public:
//    int maxCoins(vector<int>& nums) {
//
//    }
//};


/* 315. Count of Smaller Numbers After Self */
// Method 3: merge sort
/*
 *  consider the following step in the merge sort:
 *  vector1: [1, 3, 5], vector2: [2, 3, 4]
 *  the merged result will be: [1, 2, 3, 3, 4, 5]
 *  and the result for this problem will be [0, 1 (2 goes before 3), 3 (2, 3, 4 goes before 5), 0, 0, 0]
 */
//class Solution {
//private:
//    // merge sort range [begin, end]
//    void mergeSortAndUpdate(vector<int>& nums, int begin, int end, vector<int>& res) {
//        if (begin == end) {
//            return;
//        }
//        int middle = begin + (end - begin) / 2;
//        mergeSortAndUpdate(nums, begin, middle, res);
//        mergeSortAndUpdate(nums, middle + 1, end, res);
//
//        vector<int> vec1(nums.begin() + begin, nums.begin() + middle + 1); // [begin, middle]
//        vector<int> vec2(nums.begin() + middle + 1, nums.begin() + end + 1); // [middle + 1, end]
//        auto it1 = vec1.begin();
//        auto it2 = vec2.begin();
//        auto numsIt = nums.begin() + begin;
//        int startInd = begin;
//        while (it1 != vec1.end() && it2 != vec2.end()) {
//            if (*it2 < *it1) {
//                *numsIt = *it2;
//                for (int i = startInd; i <= )
//            }
//        }
//    }
//
//public:
//    vector<int> countSmaller(vector<int>& nums) {
//        vector<int> res(nums.size(), 0);
//        mergeSortAndUpdate(nums, 0, int(nums.size()) - 1, res);
//        return res;
//    }
//};

/* 321. Create Maximum Number */


//int main() {
//    vector<int> nums1{4,6,9,1,0,6,3,1,5,2,8,3,8,8,4,7,2,0,7,1,9,9,0,1,5,9,3,9,3,9,7,3,0,8,1,0,9,1,6,8,8,4,4,5,7,5,2,8,2,7,7,7,4,8,5,0,9,6,9,2};
//    vector<int> nums2{9,9,4,5,1,2,0,9,3,4,6,3,0,9,2,8,8,2,4,8,6,5,4,4,2,9,5,0,7,3,7,5,9,6,6,8,8,0,2,4,2,2,1,6,6,5,3,6,2,9,6,4,5,9,7,8,0,7,2,3};
//    Solution S;
//    S.maxNumber(nums1, nums2, 60);
//    return 0;
//}


