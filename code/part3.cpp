#include <iostream>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>
#include <set>
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
using namespace std;

/* #167 *//*
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int> result;
        int left = 0;
        int right = int(numbers.size()) - 1;
        while (left < right) {
            if (numbers[left] + numbers[right] == target) {
                result.push_back(left + 1);
                result.push_back(right + 1);
                break;
            }
            else if (numbers[left] + numbers[right] > target) --right;
            else ++left;
        }
        
        return result;
    }
};*/

/* #168 *//*
class Solution {
public:
    string convertToTitle(int columnNumber) {
        stack<int> digits;
        int base = 26;
        while (columnNumber) {
            // convert to 0 base
            --columnNumber;
            digits.push(columnNumber % base);
            columnNumber /= base;
        }
        
        string result(digits.size(), ' ');
        int i = 0;
        while (!digits.empty()) {
            result[i] = 'A' + digits.top();
            digits.pop();
            ++i;
        }
        return result;
    }
};*/

/* #169 Boyer-Moore Voting Algorithm *//*
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int count = 1;
        int candidate = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            if (count == 0) candidate = nums[i];
            if (nums[i] == candidate) ++count;
            else --count;
        }
        return candidate;
    }
};*/

/* #170 *//* Time limit exceeded*//*
class TwoSum {
private:
    list<int> nums;
    
public:
    TwoSum() {}
    
    void add(int number) {
        auto it = upper_bound(nums.begin(), nums.end(), number);
        nums.insert(it, number);
    }
    
    bool find(int value) {
        if (nums.size() < 2) return false;
        auto left = nums.begin();
        auto right = --nums.end();
        while (left != right) {
            if (*left + *right == value) return true;
            else if (*left == *right) return false;
            else if (*left + *right < value) ++left;
            else --right;
        }
        return false;
    }
};

// a beautiful solution
class TwoSum {
    unordered_multiset<int> nums;
public:
    void add(int number) {
        nums.insert(number);
    }
    bool find(int value) {
        for (int i : nums) {
            int count = i == value - i ? 1 : 0;
            if (nums.count(value - i) > count) {
                return true;
            }
        }
        return false;
    }
};*/
/**
* Your TwoSum object will be instantiated and called as such:
* TwoSum* obj = new TwoSum();
* obj->add(number);
* bool param_2 = obj->find(value);
*/

/* 171 *//*
class Solution {
public:
    int titleToNumber(string columnTitle) {
        int res = 0;
        for (auto c : columnTitle) {
            res *= 26;
            res += c - 'A' + 1;
        }
        return res;
    }
};*/

/* #172 *//*
class Solution {
private:
    int num2 = 0;
    int num5 = 0;
    
    void getNum2(int n){
        while (n) {
            n = n >> 1;
            num2 += n;
        }
    }
    
    void getNum5(int n){
        while (n) {
            n /= 5;
            num5 += n;
        }
    }
    
public:
    int trailingZeroes(int n) {
        getNum2(n);
        getNum5(n);
        return min(num5, num2);
    }
};*/


/* #173 Using Stack for inorder traversal */
// Definition for a binary tree node.
/*
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};*/
/*
class BSTIterator {
private:
    stack<TreeNode*> Stack;
    
public:
    BSTIterator(TreeNode* root) {
        while (root) {
            Stack.push(root);
            root = root->left;
        }
    }
    
    int next() {
        TreeNode* curr = Stack.top();
        int res = curr->val;
        Stack.pop();
        if (curr->right){
            curr = curr->right;
            while (curr) {
                Stack.push(curr);
                curr = curr->left;
            }
        }
        return res;
    }
    
    bool hasNext() {
        return !Stack.empty();
    }
};*/
/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */




int main(){
    Solution S;
    //vector<string> words{"zzyy","zy","zyy"};
    //vector<vector<char>> board{{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}};
    vector<int> nums{94,89,54,26,54,54,99,64};
    vector<string> words{"cat","cats","and","sand","dog"};
    return 0;
}
