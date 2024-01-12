#include <iostream>
#include <sstream>
#include <string>
// unordered_multiset here
#include <unordered_set>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>
#include <assert.h>
#include <set>
#include <deque>
#include <queue>
#include <unordered_map>
#include <queue>
#include <map>
#include <numeric>
#include <list>
#include <forward_list>
using namespace std;

class SegmentSumTree {
private:
    int numLeaf;
    vector<int> sumNodes;
    
    struct Range {
        int left;
        int right;
        
        Range(int left, int right): left(left), right(right) {}
        
        bool isLeaf() const {
            return left == right;
        }
        
        bool contains(const Range& other) const {
            return other.left >= left && other.right <= right;
        }
        
        int getMiddle() const {
            return left + (right - left) / 2;
        }
        
        Range leftRange() const {
            return Range(left, getMiddle());
        }
        
        Range rightRange() const {
            return Range(1 + getMiddle(), right);
        }
    };
    
    static int calcLeafRanges(int numLeaf) {
        int range = 1;
        while (range < numLeaf) {
            range <<= 1;
        }
        return range;
    }
    
    int getLeftChildIndex(int index) {
        return 2 * index + 1;
    }
    
    int getRightChildIndex(int index) {
        return 2 * index + 2;
    }
    
    Range allRange;
    
    int getNodeValue(int index) {
        if (index >= sumNodes.size()) {
            return 0;
        }
        
        return sumNodes[index];
    }
    
    /**
     * @param index should not be zero
     */
    int getParentIndex(int index) {
        if (index == 0) {
            throw runtime_error("trying to get the parent index of index 0");
        }
        
        return (index - 1) / 2;
    }
    
    void initializeInternal(int treeIndex, const Range& range, const vector<int>& leafNodes) {
        if (range.isLeaf()) {
            if (range.left < numLeaf) {
                sumNodes[treeIndex] = leafNodes[range.left];
            }
            return;
        }
        
        if (treeIndex >= sumNodes.size()) {
            return;
        }

        int leftChildIndex = getLeftChildIndex(treeIndex);
        int rightChildIndex = getRightChildIndex(treeIndex);
        initializeInternal(leftChildIndex, range.leftRange(), leafNodes);
        initializeInternal(rightChildIndex, range.rightRange(), leafNodes);
        
        sumNodes[treeIndex] = getNodeValue(leftChildIndex) + getNodeValue(rightChildIndex);
    }
    
    int query(int treeIndex, const Range& indexRange, const Range& queryRange) {
        if (queryRange.contains(indexRange)) {
            return getNodeValue(treeIndex);
        }
        
        if (indexRange.right < queryRange.left || indexRange.left > queryRange.right) {
            return 0;
        }
        
        return query(getLeftChildIndex(treeIndex), indexRange.leftRange(), queryRange) + query(getRightChildIndex(treeIndex), indexRange.rightRange(), queryRange);
    }
    
    void update(int treeIndex, const Range& indexRange, int updateIndex, int newVal) {
        if (indexRange.isLeaf()) {
            sumNodes[treeIndex] = newVal;
            return;
        }
        
        int rightChildId = getRightChildIndex(treeIndex);
        int leftChildId = getLeftChildIndex(treeIndex);
        int mid = indexRange.getMiddle();
        if (updateIndex > mid) {
            update(rightChildId, indexRange.rightRange(), updateIndex, newVal);
        } else {
            update(leftChildId, indexRange.leftRange(), updateIndex, newVal);
        }
        
        sumNodes[treeIndex] = getNodeValue(leftChildId) + getNodeValue(rightChildId);
    }
    
public:
    /**
     * @param nodes  should not be empty; the vector of leaf nodes passed to the segment tree
     */
    SegmentSumTree(const vector<int> nodes): numLeaf((int) nodes.size()), sumNodes(vector<int>(nodes.size() * 3, 0)), allRange(Range(0, calcLeafRanges((int)nodes.size()) - 1)) {
        if (nodes.empty()) {
            throw runtime_error("leaf nodes should not be empty");
        }
        initializeInternal(0, allRange, nodes);
    }
    
    /**
     * @param floor the left inclusive range
     * @param ceil the right inclusive range
     */
    int query(int floor, int ceil) {
        return query(0, allRange, Range(floor, ceil));
    }
    
    void update(int index, int newVal) {
        if (index >= numLeaf) {
            throw runtime_error("the index to update is out of range");
        }
        
        update(0, allRange, index, newVal);
    }
};

class NumArray {
private:
    SegmentSumTree segTree;
public:
    NumArray(vector<int>& nums): segTree(SegmentSumTree(nums)) {}
    
    void update(int index, int val) {
        segTree.update(index, val);
    }
    
    int sumRange(int left, int right) {
        return segTree.query(left, right);
    }
};
                                                                                
int main() {
    vector<int> nums{1,3,5};
    NumArray arr(nums);
    cout << arr.sumRange(0, 2) << endl;
    arr.update(1, 2);
    cout << arr.sumRange(0, 2) << endl;
    
    return 0;
}

