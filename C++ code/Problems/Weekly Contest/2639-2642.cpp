/* 6333. Find the Width of Columns of a Grid */
//class Solution {
//public:
//    vector<int> findColumnWidth(vector<vector<int>>& grid) {
//        int numRows = int(grid.size());
//        int numCols = int(grid[0].size());
//        vector<int> res;
//        res.reserve(numCols);
//
//        for (int column = 0; column < numCols; ++column) {
//            int maxLen = 0;
//            for (int row = 0; row < numRows; ++row) {
//                maxLen = max(maxLen, (int)to_string(grid[row][column]).size());
//            }
//            res.push_back(maxLen);
//        }
//
//        return res;
//    }
//};

/* 6334. Find the Score of All Prefixes of an Array */
//class Solution {
//public:
//    vector<long long> findPrefixScore(vector<int>& nums) {
//        vector<long long> res;
//        res.resize(nums.size());
//
//        res[0] = nums[0];
//        // first iter: find the largest num up to index i
//        for (int i = 1; i < nums.size(); ++i) {
//            res[i] = max((long long)nums[i], res[i - 1]);
//        }
//        // second iter: find conversion
//        for (int i = 0; i < nums.size(); ++i) {
//            res[i] += nums[i];
//        }
//        // third iter: calculate score
//        for (int i = 1; i < nums.size(); ++i) {
//            res[i] += res[i - 1];
//        }
//
//        return res;
//    }
//};

/* 6335. Cousins in Binary Tree II */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// BFS method
//class Solution {
//public:
//    TreeNode* replaceValueInTree(TreeNode* root) {
//        deque<pair<TreeNode*, TreeNode*>> nodesWithParent1; // first node; second: parent
//        deque<pair<TreeNode*, TreeNode*>> nodesWithParent2;
//        unordered_map<TreeNode*, int> parentSum;
//        int totalSum = 0;
//
//        nodesWithParent1.push_back({root, nullptr}); // initialize
//        while (!nodesWithParent1.empty()) {
//            // first iter: calculate sum
//            for (const auto& nodeWithParent : nodesWithParent1) {
//                int nodeVal = nodeWithParent.first->val;
//                totalSum += nodeVal;
//                parentSum[nodeWithParent.second] += nodeVal;
//            }
//
//            // second iter: assign val, clear current level and prepare next level
//            while (!nodesWithParent1.empty()) {
//                auto nodeWithParent = nodesWithParent1.front();
//                nodesWithParent1.pop_front();
//
//                TreeNode* node = nodeWithParent.first;
//                if (node->left) {
//                    nodesWithParent2.push_back({node->left, node});
//                }
//                if (node->right) {
//                    nodesWithParent2.push_back({node->right, node});
//                }
//
//                node->val = totalSum - parentSum[nodeWithParent.second];
//            }
//
//            swap(nodesWithParent1, nodesWithParent2);
//            parentSum.clear();
//            totalSum = 0;
//        }
//
//        return root;
//    }
//};

/* 6336. Design Graph With Shortest Path Calculator */
// TLE
//class Graph {
//private:
//    int numNode;
//    unordered_map<int, deque<pair<int, int>/* first: node, second: len*/>> edgeMap;
//
//    bool canFind(int node1, int node2, unordered_set<int>& visitedNode, int prevPathLen, int& pathLen) {
//        auto nextNodesIt = edgeMap.find(node1);
//        if (nextNodesIt == edgeMap.end()) {
//            return false;
//        }
//
//        if (prevPathLen > pathLen) {
//            return false;
//        }
//
//        auto& nextNodes = nextNodesIt->second;
//        bool hasFound = false;
//        for (const auto& nodeInfo : nextNodes) {
//            if (nodeInfo.first == node2) {
//                hasFound = true;
//                pathLen = min(pathLen, prevPathLen + nodeInfo.second);
//                continue;
//            }
//            if (visitedNode.find(nodeInfo.first) != visitedNode.end()) {
//                continue;
//            }
//
//            visitedNode.insert(nodeInfo.first);
//            if (canFind(nodeInfo.first, node2, visitedNode, prevPathLen + nodeInfo.second, pathLen)) {
//                hasFound = true;
//            }
//            visitedNode.erase(nodeInfo.first);
//        }
//
//        if (!hasFound) {
//
//        }
//        return hasFound;
//    }
//
//public:
//    Graph(int n, vector<vector<int>>& edges): numNode(n) {
//        for (const auto& edgeInfo : edges) {
//            edgeMap[edgeInfo[0]].push_back({edgeInfo[1], edgeInfo[2]});
//        }
//    }
//
//    void addEdge(vector<int> edge) {
//        edgeMap[edge[0]].push_back({edge[1], edge[2]});
//    }
//
//    int shortestPath(int node1, int node2) {
//        if (node1 == node2) {
//            return 0;
//        }
//
//        int pathLen = INT_MAX;
//        unordered_set<int> visitedNode;
//        visitedNode.insert(node1);
//        if (!canFind(node1, node2, visitedNode, 0, pathLen)) {
//            return -1;
//        }
//        return pathLen;
//    }
//};

// DP: passed
class Graph {
private:
    int n;
    vector<vector<int>> shortestPathMeme; // meme[i][j] marks the shortest distance from node i to node j

public:
    Graph(int n, vector<vector<int>>& edges): n(n) {
        for (int i = 0; i < n; ++i) {
            shortestPathMeme.push_back(vector<int>(n, -1));
            shortestPathMeme[i][i] = 0;
        }
        
        for (vector<int> edge : edges) {
            addEdge(edge);
        }
    }
    
    void addEdge(vector<int> edge) {
        int node1 = edge[0];
        int node2 = edge[1];
        int newLen = edge[2];
        int curLen = shortestPath(node1, node2);
        
        if (curLen >= 0 && curLen <= newLen) { // do nothing is no update is not needed
            return;
        }
        
        for (int i = 0; i < n; ++i) {
            int toNode1 = shortestPath(i, node1);
            if (toNode1 == -1) { // skip if cannot reach
                continue;
            }
            for (int j = 0; j < n; ++j) {
                int fromNode2 = shortestPath(node2, j);
                if (fromNode2 == -1) { // skip if cannot reach
                    continue;
                }
                // try update
                int iToj = shortestPath(i, j);
                int newIToJLen = toNode1 + newLen + fromNode2;
                if (iToj == -1 || iToj > newIToJLen) {
                    shortestPathMeme[i][j] = newIToJLen;
                }
            }
        }
    }
    
    int shortestPath(int node1, int node2) {
        return shortestPathMeme[node1][node2];
    }
};


int main() {
    vector<vector<int>> edges{
        {11,6,84715},{7,9,764823},{6,0,315591},{1,4,909432},{6,5,514907},{9,6,105610},{3,10,471042},{7,10,348752},{5,11,715628},{6,1,973999},{8,7,593929},{7,6,64688},{6,4,741734},{10,1,894247},{9,7,81181},{2,11,75418},{12,2,85431},{7,2,260306},{11,9,640614},{2,3,648804},{4,12,568023},{0,8,730096},{9,11,633474},{3,6,390214},{1,10,117955},{9,8,222602},{10,7,689294}, {1,2,36450},{8,0,709628},{2,4,30185},{12,1,21696},{1,8,2553}, {4,6,2182},{7,5,206},{5,7,140}
    };
    Graph g(13, edges);
//    cout << g.shortestPath(3, 2) << endl;
//    cout << g.shortestPath(0, 3) << endl;
    cout << g.shortestPath(12, 4) << endl;

    return 0;
}
