/* 309. Best Time to Buy and Sell Stock with Cooldown */
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() < 2) {
            return 0;
        }
        
        // two states: hold, not hold
        deque<vector<int>> profits; // vectot[0] for hold, vector[1] for not hold
        profits.push_back({-prices.front(), 0});
        profits.push_back({max(-prices.front(), -prices[1]), max(prices[1] - prices.front(), 0)});
        for (int i = 2; i < prices.size(); ++i) {
            profits.push_back({
                max(profits.front()[1] - prices[i]/* buy */, profits.back()[0] /* continue holding */),
                max(profits.back()[0] + prices[i] /* sell */, profits.back()[1] /* continue not holding */)
            });
            profits.pop_front();
        }
        return profits.back()[1];
    }
};

int main() {
    vector<int> prices{2, 1, 4};
    Solution S;
    S.maxProfit(prices);
    
    return 0;
}
