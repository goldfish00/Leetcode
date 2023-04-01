/* 305. Number of Islands II */
// idea: mark the map with different integers (same land same integer as possible)
// union find on merge
class Map {
private:
    int numRow;
    int numColumn;
    vector<vector<int>> map;
    
public:
    Map(int m, int n) : numRow(m), numColumn(n) {
        map.resize(m);
        for (auto& row : map) {
            row.resize(n);
        }
    }
    
    int getLeft(int row, int column) {
        if (column == 0) {
            return 0;
        }
        return map[row][column - 1];
    }
    
    int getRight(int row, int column) {
        if (column + 1 == numColumn) {
            return 0;
        }
        return map[row][column + 1];
    }
    
    int getTop(int row, int column) {
        if (row == 0) {
            return 0;
        }
        return map[row - 1][column];
    }
    
    int getBottom(int row, int column) {
        if (row + 1 == numRow) {
            return 0;
        }
        return map[row + 1][column];
    }
    
    int getCell(int row, int column) {
        return map[row][column];
    }
    
    void markCell(int row, int column, int landIndex) {
        map[row][column] = landIndex;
    }
};

class UnionFind {
private:
    vector<int> parentRecord; // parentRecord[i] if the parent of land i+1
    unordered_map<int, deque<int>> childrenRecord; // key: parent index, val: child index
    
public:
    
    int genNewIndex() {
        int nextIndex = (int)parentRecord.size() + 1;
        parentRecord.push_back(nextIndex);
        childrenRecord[nextIndex].push_back(nextIndex);
        return nextIndex;
    }
    
    void merge(int child1, int child2) {
        int parent1 = parentRecord[child1 - 1];
        int parent2 = parentRecord[child2 - 1];
        if (parent1 == parent2) { // do nothing
            return;
        }
        
        int finalParent = min(parent1, parent2);
        int recedingParent = max(parent1, parent2);
        auto toDeleteParentIt = childrenRecord.find(recedingParent);
        deque<int>& toDeleteChildren = toDeleteParentIt->second;
        deque<int>& moreChildren = childrenRecord[finalParent];
        
        while (!toDeleteChildren.empty()) {
            const int& i = toDeleteChildren.front();
            parentRecord[i - 1] = finalParent;
            moreChildren.push_back(i);
            toDeleteChildren.pop_front();
        }
        
        childrenRecord.erase(toDeleteParentIt);
    }
    
    int getParent(int child){
        return parentRecord[child - 1];
    }
    
    int size() {
        return (int)childrenRecord.size();
    }
};

class Solution {
public:
    vector<int> numIslands2(int m, int n, vector<vector<int>>& positions) {
        Map map(m, n);
        UnionFind uf;
        vector<int> answers;
        answers.reserve(positions.size());
        
        for (const auto& pos : positions) {
            if (map.getCell(pos.front(), pos.back()) != 0) { // already marked
                answers.push_back(uf.size());
                continue;
            }
            
            vector<int> adjacentLand;
            int landIndex = 0;
            if ((landIndex = map.getTop(pos.front(), pos.back())) != 0) {
                adjacentLand.push_back(landIndex);
            }
            if ((landIndex = map.getBottom(pos.front(), pos.back())) != 0) {
                adjacentLand.push_back(landIndex);
            }
            if ((landIndex = map.getLeft(pos.front(), pos.back())) != 0) {
                adjacentLand.push_back(landIndex);
            }
            if ((landIndex = map.getRight(pos.front(), pos.back())) != 0) {
                adjacentLand.push_back(landIndex);
            }
            
            if (adjacentLand.size() == 0) { // all water surrounded
                map.markCell(pos.front(), pos.back(), uf.genNewIndex());
                answers.push_back(uf.size());
                continue;
            }
            
            int first = adjacentLand[0];
            for (int i = 1; i < adjacentLand.size(); ++i) {
                uf.merge(first, adjacentLand[i]);
            }
            map.markCell(pos.front(), pos.back(), uf.getParent(first));
            answers.push_back(uf.size());
        }
        
        return answers;
    }
};

