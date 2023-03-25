struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


/* 298. Binary Tree Longest Consecutive Sequence */
class Solution {
public:
    int longestConsecutive(TreeNode* root, int prevDistance = 0) {
        if (!root) {
            return 0;
        }
        if (!root->left && !root->right) {
            return 1 + prevDistance;
        }
        
        int maxLeftDistance = 0;
        if (root->left) {
            if (root->left->val == root->val + 1) {
                maxLeftDistance = longestConsecutive(root->left, prevDistance + 1);
            } else {
                maxLeftDistance = max(1 + prevDistance, longestConsecutive(root->left));
            }
        }
        
        int maxRightDistance = 0;
        if (root->right) {
            if (root->right->val == root->val + 1) {
                maxRightDistance = longestConsecutive(root->right, prevDistance + 1);
            } else {
                maxRightDistance = max(1 + prevDistance, longestConsecutive(root->right));
            }
        }
        
        return max(maxLeftDistance, maxRightDistance);
    }
};

