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

/* 272. Closest Binary Search Tree Value II */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class LessCloseToTarget {
private:
    static double target;
    friend class Solution;
    
public:
    bool operator()(const int& left, const int& right) const {
        cout << "Target: " << target << endl;
        return abs(left - target) < abs(right - target);
    }
};

double LessCloseToTarget::target = 0;

class Solution {
private:
    void recursivelyAdjustTarget(TreeNode* root, priority_queue<int, vector<int>, LessCloseToTarget>& pq, const int& k) {
        if (!root) {
            return;
        }
        
        if (pq.size() < k) {
            pq.push(root->val);
        } else { // == k
            assert(pq.size() == k);
            LessCloseToTarget less;
            if (less(root->val, pq.top())) {
                pq.pop();
                pq.push(root->val);
            }
        }
        
        recursivelyAdjustTarget(root->left, pq, k);
        recursivelyAdjustTarget(root->right, pq, k);
    }
    
public:
    vector<int> closestKValues(TreeNode* root, double target, int k) {
        LessCloseToTarget::target = target;
        priority_queue<int, vector<int>, LessCloseToTarget> pq;
        recursivelyAdjustTarget(root, pq, k);
        
        vector<int> results;
        results.reserve(k);
        while (!pq.empty()) {
            results.push_back(pq.top());
            pq.pop();
        }
        return results;
    }
};

