#include <iostream>
// unordered_multiset here
#include <unordered_set>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>
#include <assert.h>
#include <set>
#include <unordered_map>
using namespace std;

/* 6314. Count Number of Possible Root Nodes */
/* Alice has an undirected tree with n nodes labeled from 0 to n - 1. The tree is represented as a 2D integer array edges of length n - 1 where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.

Alice wants Bob to find the root of the tree. She allows Bob to make several guesses about her tree. In one guess, he does the following:

Chooses two distinct integers u and v such that there exists an edge [u, v] in the tree.
He tells Alice that u is the parent of v in the tree.
Bob's guesses are represented by a 2D integer array guesses where guesses[j] = [uj, vj] indicates Bob guessed uj to be the parent of vj.

Alice being lazy, does not reply to each of Bob's guesses, but just says that at least k of his guesses are true.

Given the 2D integer arrays edges, guesses and the integer k, return the number of possible nodes that can be the root of Alice's tree. If there is no such tree, return 0.
 */
class Solution {
private:
    void constructTreeMap(int root, const unordered_map<int, set<int>>& connectedNodes, unordered_map<int, int>& treeMap) {
        // dfs: if connected node is not current node's parent, then it must be the current node's child
        auto it = connectedNodes.find(root);
        if (it == connectedNodes.end()) {
            return;
        }
        
        auto parentIt = treeMap.find(root);
        int parentIndex = -1;
        if (parentIt != treeMap.end()) {
            parentIndex = parentIt->second;
        }
        
        for (const int& connectedNode : it->second) {
            if (connectedNode == parentIndex) {
                continue;
            }
            treeMap[connectedNode] = root;
            constructTreeMap(connectedNode, connectedNodes, treeMap);
        }
    }
        
    int correctGuessNum(const vector<vector<int>>& guesses, const unordered_map<int, int>& treeMap) {
        int rightGuessCount = 0;
        for (const auto& pairs : guesses) {
            auto it = treeMap.find(pairs.back());
            if (it == treeMap.end()) {
                continue;
            }
            if (it->second == pairs.front()) {
                ++rightGuessCount;
            }
        }
        return rightGuessCount;
    }
    
public:
    int rootCount(vector<vector<int>>& edges, vector<vector<int>>& guesses, int k) {
        unordered_map<int, set<int>> connectedNodes;
        for (const auto& pair : edges) {
            connectedNodes[pair.front()].insert(pair.back());
            connectedNodes[pair.back()].insert(pair.front());
        }
        
        unordered_map<int, int> treeMap; // key is the child and value is the parent
        int numNode = (int)edges.size() + 1;
        int count = 0;
        
        for (int rootIndex = 0; rootIndex < numNode; ++rootIndex) {
            treeMap.clear();
            constructTreeMap(rootIndex, connectedNodes, treeMap);
            
            if (correctGuessNum(guesses, treeMap) >= k) {
                ++count;
            }
        }
        
        return count;
    }
};

int main() {
    Solution S;
    vector<vector<int>> edges{{0, 1}, {1, 2}, {1, 3}, {4, 2}};
    vector<vector<int>> guesses{{1, 3}, {0, 1}, {1, 0}, {2, 4}};
    S.rootCount(edges, guesses, 3);
    return 0;
}

