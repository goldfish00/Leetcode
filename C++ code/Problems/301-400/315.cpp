/* 315. Count of Smaller Numbers After Self */
// TLE
//class Solution {
//public:
//    vector<int> countSmaller(vector<int>& nums) {
//        vector<int> res;
//        res.reserve(nums.size());
//
//        vector<int> sortedNums(nums.begin(), nums.end());
//        sort(sortedNums.begin(), sortedNums.end());
//        for (int i = 0; i < nums.size(); ++i) {
//            res.push_back(int(lower_bound(sortedNums.begin(), sortedNums.end(), nums[i]) - sortedNums.begin()));
//        }
//
//        sortedNums.clear();
//        for (int i = 0; i < nums.size(); ++i) {
//            auto it = lower_bound(sortedNums.begin(), sortedNums.end(), nums[i]);
//            res[i] -= int(it - sortedNums.begin());
//            sortedNums.insert(it, nums[i]);
//        }
//
//        return res;
//    }
//};

// TLE
//class Solution {
//public:
//    vector<int> countSmaller(vector<int>& nums) {
//        vector<int> sortedNums;
//        sortedNums.reserve(nums.size());
//        sortedNums.push_back(nums.back());
//
//        vector<int> res(nums.size(), 0);
//        for (auto numsIt = nums.rbegin() + 1, resIt = res.rbegin() + 1; numsIt != nums.rend(); ++numsIt, ++resIt) {
//            auto upperIt = lower_bound(sortedNums.begin(), sortedNums.end(), *numsIt);
//            *resIt = int(upperIt - sortedNums.begin());
//            sortedNums.insert(upperIt, *numsIt);
//        }
//
//        return res;
//    }
//};

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

/* 315. Count of Smaller Numbers After Self */
// Binary Tree / Fenwich Tree
/*
 * The idea of binary index tree / Finwich Tree is to store the partial incremental data using LSB (least significant bit)
 * When querying, the next index can be generated by subtracting the LSB from the previous index
 * When updating, the next index can be generated by adding the LSB to the previous index
 */

/*
 * This problem can be transformed into the following binary index tree:
 * 1. get the range of nums vector, and store an offset which equals to -min (turns the smallest value into zero)
 * 2. iterate nums vector from the last element to the first
 * 3. in the fenwich tree, caculate the cumulated number of vals of the current range, from [0, num + offset - 1]
 * 4. update the finwich tree by adding 1 to tree[num + offset]
 */
class Solution {
private:
    int offset;
    vector<int> fenTree;
    
    void initializeFenTree(const vector<int>& nums) {
        pair<int, int> minMax{nums.front(), nums.front()};
        for (const int& num : nums) {
            if (num < minMax.first) {
                minMax.first = num;
            } else if (num > minMax.second) {
                minMax.second = num;
            }
        }
        
        // Notice: fenwich tree is 1-based for lsb calculation
        offset = -minMax.first + 1;
        fenTree.resize(minMax.second - minMax.first + 2);
    }
    
    int lsb(const int& num) {
        return num & (-num);
    }
    
    void update(const int& num) {
        int adjustedNum = num + offset;
        while (adjustedNum < fenTree.size()) {
            fenTree[adjustedNum] += 1;
            adjustedNum += lsb(adjustedNum);
        }
    }
    
    int query(const int& num) {
        int adjustedNum = num + offset - 1;
        int cumulatedVal = 0;
        
        while (1) {
            cumulatedVal += fenTree[adjustedNum];
            adjustedNum -= lsb(adjustedNum);
            if (adjustedNum == 0) {
                break;
            }
        }
        return cumulatedVal;
    }
    
public:
    vector<int> countSmaller(vector<int>& nums) {
        if (nums.size() == 1) {
            return vector<int>{0};
        }
        
        initializeFenTree(nums);
        
        vector<int> res(nums.size(), 0);
        for (auto numsIt = nums.rbegin(), resIt = res.rbegin(); numsIt != nums.rend(); ++numsIt, ++resIt) {
            *resIt = query(*numsIt);
            update(*numsIt);
        }
        return res;
    }
};

int main() {
    vector<int> nums{5, 2, 6, 1};
    Solution S;
    S.countSmaller(nums);
    
    return 0;
}



