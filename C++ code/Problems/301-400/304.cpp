/* 304. Range Sum Query 2D - Immutable */
class NumMatrix {
private:
    vector<vector<int>> rectSum;
    
    int getSum(int row, int column) {
        if (row < 0 || column < 0) {
            return 0;
        }
        return rectSum[row][column];
    }
    
public:
    NumMatrix(vector<vector<int>>& matrix) {
        rectSum = matrix;
        for (auto& row : rectSum) {
            for (int i = 1; i < row.size(); ++i) {
                row[i] += row[i - 1];
            }
        }
        
        for (int j = 0; j < rectSum[0].size(); ++j) {
            for (int i = 1; i < rectSum.size(); ++i) {
                rectSum[i][j] += rectSum[i - 1][j];
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        return getSum(row2, col2) - getSum(row1 - 1, col2) - getSum(row2, col1 - 1) + getSum(row1 - 1, col1 - 1);
    }
};

int main() {
    vector<vector<int>> matrix{{3,0,1,4,2},{5,6,3,2,1},{1,2,0,1,5},{4,1,0,1,7},{1,0,3,0,5}};
    NumMatrix n(matrix);
    n.sumRegion(1, 1, 2, 2);
    
    return 0;
}
