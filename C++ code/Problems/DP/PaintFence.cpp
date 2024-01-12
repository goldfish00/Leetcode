class Solution {
private:
    struct colorInfo {
        int sameAsPrevNum;
        int differentFromPrevNum;
        
        int allNum() {
            return sameAsPrevNum + differentFromPrevNum;
        }
    };
    
public:
    int numWays(int n, int k) {
        if (n == 1) {
            return k;
        }
        
        colorInfo meme{0, k};
        for (int i = 2; i <= n; ++i) {
            int sameAsPrev = meme.differentFromPrevNum;
            int differentFromPrev = meme.sameAsPrevNum * (k - 1) + meme.differentFromPrevNum * (k - 1);
            
            meme.sameAsPrevNum = sameAsPrev;
            meme.differentFromPrevNum = differentFromPrev;
        }
        
        return meme.allNum();
    }
};

int main() {
    Solution S;
    S.numWays(5, 3);
    
    return 0;
}
