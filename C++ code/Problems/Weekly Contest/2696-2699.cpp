//class Solution {
//private:
//    const unordered_set<string> removables{"AB", "CD"};
//
//    string genTwoCharStr(const string& s, const int& i, vector<int>& indices) {
//        string res;
//        for (int id = i; id < s.size(); ++id) {
//            if (res.size() == 2) {
//                break;
//            }
//
//            if (s[id] != '0') {
//                res.push_back(s[id]);
//                indices.push_back(id);
//            }
//        }
//
//        return res;
//    }
//
//    int findPrev(const string& s, const int& i) {
//        for (int id = i - 1; id >= 0; --id) {
//            if (s[id] != '0') {
//                return id;
//            }
//        }
//
//        return i;
//    }
//
//public:
//    int minLength(string s) {
//        int len = (int)s.size();
//
//        for (int i = 0; i < s.size() - 1;) {
//            vector<int> ids;
//            auto it = removables.find(genTwoCharStr(s, i, ids));
//            if (it == removables.end()) { // match failed
//                if (ids.size() < 2) {
//                    break;
//                }
//
//                i = ids.back();
//                continue;
//            }
//
//            s[ids.front()] = '0';
//            s[ids.back()] = '0';
//            len -= 2;
//            i = findPrev(s, i);
//        }
//
//        return len;
//    }
//};
//
//int main() {
//    Solution S;
//    S.minLength("CCDAABBDCD");
//
//    return 0;
//}


//class Solution {
//public:
//    string makeSmallestPalindrome(string s) {
//        auto frontIt = s.begin();
//        auto backIt = s.end() - 1;
//
//        while (frontIt != backIt && backIt + 1 != frontIt) {
//            if (*frontIt != *backIt) {
//                char c = min(*frontIt, *backIt);
//                *frontIt = c;
//                *backIt = c;
//            }
//
//            ++frontIt;
//            --backIt;
//        }
//
//        return s;
//    }
//};


//class Solution {
//private:
//    unordered_map<int, unordered_set<int>> meme; // key: num, val: partitioned possibilities
//
//    void genMeme(int num) {
//        if (meme.find(num) != meme.end()) {
//            return;
//        }
//
//        if (num < 10) {
//            meme[num].insert(num);
//            return;
//        }
//
//        auto& possibilities = meme[num];
//        possibilities.insert(num);
//
//        int partitioned = num % 10;
//        int base = 10;
//        num /= 10;
//
//        while (num != 0) {
//            genMeme(partitioned);
//            genMeme(num);
//
//            auto partitionedIt = meme.find(partitioned);
//            auto numIt = meme.find(num);
//
//            for (const int& i : partitionedIt->second) {
//                for (const int& j : numIt->second) {
//                    possibilities.insert(i + j);
//                }
//            }
//
//            partitioned += base * (num % 10);
//            num /= 10;
//            base *= 10;
//        }
//    }
//
//    // whether can find partition of num s.t. partitioned parts sum to target
//    bool canBePartitioned(int target, int num) {
//        genMeme(num);
//        auto it = meme.find(num);
//
//        auto findIt = it->second.find(target);
//        return findIt != it->second.end();
//    }
//
//public:
//    int punishmentNumber(int n) {
//        int res = 0;
//        for (int i = 1; i <= n; ++i) {
//            int pow2 = i * i;
//            if (canBePartitioned(i, pow2)) {
//                res += pow2;
//            }
//        }
//
//        return res;
//    }
//};
//
//int main() {
//    Solution S;
//    cout << S.punishmentNumber(37) << endl;
//
//    return 0;
//}

// TLE
class Solution {
private:
    const int minLen = 1;
    
    struct pathInfo {
    public:
        vector<int> nodes;
        int numUndefinedEdge = 0;
        int definedLength = 0;
        bool hasContradictioin = false;
        
        bool isDefined() {
            return !nodes.empty();
        }
        
        int getLastVisited() {
            return nodes.back();
        }
    };
    
    bool isValid(const pathInfo& path, const int& target) {
        if (path.definedLength + path.numUndefinedEdge > target) {
            return false;
        }
        
        return true;
    }
    
    bool hasContradiction(const pathInfo& path, const int& target) {
        if (path.numUndefinedEdge == 0 && path.definedLength < target) {
            return true;
        }
        
        return false;
    }
    
    void initializeEdgeMap(vector<vector<int>>& edgeMap, const vector<vector<int>>& edges) {
        for (const auto& edgeInfo : edges) {
            edgeMap[edgeInfo[0]][edgeInfo[1]] = edgeInfo.back();
            edgeMap[edgeInfo[1]][edgeInfo[0]] = edgeInfo.back();
        }
    }
    
    void updateShortestPath(pathInfo& shortestPath, const pathInfo& curPath, const int& target) {
        if (!shortestPath.isDefined()) {
            shortestPath = curPath;
            return;
        }
        
        if (shortestPath.hasContradictioin) {
            return;
        }
                
        if (hasContradiction(shortestPath, target) || hasContradiction(curPath, target)) {
            shortestPath.hasContradictioin = true;
            return;
        }
        
        if (!isValid(curPath, target)) {
            return;
        }
        
        if (!isValid(shortestPath, target)
            || shortestPath.numUndefinedEdge > curPath.numUndefinedEdge
            || (shortestPath.numUndefinedEdge == curPath.numUndefinedEdge &&
                shortestPath.definedLength > curPath.definedLength)) {
            shortestPath = curPath;
        }
    }
    
    void findShortestPath(pathInfo& shortestPath, pathInfo& curPath, const vector<vector<int>>& edgeMap, const int& dest, const int& target, unordered_set<int>& vistedNodes) {
        const vector<int>& edgeWeights = edgeMap[curPath.getLastVisited()];
        for (int i = 0; i < edgeWeights.size(); ++i) {
            if (curPath.hasContradictioin) {
                return;
            }
            
            int weight = edgeWeights[i];
            if (weight == 0) {
                continue;
            }
            
            if (vistedNodes.find(i) != vistedNodes.end()) {
                continue;
            }
            
            if (weight == -1) {
                ++curPath.numUndefinedEdge;
            } else {
                int tentativeWeight = curPath.definedLength + weight;
                if (tentativeWeight > target) {
                    continue;
                }
                curPath.definedLength = tentativeWeight;
            }
            vistedNodes.insert(i);
            curPath.nodes.push_back(i);
            
            if (i == dest) {
                updateShortestPath(shortestPath, curPath, target);
            } else {
                findShortestPath(shortestPath, curPath, edgeMap, dest, target, vistedNodes);
            }
            
            vistedNodes.erase(i);
            curPath.nodes.pop_back();
            if (weight == -1) {
                --curPath.numUndefinedEdge;
            } else {
                curPath.definedLength -= weight;
            }
        }
    }
    
    // sum > numEdge
    vector<int> genPossibleEdgeWeights(const int& numEdge, const int& sum) {
        if (sum == 0) {
            return vector<int>();
        }
        
        vector<int> res(numEdge, sum / numEdge);
        int numOneMore = sum % numEdge;
        
        for (int i = 0; i < numOneMore; ++i) {
            ++res[i];
        }
        
        return res;
    }
    
public:
    vector<vector<int>> modifiedGraphEdges(int n, vector<vector<int>>& edges, int source, int destination, int target) {
        vector<vector<int>> edgeMap(n, vector<int>(n, 0));
        initializeEdgeMap(edgeMap, edges);
        
        pathInfo shortestPath, curPath;
        unordered_set<int> visitedNodes{source};
        curPath.nodes.push_back(source);
        findShortestPath(shortestPath, curPath, edgeMap, destination, target, visitedNodes);
        
        if (!shortestPath.isDefined() /* cannot find the path */
            || shortestPath.hasContradictioin /* exist defined shorter path already */
            || shortestPath.definedLength + shortestPath.numUndefinedEdge > target /* shortest path too long*/
            || (shortestPath.numUndefinedEdge == 0 && shortestPath.definedLength < target) /* shortest path too short */) { // impossible
            return vector<vector<int>>();
        }
        
        // fill the number
        int weightFillIndex = shortestPath.numUndefinedEdge - 1;
        int weightSum = target - shortestPath.definedLength;
        for (auto it = shortestPath.nodes.begin() + 1; it != shortestPath.nodes.end(); ++it) {
            int node1 = *it;
            int node2 = *(it - 1);
            if (edgeMap[node1][node2] != -1) {
                continue;
            }
            
            if (node1 > node2) {
                swap(node1, node2);
            }
            
            if (weightFillIndex != 0) {
                edgeMap[node1][node2] = 1;
                --weightSum;
                --weightFillIndex;
            } else {
                edgeMap[node1][node2] = weightSum;
            }
        }
        
        // generate res
        for (auto& edge : edges) {
            if (edge.back() != -1) {
                continue;
            }
            
            int node1 = edge[0];
            int node2 = edge[1];
            if (node1 > node2) {
                swap(node1, node2);
            }
            
            int weight = edgeMap[node1][node2];
            if (weight != -1) {
                edge.back() = weight;
            } else {
                edge.back() = target;
            }
        }
        
        return edges;
    }
};

int main() {
    Solution S;

//    vector<vector<int>> edges{
//        {4,1,-1},
//        {2,0,-1},
//        {0,3,-1},
//        {4,3,-1}
//    };
//    S.modifiedGraphEdges(5, edges, 0, 1, 5);
    
//    vector<vector<int>> edges{
//        {0,1,-1},
//        {1,2,-1},
//        {3,1,-1},
//        {3,0,2},
//        {0,2,5}
//    };
//    S.modifiedGraphEdges(4, edges, 2, 3, 8);
    
//    vector<vector<int>> edges{
//        {1,0,4},
//        {1,2,3},
//        {2,3,5},
//        {0,3,-1}
//    };
//    S.modifiedGraphEdges(4, edges, 0, 2, 6);
    
    vector<vector<int>> edges{
        {{3,0,1},{2,1,-1},{2,3,6},{4,2,6},{1,3,2},{2,0,7},{0,4,10},{0,1,6}}
    };
    S.modifiedGraphEdges(5, edges, 1, 4, 14);
    
//    vector<vector<int>> edges{{0,1,5},{1,2,7},{2,3,7},{3,1,9},{3,0,-1},{0,2,-1}};
//    S.modifiedGraphEdges(4, edges, 2, 3, 7);
    
//    vector<vector<int>> edges{{0,1,-1},{3,1,4},{4,2,3},{3,4,5},{1,4,6},{0,3,8},{2,1,-1},{3,2,2}};
//    S.modifiedGraphEdges(5, edges, 0, 2, 6);
    
    
    return 0;
}
