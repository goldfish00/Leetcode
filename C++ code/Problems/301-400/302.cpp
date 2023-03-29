/* 302. Smallest Rectangle Enclosing Black Pixels */
class Solution {
private:
    
    int getArea(const pair<int, int>& buttomLeftPt, const pair<int, int>& topRightPt) const {
        return (topRightPt.first - buttomLeftPt.first + 1) * (topRightPt.second - buttomLeftPt.second + 1);
    }
    
    pair<int, int> markLeft(vector<vector<char>>& image, const pair<int, int>& pt) const {
        if (pt.first == 0) {
            return {-1, 0};
        }
        
        pair<int, int> left{pt.first - 1, pt.second};;
        if (image[left.first][left.second] != '1') {
            return {-1, 0};
        }
        
        image[left.first][left.second] = '2';
        return left;
    }
    
    pair<int, int> markRight(vector<vector<char>>& image, const pair<int, int>& pt) const {
        if (pt.first + 1 == image.size()) {
            return {-1, 0};
        }
        
        pair<int, int> right{pt.first + 1, pt.second};;
        if (image[right.first][right.second] != '1') {
            return {-1, 0};
        }
        
        image[right.first][right.second] = '2';
        return right;
    }
    
    pair<int, int> markUp(vector<vector<char>>& image, const pair<int, int>& pt) const {
        if (pt.second == 0) {
            return {-1, 0};
        }
        
        pair<int, int> top{pt.first, pt.second - 1};;
        if (image[top.first][top.second] != '1') {
            return {-1, 0};
        }
        
        image[top.first][top.second] = '2';
        return top;
    }
    
    pair<int, int> markDown(vector<vector<char>>& image, const pair<int, int>& pt) const {
        if (pt.second + 1 == image[0].size()) {
            return {-1, 0};
        }
        
        pair<int, int> down{pt.first, pt.second + 1};;
        if (image[down.first][down.second] != '1') {
            return {-1, 0};
        }
        
        image[down.first][down.second] = '2';
        return down;
    }
    
    bool isPtValid(const pair<int, int>& pt) const {
        return pt.first >= 0;
    }
    
    void updateButtonLeft(pair<int, int>& buttomLeftPt, const pair<int, int>& pt) {
        if (pt.first < buttomLeftPt.first) {
            buttomLeftPt.first = pt.first;
        }
        if (pt.second < buttomLeftPt.second) {
            buttomLeftPt.second = pt.second;
        }
    }
    
    void updateTopRight(pair<int, int>& topLeftPt, const pair<int, int>& pt) {
        if (pt.first > topLeftPt.first) {
            topLeftPt.first = pt.first;
        }
        if (pt.second > topLeftPt.second) {
            topLeftPt.second = pt.second;
        }
    }
    
    
    void updateRectangle(const pair<int, int>& pt, pair<int, int>& buttomLeftPt, pair<int, int>& topRightPt) {
        updateTopRight(topRightPt, pt);
        updateButtonLeft(buttomLeftPt, pt);
    }
    
    void addToQueueAndUpdate(const pair<int, int>& pt, deque<pair<int, int>>& unvisitedPts, pair<int, int>& buttomLeftPt, pair<int, int>& topRightPt) {
        if (isPtValid(pt)) {
            unvisitedPts.push_back(pt);
            updateRectangle(pt, buttomLeftPt, topRightPt);
        }
    }
    
    void exploreBlackTiles(vector<vector<char>>& image, deque<pair<int, int>>& unvisitedPts, pair<int, int>& buttomLeftPt, pair<int, int>& topRightPt) {
        while (!unvisitedPts.empty()) {
            pair<int, int> ptToVisit = unvisitedPts.front();
            unvisitedPts.pop_front();
            
            pair<int, int> nextPt;
            nextPt = markLeft(image, ptToVisit);
            addToQueueAndUpdate(nextPt, unvisitedPts, buttomLeftPt, topRightPt);
            
            nextPt = markRight(image, ptToVisit);
            addToQueueAndUpdate(nextPt, unvisitedPts, buttomLeftPt, topRightPt);
            
            nextPt = markUp(image, ptToVisit);
            addToQueueAndUpdate(nextPt, unvisitedPts, buttomLeftPt, topRightPt);
            
            nextPt = markDown(image, ptToVisit);
            addToQueueAndUpdate(nextPt, unvisitedPts, buttomLeftPt, topRightPt);
        }
    }
    
public:
    int minArea(vector<vector<char>>& image, int x, int y) {
        pair<int, int> buttomLeftPt{x, y};
        pair<int, int> topRightPt{x, y};
        deque<pair<int, int>> unvisitedPts{{x, y}};
        
        exploreBlackTiles(image, unvisitedPts, buttomLeftPt, topRightPt);
        return getArea(buttomLeftPt, topRightPt);
    }
};

int main() {
    Solution S;
//    vector<vector<char>> map{{'0','0','1','0'},{'0','1','1','0'},{'0','1','0','0'}};
    vector<vector<char>> map{{'1', '1'}};
    S.minArea(map, 0, 1);
    
    return 0;
}
