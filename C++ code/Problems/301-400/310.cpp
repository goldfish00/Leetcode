/* 310. Minimum Height Trees */

/* TLE */
class Solution {
private:
    int findHeightWithBacktrack(int parent, int root, int prevHeight, const unordered_map<int, set<int>>& biEdges, int currentMin) {
        auto it = biEdges.find(root);
        if (it->second.size() == 1 && *(it->second.begin()) == parent) {
            return 1;
        }
        
        int height = 0;
        for (const int& connected : it->second) {
            if (connected == parent) {
                continue;
            }
            height = max(height, findHeightWithBacktrack(root, connected, prevHeight + 1, biEdges, currentMin));
            if (height > currentMin) {
                return currentMin + 1;
            }
        }
        return prevHeight + 1 + height;
    }
    
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        vector<int> nodes;

        if (n < 3) {
            nodes.resize(n);
            iota(nodes.begin(), nodes.end(), 0);
            return nodes;
        }
        
        unordered_map<int, set<int>> biEdges;
        for (const auto& edge : edges) {
            biEdges[edge.front()].insert(edge.back());
            biEdges[edge.back()].insert(edge.front());
        }
        
        int minHeight = INT_MAX;
        for (int i = 0; i < n; ++i) {
            int height = findHeightWithBacktrack(-1, i, 0, biEdges, minHeight);
            if (height < minHeight) {
                minHeight = height;
                nodes.clear();
                nodes.push_back(i);
            } else if (height == minHeight) {
                nodes.push_back(i);
            }
        }
        return nodes;
    }
};
