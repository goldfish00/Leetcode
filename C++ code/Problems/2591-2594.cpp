/* 6323. Distribute Money to Maximum Children */
//class Solution {
//public:
//    int distMoney(int money, int children) {
//        if (money < children) {
//            return -1;
//        }
//
//        // distribute the first dollar first
//        money -= children;
//        int numSeven = money / 7;
//        int residue = money % 7;
//        if ((numSeven == children && residue != 0) || numSeven > children) {
//            return children - 1;
//        }
//
//
//        // check for 4
//        if (residue == 3 && children - numSeven == 1) {
//            return numSeven - 1;
//        }
//        return numSeven;
//    }
//};
//
//int main() {
//    Solution S;
////    S.distMoney(17, 2);
//    S.distMoney(23, 2);
//    return 0;
//}

/* 6324. Maximize Greatness of an Array */
//class Solution {
//public:
//    int maximizeGreatness(vector<int>& nums) {
//        sort(nums.begin(), nums.end());
//        vector<int> uniqueCount;
//        int count = 1;
//
//        for (auto it = nums.begin() + 1; it != nums.end(); ++it) {
//            if (*it == *(it - 1)) {
//                ++count;
//            } else {
//                uniqueCount.push_back(count);
//                count = 1;
//            }
//        }
//        uniqueCount.push_back(count);
//
//        int maximalGreaterNum = 0;
//        int unfulfilled = 0;
//        for (auto it = uniqueCount.begin() + 1; it != uniqueCount.end(); ++it) {
//            int diff = *it - *(it - 1);
//            if (diff <= 0) {
//                unfulfilled -= diff;
//                maximalGreaterNum += *it;
//            } else { // diff > 0
//                maximalGreaterNum += *(it - 1);
//                maximalGreaterNum += min(diff, unfulfilled);
//                unfulfilled = max(unfulfilled - diff, 0);
//            }
//        }
//
//        return maximalGreaterNum;
//    }
//};

/* 6351. Find Score of an Array After Marking All Elements */
//class Solution {
//private:
//    void eraserIndex(const vector<int>& nums, map<int, set<int>>& valIndicesMap, int index) {
//        auto it = valIndicesMap.find(nums[index]);
//        if (it == valIndicesMap.end()) {
//            return;
//        }
//        it->second.erase(index);
//        if (it->second.empty()) {
//            valIndicesMap.erase(it);
//        }
//    }
//
//public:
//    long long findScore(vector<int>& nums) {
//        map<int, set<int>> valIndicesMap;
//        for (int i = 0; i < nums.size(); ++i) {
//            valIndicesMap[nums[i]].insert(i);
//        }
//
//        long long score = 0;
//        while (!valIndicesMap.empty()) {
//            auto it = valIndicesMap.begin();
//            score += it->first;
//
//            set<int>& indices = it->second;
//            int index = *indices.begin();
//            indices.erase(indices.begin());
//            if (indices.empty()) {
//                valIndicesMap.erase(it);
//            }
//
//            if (index + 1 != nums.size()) {
//                eraserIndex(nums, valIndicesMap, index + 1);
//            }
//            if (index != 0) {
//                eraserIndex(nums, valIndicesMap, index - 1);
//            }
//        }
//
//        return score;
//    }
//};
//
//int main() {
//    vector<int> nums{2,1,3,4,5,2};
//    Solution S;
//    S.findScore(nums);
//    return 0;
//}

/* 6325. Minimum Time to Repair Cars */
/* Backtrack: TLE */
class Solution {
private:
    long long findWithBacktrack(const vector<int>& ranks, int mechanismIndex, int cars, long long time, const long long& upperBound) {
        if (mechanismIndex + 1 == ranks.size()) {
            long long timeNeeded = ranks.back() * pow(cars, 2);
            return max(timeNeeded, time);
        }

        long long minTime = time;
        for (int i = cars, j = 0; i >= 0; --i, ++j) {
            long long timeNeeded = ranks[mechanismIndex] * pow(i, 2);
            if (timeNeeded > upperBound) {
                minTime = upperBound;
                continue;
            }

            if (j == 0) {
                minTime = max(minTime, timeNeeded);
            } else {
                minTime = min(minTime, findWithBacktrack(ranks, mechanismIndex + 1, j, max(time, timeNeeded), upperBound));
            }
        }
        return minTime;
    }

public:
    long long repairCars(vector<int>& ranks, int cars) {
        sort(ranks.begin(), ranks.end());
        long long upperBound = ranks.front() * pow(cars, 2);
        return findWithBacktrack(ranks, 0, cars, 0, upperBound);
    }
};

