/* 285. Inorder Successor in BST */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
private:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p, bool &hasFound) {
        if (!root) {
            return nullptr;
        }
        
        TreeNode *node = inorderSuccessor(root->left, p, hasFound);
        if (node) {
            return node;
        }
        
        if (hasFound) {
            return root;
        }
        
        if (root == p) {
            hasFound = true;
        }
        
        return inorderSuccessor(root->right, p, hasFound);
    }
    
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        bool hasFound = false;
        return inorderSuccessor(root, p, hasFound);
    }
};

