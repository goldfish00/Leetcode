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

/* 252. Meeting Rooms */
class Solution {
private:
    class IntervalPrecede{
    public:
        bool operator()(const vector<int>& leftInterval, const vector<int>& rightInterval) {
            return leftInterval[0] < rightInterval[0];
        }
    };
    
public:
    bool canAttendMeetings(vector<vector<int>>& intervals) {
        if (intervals.size() < 2) {
            return true;
        }
        
        IntervalPrecede lessCmp;
        sort(intervals.begin(), intervals.end(), lessCmp);
        for (int i = 0; i < intervals.size() - 1; ++i) {
            // if the latter meetings start time percede the previous meeting's end time
            if (intervals[i + 1][0] < intervals[i][1]) {
                return false;
            }
        }
        return true;
    }
};


int main() {
    
    return 0;
}
