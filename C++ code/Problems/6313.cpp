#include <iostream>
// unordered_multiset here
#include <unordered_set>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>
#include <assert.h>
using namespace std;

/* 6313. Count Ways to Group Overlapping Ranges */
class Solution {
private:
    class StartingLess {
    public:
        bool operator()(const vector<int>& left, const vector<int>& right) {
            if (left.front() < right.front()) {
                return true;
            }
            if (left.front() == right.front()) {
                return left.end() < right.end();
            }
            return false;
        }
    };
    
    // the left's starting time is no greater then the right's
    bool hasOverlapped(const vector<int>& left, const vector<int>& right) {
        return right.front() <= left.back();
    }
    
    void merge(vector<int>& master, const vector<int>& overlappedChildren) {
        master.front() = min(master.front(), overlappedChildren.front());
        master.back() = max(master.back(), overlappedChildren.back());
    }
    
public:
    int countWays(vector<vector<int>>& ranges) {
        StartingLess less;
        sort(ranges.begin(), ranges.end(), less);
        // index of the first overlapped range
        vector<int> masterIndices;
        masterIndices.resize(ranges.size());
        
        for (int i = 0; i < ranges.size(); ++i) {
            if (i == 0) {
                masterIndices[i] = 0;
                continue;
            }
            
            int previousIndex = masterIndices[i - 1];
            if (hasOverlapped(ranges[previousIndex], ranges[i])) {
                masterIndices[i] = previousIndex;
                merge(ranges[previousIndex], ranges[i]);
            } else {
                masterIndices[i] = i;
            }
        }
        
        int distinctBucket = 1;
        for (auto it = masterIndices.begin() + 1; it != masterIndices.end(); ++it) {
            if (*it != *(it - 1)) {
                ++distinctBucket;
            }
        }
        
        int numPossible = 1;
        int modula = (int)pow(10, 9) + 7;
        while (distinctBucket > 0) {
            numPossible <<= 1;
            if (numPossible > modula) {
                numPossible = numPossible % modula;
            }
            --distinctBucket;
        }
        return numPossible;
    }
};

int main() {
    Solution S;
    vector<vector<int>> integers{{6, 10}, {5, 15}};
    S.countWays(integers);
    return 0;
}
