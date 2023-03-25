/* 296. Best Meeting Point */
class Solution {
private:
    int getTotalDistance(vector<int>& ones) {
        if (ones.size() == 1) {
            return 0;
        }
        
        sort(ones.begin(), ones.end());
        int minDistance = 0;
        for (auto frontIt = ones.begin(), backIt = ones.end() - 1; frontIt != backIt + 1 && frontIt != backIt; ++frontIt, --backIt) {
            minDistance += *backIt - *frontIt;
        }
        
        return minDistance;
    }
    
public:
    int minTotalDistance(vector<vector<int>>& grid) {
        size_t numRows = grid.size();
        size_t numColumns = grid[0].size();
        vector<int> horizontalOnes;
        vector<int> verticalOnes;
        
        for (int rowIndex = 0; rowIndex < numRows; ++rowIndex) {
            for (int columnIndex = 0; columnIndex < numColumns; ++columnIndex) {
                if (grid[rowIndex][columnIndex] == 1) {
                    verticalOnes.push_back(rowIndex);
                    horizontalOnes.push_back(columnIndex);
                }
            }
        }
        
        return getTotalDistance(verticalOnes) + getTotalDistance(horizontalOnes);
    }
};

int main() {
//    vector<vector<int>> grid{
//        {1,0,0,0,1},
//        {0,0,0,0,0},
//        {0,0,1,0,0}};
    vector<vector<int>> grid {
        {1, 1}
    };
    Solution S;
    cout << S.minTotalDistance(grid) << endl;
    return 0;
}
