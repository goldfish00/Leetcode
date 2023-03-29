/* 2600. K Items With the Maximum Sum */
//class Solution {
//public:
//    int kItemsWithMaximumSum(int numOnes, int numZeros, int numNegOnes, int k) {
//        if (k <= numOnes + numZeros) {
//            return min(k, numOnes);
//        }
//        return 2 * numOnes - k + numZeros;
//    }
//};

/* 2601. Prime Subtraction Operation */
//class Solution {
//private:
//    deque<int> primes{2, 3, 5};
//
//    bool isPrime(int num) {
//        int upperBound = (int)sqrt(num);
//        for (const int& prime : primes) {
//            if (prime > upperBound) {
//                break;
//            }
//            if (num % prime == 0) {
//                return false;
//            }
//        }
//        return true;
//    }
//
//    void genPrime(int upperBound) {
//        if (upperBound <= primes.back()) {
//            return;
//        }
//
//        for (int n = primes.back() + 1; n < upperBound; ++n) {
//            if (isPrime(n)) {
//                primes.push_back(n);
//            }
//        }
//    }
//
//    // find the greatest subtraction of current and a prime such that
//    // current - prime < next
//    int findGreatestSubRes(int current, int next) {
//        genPrime(current);
//
//        for (const int& prime : primes) {
//            int res = current - prime;
//            if (res < next) {
//                return res;
//            }
//        }
//
//        return 0;
//    }
//
//public:
//    bool primeSubOperation(vector<int>& nums) {
//        int count = (int)nums.size();
//        for (int i = count - 2; i >= 0; --i) {
//            if (nums[i] < nums[i + 1]) {
//                continue;
//            }
//
//            nums[i] = findGreatestSubRes(nums[i], nums[i + 1]);
//            if (nums[i] <= 0) {
//                return false;
//            }
//        }
//        return true;
//    }
//};
//
//int main() {
////    vector<int> nums{1,20,7,12,4};
//    vector<int> nums{18,12,14,6};
//    Solution S;
//    cout << S.primeSubOperation(nums) << endl;
//    return 0;
//}

/* 2602. Minimum Operations to Make All Array Elements Equal */
//class Solution {
//private:
//    long long findMinOperations(const vector<int>& nums, int target) {
//        long long numOps = 0;
//        for (const int& n : nums) {
//            numOps += abs(n - target);
//        }
//        return numOps;
//    }
//
//    void markAnswers(vector<long long>& answers, const set<int>& indices, long long res) {
//        for (const int& i : indices) {
//            answers[i] = res;
//        }
//    }
//
//public:
//    vector<long long> minOperations(vector<int>& nums, vector<int>& queries) {
//        vector<long long> answers;
//        map<int, set<int>> targetQueryDict; //key: target, value: indices in the queries
//        answers.resize(queries.size());
//        for (int i = 0; i < queries.size(); ++i) {
//            targetQueryDict[queries[i]].insert(i);
//        }
//
//        sort(nums.begin(), nums.end());
//        sort(queries.begin(), queries.end());
//
//        int prevTarget = queries[0];
//        long long res = findMinOperations(nums, prevTarget);
//        markAnswers(answers, targetQueryDict[prevTarget], res);
//        auto upperBound = upper_bound(nums.begin(), nums.end(), prevTarget);
//
//        for (int i = 1; i < queries.size(); ++i) {
//            int curTarget = queries[i];
//            if (curTarget == prevTarget) {
//                continue;
//            }
//
//            auto newUpperBound = upper_bound(nums.begin(), nums.end(), curTarget);
//            res += ((upperBound - nums.begin()) - (nums.end() - newUpperBound)) * (curTarget - prevTarget);
//
//            for (auto it = upperBound; it != newUpperBound; ++it) {
//                res += curTarget + prevTarget - 2 * (*it);
//            }
//            markAnswers(answers, targetQueryDict[curTarget], res);
//
//            prevTarget = curTarget;
//            upperBound = newUpperBound;
//        }
//
//        return answers;
//    }
//};

/* 2603. Collect Coins in a Tree */
// Wrong Solution
class Solution {
private:
    void tryCollectAtNode(const int& rootNode, int curNode, unordered_map<int, set<int>>& canCollectNode, const unordered_map<int, set<int>> mutualEdges, const vector<int>& coins, int distance) {
        if (coins[curNode] == 1) {
            canCollectNode[rootNode].insert(curNode);
        }
        if (distance == 0) {
            return;
        }
        
        auto it = mutualEdges.find(curNode);
        if (it == mutualEdges.end()) {
            return;
        }
        for (const int& nextNode : it->second) {
            tryCollectAtNode(rootNode, nextNode, canCollectNode, mutualEdges, coins, distance - 1);
        }
    }
    
    void tryFindCoins(int curNode, unordered_set<int>& uncollectedCoin, unordered_set<int> visitedNode, const unordered_map<int, set<int>>& mutualEdges, const unordered_map<int, set<int>> canCollectNode, int step, int& minStep) {
        auto edgeIt = mutualEdges.find(curNode);
        auto it = canCollectNode.find(curNode);
        if (it == canCollectNode.end()) {
            if (edgeIt == mutualEdges.end()) {
                return;
            }
        }
        
        if (step * 2 >= minStep) {
            return;
        }
        visitedNode.insert(curNode);
        
        deque<int> newlyVisitedNodes;
        if (it != canCollectNode.end()) {
            for (const int& node : it->second) {
                auto uncollectedIt = uncollectedCoin.find(node);
                if (uncollectedIt != uncollectedCoin.end()) {
                    uncollectedCoin.erase(uncollectedIt);
                    newlyVisitedNodes.push_back(node);
                }
            }
        }
        
        if (uncollectedCoin.empty()) {
            minStep = min(minStep, step * 2);
            for (const int& i : newlyVisitedNodes) {
                uncollectedCoin.insert(i);
            }
            return;
        }
        
        for (const int& i : edgeIt->second) {
            if (visitedNode.find(i) != visitedNode.end()) {
                continue;
            }
            tryFindCoins(i, uncollectedCoin, visitedNode, mutualEdges, canCollectNode, step + 1, minStep);
        }
        
        for (const int& i : newlyVisitedNodes) {
            uncollectedCoin.insert(i);
        }
        visitedNode.erase(curNode);
        return;
    }
    
public:
    int collectTheCoins(vector<int>& coins, vector<vector<int>>& edges) {
        unordered_set<int> coinNodes;
        for (int i = 0; i < coins.size(); ++i) {
            if (coins[i] == 1) {
                coinNodes.insert(i);
            }
        }
        if (coinNodes.empty()) {
            return 0;
        }
        
        unordered_map<int, set<int>> mutualEdges;
        for (const vector<int>& edge : edges) {
            mutualEdges[edge.front()].insert(edge.back());
            mutualEdges[edge.back()].insert(edge.front());
        }
        
        unordered_map<int, set<int>> canCollectNode;
        for (int i = 0; i < coins.size(); ++i) {
            tryCollectAtNode(i, i, canCollectNode, mutualEdges, coins, 2);
        }
        
        int numStep = 2 * (int)coins.size();
        unordered_set<int> visitedNode;
        for (int i = 0; i < coins.size(); ++i) {
            tryFindCoins(i, coinNodes, visitedNode, mutualEdges, canCollectNode, 0, numStep);
        }
        return numStep;
    }
};

int main() {
    vector<int> cions{1,0,0,0,0,1};
    vector<vector<int>> edges{{0,1},{1,2},{2,3},{3,4},{4,5}};
    Solution S;
    cout << S.collectTheCoins(cions, edges) <<  endl;

    return 0;
}
