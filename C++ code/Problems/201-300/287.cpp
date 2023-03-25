/* 287. Find the Duplicate Number */
/* Brute Force: TLE*/
//class Solution {
//public:
//    int findDuplicate(vector<int>& nums) {
//        for (auto it = nums.begin(); it != nums.end(); ++it) {
//            for (auto otherIt = it + 1; otherIt != nums.end(); ++otherIt) {
//                if (*otherIt == *it) {
//                    return *it;
//                }
//            }
//        }
//        return 0;
//    }
//};

// Negative Marking: Passed
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int nextToVisit = nums.front();
        while (1) {
            int& val = nums[nextToVisit];
            if (val < 0) { // already visited
                return nextToVisit;
            }
            nextToVisit = val;
            val *= -1;
        }
        return 0;
    }
};

