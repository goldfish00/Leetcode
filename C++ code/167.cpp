#include <iostream>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>
#include <set>
// onordered_multiset here
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

/* #174 *//* Using DP*//*
class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        size_t numRow = dungeon.size();
        size_t numColumn = dungeon[0].size();
        // the matrix[i][j] denotes the minimum health before passing through the dungeon block[i][j]
        int minHealth[numRow][numColumn];
        // initialize
        minHealth[numRow - 1][numColumn - 1] = max(1, 1 - dungeon[numRow - 1][numColumn - 1]);
        // last column
        for (int i = int(numRow) - 2; i >= 0; --i) {
            minHealth[i][numColumn - 1] = max(1, minHealth[i + 1][numColumn - 1] - dungeon[i][numColumn - 1]);
        }
        // last row
        for (int i = int(numColumn) - 2; i >= 0; --i) {
            minHealth[numRow - 1][i] = max(1, minHealth[numRow - 1][i + 1] - dungeon[numRow - 1][i]);
        }
        // inner part
        for (int row = int(numRow) - 2; row >= 0; --row) {
            for (int column = int(numColumn) - 2; column >= 0; --column) {
                minHealth[row][column] = min(minHealth[row + 1][column], minHealth[row][column + 1]) - dungeon[row][column];
                minHealth[row][column] = max(minHealth[row][column], 1);
            }
        }
        return minHealth[0][0];
    }
};*/


/* #179 *//*
class Solution {
private:
    class StringLess{
    public:
        bool operator()(int leftInt, int rightInt){
            string left = to_string(leftInt);
            string right = to_string(rightInt);
            if (left.size() == right.size()) return left < right;
            if (left[0] != right[0]) return left[0] < right[0];
            return left + right < right + left;
        }
    };
    
public:
    string largestNumber(vector<int>& nums) {
        StringLess cmp;
        sort(nums.begin(), nums.end(), cmp);
        if (nums.front() == nums.back() && nums.back() == 0) return to_string(0);
        string res;
        while (!nums.empty()) {
            res.append(to_string(nums.back()));
            nums.pop_back();
        }
        return res;
    }
};*/

/* #186 *//*
class Solution {
public:
    void reverseWords(vector<char>& s) {
        // the idea: from the last character in the vector, find the space and write
        vector<char> res(s.size());
        // the next world to write [start, end]
        int start = int(s.size() - 1);
        int end = int(s.size() - 1);
        auto writePlace = res.begin();
        while (writePlace != res.end()) {
            // find the space
            while (start > 0) {
                if (s[start] == ' ') break;
                --start;
            }
            // write
            for (int ind = start; ind <= end; ++ind, ++writePlace) {
                if (writePlace == res.begin()){
                    if(ind != 0) ++ind;
                }
                else if (ind == 0){
                    *writePlace = ' ';
                    ++writePlace;
                }
                *writePlace = s[ind];
            }
            start = end = start - 1;
        }
        swap(s, res);
    }
};*/

/* #187 *//*
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        if (s.length() < 11) return vector<string>();
        vector<string> res;
        res.reserve(s.length() - 9);
        unordered_map<string, int> dict;
        for (size_t i = 0; i <= s.length() - 10; ++i) {
            ++dict[s.substr(i, 10)];
        }
        for (const auto& pair : dict) {
            if (pair.second > 1) res.push_back(pair.first);
        }
        return res;
    }
};*/

/* #188 Hard Stock: DP *//*
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        
    }
};*/

/* #189 Using constant space by finding gcd(nums, k) *//*
class Solution {
private:
    int gcd(int a, int b){
        // a is the bigger one
        if (a < b) swap(a, b);
        if (a % b == 0) return b;
        else return gcd(b, a % b);
    }
    
public:
    void rotate(vector<int>& nums, int k) {
        if (k % nums.size() == 0) return;
        int n = int(nums.size());
        int times = gcd(n, k);
        for (int time = 0; time < times; ++time) {
            int startInd = time;
            int nextInd = (time + k) % n;
            while (nextInd != startInd) {
                swap(nums[nextInd], nums[startInd]);
                nextInd = (nextInd + k) % n;
            }
        }
    }
};*/


/* #190 *//*
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t greatest1 = 1 << 31;
        uint32_t smallest1 = 1;
        for (int i = 0; i < 16; ++i, greatest1 = greatest1 >> 1, smallest1 = smallest1 << 1) {
            if ((n & greatest1) == ((n & smallest1) << (31 - 2 * i))) continue;
            if ((n & smallest1) == smallest1){
                n -= smallest1;
                n += greatest1;
            }
            else {
                n += smallest1;
                n -= greatest1;
            }
        }
        return n;
    }
};*/


/* #191 *//*
class Solution {
public:
    int hammingWeight(uint32_t n) {
        uint32_t lower = 1;
        int num1 = 0;
        for (int i = 0; i < 32; ++i, lower = lower << 1) {
            if ((n & lower) == lower) ++num1;
        }
        return num1;
    }
};*/

/* #192 */


int main(){
    Solution S;
    //vector<string> words{"zzyy","zy","zyy"};
    //vector<vector<char>> board{{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}};
    vector<int> nums{10, 2};
    vector<string> words{"cat","cats","and","sand","dog"};
    vector<char> s{'t'};
    return 0;
}
