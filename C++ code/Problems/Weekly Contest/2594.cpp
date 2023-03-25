/* 2594. Minimum Time to Repair Cars */
class Solution {
private:
    bool canMake(const map<int, int>& numRankMap, int cars, long long time) {
        int carsMade = 0;
        for (auto const& pair : numRankMap) {
            carsMade += pair.second * int(pow(time / pair.first, 0.5));
        }
        return carsMade >= cars;
    }
    
public:
    long long repairCars(vector<int>& ranks, int cars) {
        map<int, int> numRankMap;
        for (const int& rank : ranks) {
            ++numRankMap[rank];
        }
        long long upperBound = numRankMap.begin()->first * pow(ceil(double(cars) / numRankMap.begin()->second), 2);
        // binary search for the smallest time
        long long lowerBound = 0;
        
        while (lowerBound != upperBound) {
            long long middle = (upperBound + lowerBound) / 2;
            if (middle == lowerBound) {
                return upperBound;
            }
            
            if (!canMake(numRankMap, cars, middle)) {
                lowerBound = middle;
            } else {
                upperBound = middle;
            }
        }
        
        return lowerBound;
    }
};

int main() {
    vector<int> ranks{3,3,1,2,1,1,3,2,1};
    Solution S;
    cout << S.repairCars(ranks, 58) << endl;
    return 0;
}
