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

/* 255. Verify Preorder Sequence in Binary Search Tree */
// There should be a clear cut-off: once there is an element greater than the root, all other element should be also greater than the root
class Solution {
    // [startIndex, endIndex)
    bool verifyPreorder(const vector<int>& preorder, int startIndex, int endIndex) {
        if (startIndex == endIndex) {
            return true;
        }
        if (endIndex - startIndex < 3) {
            return true;
        }
        
        bool isGreater = false;
        int greaterIndex = endIndex;
        int rootVal = preorder[startIndex];
        for (int i = startIndex + 1; i < endIndex; ++i) {
            int currentVal = preorder[i];
            if (!isGreater && currentVal > rootVal) { // find the first greater; tie is not possible since vals are unique
                isGreater = true;
                greaterIndex = i;
                continue;
            }
            if (isGreater && currentVal < rootVal) {
                return false;
            }
        }
        
        return verifyPreorder(preorder, startIndex + 1, greaterIndex) && verifyPreorder(preorder, greaterIndex, endIndex);
    }
    
public:
    bool verifyPreorder(vector<int>& preorder) {
        return verifyPreorder(preorder, 0, (int)preorder.size());
    }
};

int main() {
    Solution S;
    
    return 0;
}
