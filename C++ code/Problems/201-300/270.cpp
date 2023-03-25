using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/* 270. Closest Binary Search Tree Valu */
class Solution {
private:
    int getCloser(const int left, const int right, const double& target) {
        if (abs(left - target) < abs(right - target)) {
            return left;
        }
        return right;
    }
    
public:
    int closestValue(TreeNode* root, double target) {
        double distance = abs(root->val - target);
        if (distance < 0.5) {
            return root->val;
        }
        
        if (target < root->val) {
            if (root->left) {
                return getCloser(closestValue(root->left, target), root->val, target);
            } else {
                return root->val;
            }
        }
        
        // target > root->val
        if (root->right) {
            return getCloser(closestValue(root->right, target), root->val, target);
        } else return root->val;
    }
};
