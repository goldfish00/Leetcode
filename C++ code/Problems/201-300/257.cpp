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

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/* 257. Binary Tree Paths */
class Solution {
private:
    string genPath(const vector<int>& values) {
        auto it = values.begin();
        string s;
        s.reserve(3 * values.size());
        s.append(to_string(*it));
        ++it;
        
        while (it != values.end()) {
            s.append("->");
            s.append(to_string(*it));
            ++it;
        }
        return s;
    }
    
    void backTrack(TreeNode* root, vector<int>& values, vector<string>& results) {
        if (!root->left && !root->right) {
            values.push_back(root->val);
            results.push_back(genPath(values));
            values.pop_back();
            return;
        }
        
        values.push_back(root->val);
        if (root->left) {
            backTrack(root->left, values, results);
        }
        if (root->right) {
            backTrack(root->right, values, results);
        }
        values.pop_back();
    }
    
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> results;
        if (!root) {
            return results;
        }
        
        vector<int> values;
        backTrack(root, values, results);
        return results;
    }
};

