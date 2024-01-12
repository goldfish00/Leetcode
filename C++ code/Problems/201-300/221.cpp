/* 221. Maximal Square */
//class Solution {
//private:
//    bool isOne(const char& c) {
//        return c == '1';
//    }
//
//public:
//    int maximalSquare(vector<vector<char>>& matrix) {
//        int numOnes = 0;
//        for (const auto& row : matrix) {
//            for (const char& c : row) {
//                if (isOne(c)) {
//                    ++numOnes;
//                }
//            }
//        }
//        if (numOnes == 0) {
//            return 0;
//        }
//
//        int maxEdge = 1;
//        int maxEdgePossible = sqrt(numOnes);
//        int numRow = int(matrix.size());
//        int numColumn = int(matrix[0].size());
//
//        for (int iRow = 0; iRow < numRow; ++iRow) {
//            for (int iColumn = 0; iColumn < numColumn; ++iColumn) {
//                if (!isOne(matrix[iRow][iColumn])) {
//                    continue;
//                }
//                if (iRow + maxEdge >= numRow || iColumn + maxEdge >= numColumn) {
//                    continue;
//                }
//
//                int curEdge = 1;
//                bool fail = false;
//                while (iRow + curEdge < numRow && iColumn + curEdge < numColumn) {
//                    // check new row & column
//                    for (int i = 0; i < curEdge; ++i) {
//                        if (!isOne(matrix[iRow + curEdge][iColumn + i]) || !isOne(matrix[iRow + i][iColumn + curEdge])) {
//                            fail = true;
//                            break;
//                        }
//                    }
//                    if (fail) break;
//
//                    // check new corner
//                    if (!isOne(matrix[iRow + curEdge][iColumn + curEdge])) {
//                        break;
//                    }
//
//                    ++curEdge;
//
//                    if (curEdge == maxEdgePossible) {
//                        return curEdge * curEdge;
//                    }
//                    maxEdge = max(maxEdge, curEdge);
//                }
//            }
//        }
//
//        return maxEdge * maxEdge;
//    }
//};
//
//int main() {
//    vector<vector<char>> m{{'1', '1'}, {'1', '1'}};
//    Solution S;
//    S.maximalSquare(m);
//
//    return 0;
//}
