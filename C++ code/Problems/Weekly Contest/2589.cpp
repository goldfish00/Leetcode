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

/* 2589. Minimum Time to Complete All Tasks */
class Solution {
private:
    int getAlreadyOccupiedTime(const vector<bool>& timeWindowUsed, const vector<int>& task) {
        int alreadyOccupied = 0;
        for (int i = task[0]; i <= task[1]; ++i) {
            if (timeWindowUsed[i]) ++alreadyOccupied;
        }
        return alreadyOccupied;
    }
    
public:
    int findMinimumTime(vector<vector<int>>& tasks) {
        // sort by endTime
        sort(tasks.begin(), tasks.end(), [](const vector<int>& left, const vector<int>& right){
            return left[1] < right[1];
        });
        vector<bool> timeWindowUsed(tasks.back()[1] + 1, false);
        int minimumTime = 0;
        
        for (const auto& task : tasks) {
            int alreadyOccupied = getAlreadyOccupiedTime(timeWindowUsed, task);
            if (alreadyOccupied >= task[2]) {
                continue;
            }
            int timeToOccupy = task[2] - alreadyOccupied;
            minimumTime += timeToOccupy;
            
            for (int i = task[1]; i >= task[0] && timeToOccupy > 0; --i) {
                if (!timeWindowUsed[i]) {
                    --timeToOccupy;
                    timeWindowUsed[i] = true;
                }
            }
        }
        
        return minimumTime;
    }
};

