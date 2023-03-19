/* 286. Walls and Gates */
class Solution {
private:
    static size_t numRow;
    static size_t numColumn;
    
    class PairHash{
    public:
        size_t operator()(const pair<size_t, size_t>& coor) const {
            return coor.first ^ coor.second;
        }
    };
    
    static bool isLeftValid(const pair<size_t, size_t>& coor) {
        return coor.second != 0;
    }
    
    static bool isRightValid(const pair<size_t, size_t>& coor) {
        return coor.second + 1 != numColumn;
    }
    
    static bool isTopValid(const pair<size_t, size_t>& coor) {
        return coor.first != 0;
    };
    
    static bool isButtomValid(const pair<size_t, size_t>& coor) {
        return coor.first + 1 != numRow;
    }
    
    static pair<size_t, size_t> getLeft(const pair<size_t, size_t>& coor) {
        return {coor.first, coor.second - 1};
    }
    
    static pair<size_t, size_t> getRight(const pair<size_t, size_t>& coor) {
        return {coor.first, coor.second + 1};
    }
    
    static pair<size_t, size_t> getTop(const pair<size_t, size_t>& coor) {
        return {coor.first - 1, coor.second};
    }

    static pair<size_t, size_t> getButtom(const pair<size_t, size_t>& coor) {
        return {coor.first + 1, coor.second};
    }
    
    void tryMark(function<bool(const pair<size_t, size_t>&)> isValid, function<pair<size_t, size_t>(const pair<size_t, size_t>&)> getNext, vector<vector<int>>& rooms, unordered_set<pair<size_t, size_t>, PairHash>& visitedCoor, deque<pair<size_t, size_t>>& lastCoor, const pair<size_t, size_t>& currentCoor, int step) {
        if (isValid(currentCoor)) {
            auto nextCoor = getNext(currentCoor);
            if (visitedCoor.find(nextCoor) == visitedCoor.end()) {
                rooms[nextCoor.first][nextCoor.second] = step;
                visitedCoor.insert(nextCoor);
                lastCoor.push_back(nextCoor);
            }
        }
    }
    
    void markWithBFS(vector<vector<int>>& rooms, deque<pair<size_t, size_t>>& lastCoor, unordered_set<pair<size_t, size_t>, PairHash>& visitedCoor, int step) {
        if (lastCoor.empty()) {
            return;
        }
        
        size_t roundNum = lastCoor.size();
        for (size_t i = 0; i < roundNum; ++i) {
            pair<size_t, size_t>& currentCoor = lastCoor.front();
            tryMark(isLeftValid, getLeft, rooms, visitedCoor, lastCoor, currentCoor, step);
            tryMark(isRightValid, getRight, rooms, visitedCoor, lastCoor, currentCoor, step);
            tryMark(isTopValid, getTop, rooms, visitedCoor, lastCoor, currentCoor, step);
            tryMark(isButtomValid, getButtom, rooms, visitedCoor, lastCoor, currentCoor, step);
            
            lastCoor.pop_front();
        }
        
        markWithBFS(rooms, lastCoor, visitedCoor, step + 1);
    }
    
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        numRow = rooms.size();
        numColumn = rooms[0].size();
        // coordinates of last visites coordinates
        deque<pair<size_t, size_t>> lastCoor;
        unordered_set<pair<size_t, size_t>, PairHash> visitedCoor;
        
        // intialize with coor of gates
        for (size_t i = 0; i < numRow; ++i) {
            for (size_t j = 0; j < numColumn; ++j) {
                if (rooms[i][j] == 0) {
                    lastCoor.push_back({i, j});
                    visitedCoor.insert({i, j});
                } else if (rooms[i][j] == -1) {
                    visitedCoor.insert({i, j});
                }
            }
        }
        
        markWithBFS(rooms, lastCoor, visitedCoor, 1);
    }
};

size_t Solution::numRow = 0;
size_t Solution::numColumn = 0;

int main() {
    vector<vector<int>> rooms{
        {2147483647,-1,0,2147483647},
        {2147483647,2147483647,2147483647,-1},
        {2147483647,-1,2147483647,-1},
        {0,-1,2147483647,2147483647}
    };
    Solution S;
    S.wallsAndGates(rooms);
    return 0;
}

