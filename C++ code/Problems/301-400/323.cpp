/* 323. Number of Connected Components in an Undirected Graph */
class Solution {
private:
    void searchAndMark(int node, const unordered_map<int, forward_list<int>>& uniEdges, vector<bool>& vistedStates) {
        if (vistedStates[node]) { // already visited
            return;
        }
        vistedStates[node] = true;
        
        auto it = uniEdges.find(node);
        if (it == uniEdges.end()) {
            return;
        }
        for (const int& connectedNode : it->second) {
            searchAndMark(connectedNode, uniEdges, vistedStates);
        }
    }
    
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        vector<bool> visitedStates(n, false);
        unordered_map<int, forward_list<int>> uniEdges;
        for (const vector<int>& edge : edges) {
            if (edge.front() == edge.back()) {
                continue;
            }
            uniEdges[edge.front()].push_front(edge.back());
            uniEdges[edge.back()].push_front(edge.front());
        }
        
        int numConnected = 0;
        for (int i = 0; i < n; ++i) {
            if (visitedStates[i]) {
                continue;
            }
            
            ++numConnected;
            searchAndMark(i, uniEdges, visitedStates);
        }
        return numConnected;
    }
};

int main() {
    vector<vector<int>> edges{{0, 1}};
    Solution S;
    S.countComponents(2, edges);
    
    return 0;
}
