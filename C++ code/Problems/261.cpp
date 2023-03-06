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

/* 261. Graph Valid Tree */
// Check from very node that there is not a cycle and have traversed all the nodes
class Solution {
private:
    bool isValidFrom(int lastNode, int currentNode, const vector<vector<int>>& edgesByPoint, unordered_set<int>& nodes, set<int>& unvisitedNode) {
        const vector<int>& adjacentNodes = edgesByPoint[currentNode];
        if (adjacentNodes.size() == 0) {
            if (nodes.empty()) {
                return false;
            } else return true;
        }
        
        nodes.insert(currentNode);
        unvisitedNode.erase(currentNode);
        for (const int& adjacentNode : adjacentNodes) {
            if (adjacentNode == lastNode) {
                continue;
            }
            if (nodes.find(adjacentNode) != nodes.end()) {
                return false;
            }
            if (!isValidFrom(currentNode, adjacentNode, edgesByPoint, nodes, unvisitedNode)) {
                return false;
            }
        }
        nodes.erase(currentNode);
        
        return true;
    }
    
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        if (edges.size() == 0) {
            return n == 1;
        }
        if (edges.size() < n - 1) {
            return false;
        }
        // the i'th element contains all points connected to point i
        vector<vector<int>> edgesByPoint;
        edgesByPoint.resize(n);
        for (const auto& edge : edges) {
            edgesByPoint[edge.front()].push_back(edge.back());
            edgesByPoint[edge.back()].push_back(edge.front());
        }
        
        unordered_set<int> nodes;
        set<int> unvisitedNodes;
        for (int i = 0; i < n; ++i) {
            unvisitedNodes.insert(i);
        }
        
        return isValidFrom(-1, 0, edgesByPoint, nodes, unvisitedNodes) && unvisitedNodes.empty();
    }
};

int main() {
    vector<vector<int>> edges;
    Solution S;
    S.validTree(1, edges);
    
    return 0;
}
