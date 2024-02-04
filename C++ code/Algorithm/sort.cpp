//
//  main.cpp
//  leetcode
//
//  Created by Junyi Huang on 1/23/24.
//

#include <iostream>
#include <vector>
using namespace std;

class Solution {
private:
    vector<int> bubbleSort(vector<int>& nums) {
        bool hasSwapped = true;
        
        while (hasSwapped) {
            hasSwapped = false;
            
            for (int i = 0; i < nums.size() - 1; ++i) {
                if (nums[i] > nums[i + 1]) {
                    swap(nums[i], nums[i + 1]);
                    hasSwapped = true;
                }
            }
        }
        
        return move(nums);
    }
    
    vector<int> selectionSort(vector<int>& nums) {
        for (int i = 0; i < nums.size() - 1; ++i) {
            int minId = -1;
            int minVal = INT_MAX;
            
            for (int j = i; j < nums.size(); ++j) {
                const int& curNum = nums[j];
                if (curNum < minVal) {
                    minVal = curNum;
                    minId = j;
                }
            }
            
            swap(nums[minId], nums[i]);
        }
        
        return move(nums);
    }
    
    vector<int> mergeSorted(vector<int>&& left, vector<int>&& right) {
        vector<int> res;
        res.reserve(left.size() + right.size());
        
        auto leftIt = left.begin();
        auto rightIt = right.begin();
        while (leftIt != left.end() && rightIt != right.end()) {
            if (*leftIt < *rightIt) {
                res.push_back(*leftIt);
                ++leftIt;
            } else {
                res.push_back(*rightIt);
                ++rightIt;
            }
        }
        
        while (leftIt != left.end()) {
            res.push_back(*leftIt);
            ++leftIt;
        }
        
        while (rightIt != right.end()) {
            res.push_back(*rightIt);
            ++rightIt;
        }
        
        return move(res);
    }
    
    vector<int> mergeSort(vector<int>&& nums) {
        if (nums.empty() || nums.size() == 1) {
            return move(nums);
        }
        
        int firstHalfSize = static_cast<int>(nums.size()) / 2;
        auto middleIt = nums.begin() + firstHalfSize;
        auto firstSorted = mergeSort(vector<int>(nums.begin(), middleIt));
        auto secondSorted = mergeSort(vector<int>(middleIt, nums.end()));
        
        vector<int> res(mergeSorted(move(firstSorted), move(secondSorted)));
        return move(res);
    }
    
    // inplace sort
    // range [left, right]
    void quickSort(vector<int>& nums, int left, int right) {
        if (left >= right) {
            return;
        }
        
        int midId = left + (right - left) / 2;
        int pivotVal = nums[midId];
        int countNoGreater = 0;
        for (int i = left; i <= right; ++i) {
            if (nums[i] <= pivotVal) {
                ++countNoGreater;
            }
        }
        
        int pivotId = left + countNoGreater - 1;
        swap(nums[midId], nums[pivotId]);
        
        int leftPt = left;
        int rightPt = right;
        while (true) {
            while (left < pivotId && nums[left] <= pivotVal) {
                ++left;
            }
            
            while (nums[right] > pivotVal) {
                --right;
            }
            
            if (right != pivotId && left < pivotId) {
                swap(nums[left], nums[right]);
                ++left;
                --right;
            }
            
            if (right == pivotId) {
                break;
            }
        }
        
        quickSort(nums, leftPt, pivotId - 1);
        quickSort(nums, pivotId + 1, rightPt);
    }
    
public:
    vector<int> sortArray(vector<int>& nums) {
        // Bubble sort: TLE
        // return bubbleSort(nums);
        // Selection sort: TLE
        // return selectionSort(nums);
        // Merge sort: passed
        // return mergeSort(move(nums));
        // Quick sort TLE for many inputs with the same value
        // quickSort(nums, 0, static_cast<int>(nums.size()) - 1);
        return move(nums);
    }
};

int main(int argc, const char * argv[]) {
    vector<int> nums{5,1,1,2,0,0};
    Solution S;
    auto res = S.sortArray(nums);
    for_each(res.begin(), res.end(), [](int n){cout << n << " ";});
    cout << "\n";
    
    return 0;
}

