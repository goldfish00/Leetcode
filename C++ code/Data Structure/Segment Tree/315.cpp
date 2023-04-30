/* 315. Count of Smaller Numbers After Self */
// Solution 1: segment tree
class Solution {
private:
    int offset;
    int numLeafNode;
    vector<int> segTreeArr;
    
    pair<int, int> findRange(const vector<int>& nums) {
        pair<int, int> minMax{nums.front(), nums.front()};
        for (const int& num : nums) {
            if (num < minMax.first) {
                minMax.first = num;
            } else if (num > minMax.second) {
                minMax.second = num;
            }
        }
        
        return minMax;
    }
    
    size_t findParentIndex(size_t childIndex) {
        if (childIndex == 0) {
            return childIndex;
        }
        
        if ((childIndex & 1) == 0) { // even
            return (childIndex - 2) / 2;
        }
        
        // odd
        return (childIndex - 1) / 2;
    }
    
    size_t findLeftChildIndex(size_t parentIndex) {
        return parentIndex * 2 + 1;
    }
    
    size_t findRightChildIndex(size_t parentIndex) {
        return parentIndex * 2 + 2;
    }
    
    size_t findLeafNodeIndex(int num) {
        return numLeafNode - 1 /* num non-leaf node */ + num /* index with offset */;
    }
    
    int findNumNode(int range) {
        numLeafNode = 1;
        while (range > numLeafNode) {
            numLeafNode <<= 1;
        }
        
        return numLeafNode;
    }
    
    void update(int num) {
        size_t nodeIndex = findLeafNodeIndex(num);
        while (1) {
            segTreeArr[nodeIndex] += 1;
            
            if (nodeIndex == 0) {
                break;
            }
            nodeIndex = findParentIndex(nodeIndex);
        }
    }
    
    int query(size_t treeIndex, int left, int right, int queryLeft, int queryRight) {
        if (queryLeft > right || queryRight < left ) { // out of range
            return 0;
        }
        
        if (queryRight < queryLeft) {
            return 0;
        }
        
        if (queryRight == right && queryLeft == left) {
            return segTreeArr[treeIndex];
        }
        
        if (queryLeft == queryRight) { // query leaf node
            return segTreeArr[findLeafNodeIndex(queryLeft)];
        }
        
        int mid = left + (right - left) / 2;
        if (queryRight <= mid) {
            return query(findLeftChildIndex(treeIndex), left, mid, queryLeft, queryRight);
        }
        if (queryLeft > mid) {
            return query(findRightChildIndex(treeIndex), mid + 1, right, queryLeft, queryRight);
        }
        return query(findLeftChildIndex(treeIndex), left, mid, queryLeft, mid) +\
            query(findRightChildIndex(treeIndex), mid + 1, right, mid + 1, queryRight);
    }
    
public:
    vector<int> countSmaller(vector<int>& nums) {
        if (nums.size() == 0) {
            return vector<int>{0};
        }
        
        auto minMax = findRange(nums);
        offset = -minMax.first;
        segTreeArr.resize(2 * findNumNode(minMax.second - minMax.first + 1));
        
        vector<int> res(nums.size(), 0);
        for (auto numsIt = nums.rbegin(), resIt = res.rbegin(); numsIt != nums.rend(); ++numsIt, ++resIt) {
            *numsIt += offset;
            *resIt = query(0, 0, numLeafNode - 1, 0, *numsIt - 1);
            update(*numsIt);
        }
        return res;
    }
};

int main() {
    Solution S;
//    vector<int> nums{5, 2, 6, 1};
    vector<int> nums{-1, -1};
    S.countSmaller(nums);
    return 0;
}
