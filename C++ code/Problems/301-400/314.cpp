/* 314. Binary Tree Vertical Order Traversal */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    vector<vector<int>> verticalOrder(TreeNode* root) {
        if (!root) {
            return vector<vector<int>>();
        }
        
        unordered_map<int, vector<int>> nodes;
        deque<pair<int, TreeNode*>> bfsNodes{{0, root}};
        int minIndex = 0;
        
        while (!bfsNodes.empty()) {
            auto curNodePair = bfsNodes.front();
            TreeNode* node = curNodePair.second;
            bfsNodes.pop_front();
            
            nodes[curNodePair.first].push_back(node->val);
            minIndex = min(minIndex, curNodePair.first);
            
            if (node->left) {
                bfsNodes.push_back({curNodePair.first - 1, node->left});
            }
            
            if (node->right) {
                bfsNodes.push_back({curNodePair.first + 1, node->right});
            }
        }
        
        vector<vector<int>> answers;
        answers.resize(nodes.size());
        for (const auto& nodeBund : nodes) {
            answers[nodeBund.first - minIndex] = nodeBund.second;
        }
        return answers;
    }
};
