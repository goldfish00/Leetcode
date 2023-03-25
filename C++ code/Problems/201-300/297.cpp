/* 297. Serialize and Deserialize Binary Tree */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


// refer to stringstream here: https://cplusplus.com/reference/sstream/stringstream/stringstream/
class Codec {
private:
    TreeNode* genNode(const string& val) {
        if (val == "n") {
            return nullptr;
        }
        return new TreeNode(stoi(val));
    }
    
    void addNodeToQueue(TreeNode* node, deque<TreeNode*>& nodes) {
        if (node) {
            nodes.push_back(node);
        }
    }
    
public:

    // Encodes a tree to a single string.
    // we use 'n' to indicate that there is a nullptr in the place
    // a tree with nodes 1 2 null will be serialized into 1 2 n n n
    // BFS method
    string serialize(TreeNode* root) {
        stringstream ss;
        deque<TreeNode*> nodes{root};
        
        while (!nodes.empty()) {
            TreeNode* currentNode = nodes.front();
            nodes.pop_front();
            
            if (!currentNode) {
                ss << "n ";
                continue;
            }
            
            ss << currentNode->val << " ";
            nodes.push_back(currentNode->left);
            nodes.push_back(currentNode->right);
        }
        
        return ss.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        stringstream ss(data);
        deque<TreeNode*> nodes;
        
        string val;
        ss >> val;
        TreeNode* root = genNode(val);
        addNodeToQueue(root, nodes);
        
        while (!nodes.empty()) {
            TreeNode* currentNode = nodes.front();
            nodes.pop_front();
            
            ss >> val;
            currentNode->left = genNode(val);
            ss >> val;
            currentNode->right = genNode(val);
            
            addNodeToQueue(currentNode->left, nodes);
            addNodeToQueue(currentNode->right, nodes);
        }
        
        return root;
    }
};

// refer to stringstream here: https://cplusplus.com/reference/sstream/stringstream/stringstream/
// compared with the previous solution:
// root 1, 2 will be encoded into 1, 2, n, n, n
// I try to rid of trailing zeros in this solution
class Codec {
private:
    TreeNode* genNode(const string& val) {
        if (val.empty() || val == "n") {
            return nullptr;
        }
        return new TreeNode(stoi(val));
    }
    
    void addNodeToQueue(TreeNode* node, deque<TreeNode*>& nodes) {
        if (node) {
            nodes.push_back(node);
        }
    }
    
public:

    // Encodes a tree to a single string.
    // we use 'n' to indicate that there is a nullptr in the place
    // a tree with nodes 1 2 will be serialized into 1 2 n n n
    // BFS method
    string serialize(TreeNode* root) {
        stringstream ss;
        deque<TreeNode*> nodes{root};
        size_t numNullNodes = root ? 0 : 1;
        
        while (!nodes.empty()) {
            if (numNullNodes == nodes.size()) {
                break;
            }
            
            TreeNode* currentNode = nodes.front();
            nodes.pop_front();
            
            if (!currentNode) {
                ss << "n ";
                --numNullNodes;
                continue;
            }
            
            ss << currentNode->val << " ";
            nodes.push_back(currentNode->left);
            nodes.push_back(currentNode->right);
            
            if (!currentNode->left) {
                ++numNullNodes;
            }
            if (!currentNode->right) {
                ++numNullNodes;
            }
        }
        
        return ss.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        stringstream ss(data);
        deque<TreeNode*> nodes;
        
        string val;
        ss >> val;
        TreeNode* root = genNode(val);
        addNodeToQueue(root, nodes);
        
        while (!nodes.empty()) {
            TreeNode* currentNode = nodes.front();
            nodes.pop_front();
            
            if (ss >> val) {
                currentNode->left = genNode(val);
                addNodeToQueue(currentNode->left, nodes);
            } else {
                return root;
            }
            
            if (ss >> val) {
                currentNode->right = genNode(val);
                addNodeToQueue(currentNode->right, nodes);
            } else {
                return root;
            }
        }
        
        return root;
    }
};

class Codec {
private:
    string nullS{"null"};
    
    void writeSS(stringstream& ss, TreeNode* node){
        ss << " ";
        if (!node) ss << nullS;
        else ss << node->val;
    }
    
    // return true on success; return false if a nullptr is met
    void getNode(const string s, TreeNode*& node){
        if (s == nullS) node = nullptr;
        else node = new TreeNode(stoi(s));
    }
    
    
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (!root) return string();
        
        stringstream ss;
        ss << root->val;
        deque<TreeNode*> bfsTraverse;
        bfsTraverse.push_back(root);
        
        while (!bfsTraverse.empty()) {
            TreeNode*  curr = bfsTraverse.front();
            bfsTraverse.pop_front();
            if (curr->left) bfsTraverse.push_back(curr->left);
            if (curr->right) bfsTraverse.push_back(curr->right);
            writeSS(ss, curr->left);
            writeSS(ss, curr->right);
        }
        
        return ss.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        stringstream ss(data);
        string word;
        // read the root
        TreeNode* root = nullptr;
        if (ss >> word) getNode(word, root);
        if (!root) return root;
        
        // dfs
        deque<TreeNode*> bfsTraverse;
        bfsTraverse.push_back(root);
        while (!bfsTraverse.empty()) {
            TreeNode* curr = bfsTraverse.front();
            bfsTraverse.pop_front();
            if (ss >> word) getNode(word, curr->left);
            else break;
            if (ss >> word) getNode(word, curr->right);
            else break;
            
            if (curr->left) bfsTraverse.push_back(curr->left);
            if (curr->right) bfsTraverse.push_back(curr->right);
        }
        
        return root;
    }
};

int main() {
    Codec C;
    TreeNode* node = new TreeNode(1, new TreeNode(2), nullptr);
    string s = C.serialize(node);
    cout << s << endl;
    TreeNode* root = C.deserialize(s);
    return 0;
}
