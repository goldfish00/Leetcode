
#include <iostream>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>
#include <set>
// unordered_multiset here
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
#include <cmath>
using namespace std;

/*  Meeting Rooms II */ /* Sliding window */
class Solution {
private:
    class IntervalCmp{
    public:
        bool operator()(const vector<int>& leftInterval, const vector<int>& rightInterval) {
            return leftInterval.front() < rightInterval.front();
        }
    };
    
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        // sort
        IntervalCmp iLess;
        sort(intervals.begin(), intervals.end(), iLess);
        
        int minRoom = 0;
        multiset<int> intervalEnds;
        
        for (const auto& interval: intervals) {
            if (intervalEnds.empty()) {
                intervalEnds.insert(interval.back());
                continue;
            }
            
            // if still overlap
            if (interval.front() < *(intervalEnds.begin())) {
                intervalEnds.insert(interval.back());
                continue;
            }
            
            // if not, update and clear
            minRoom = max((int) intervalEnds.size(), minRoom);
            while (!intervalEnds.empty() && *(intervalEnds.begin()) <= interval.front()) {
                intervalEnds.erase(intervalEnds.begin());
            }
            intervalEnds.insert(interval.back());
        }
        
        minRoom = max(minRoom, (int) intervalEnds.size());
        return minRoom;
    }
};


int main() {
    
    return 0;
}
