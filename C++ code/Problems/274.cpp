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

/* 274. H-Index */
class Solution {
public:
    int hIndex(vector<int>& citations) {
        sort(citations.begin(), citations.end(), greater<int>());
        
        int hIndex = 0;
        for (int i = 0; i < citations.size(); ++i) {
            int numCitation = citations[i];
            int numPaper = i + 1;
            hIndex = max(hIndex, min(numCitation, numPaper));
            
            if (numCitation < numPaper) {
                return hIndex;
            }
        }
        
        return hIndex;
    }
};

