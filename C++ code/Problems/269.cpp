#include <iostream>
// unordered_multiset here
#include <unordered_set>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>
#include <assert.h>
#include <set>
#include <deque>
#include <unordered_map>
#include <queue>
using namespace std;

/* 269. Alien Dictionary *//* Topoligical Sort */
class Solution {
private:
    bool genOrder(const string& firstS, const string& secondS, vector<char>& order) {
        order.clear();
        for (auto it1 = firstS.begin(), it2 = secondS.begin(); it1 != firstS.end() && it2 != secondS.end(); ++it1, ++it2) {
            if (*it1 == *it2) {
                continue;
            }
            
            order.push_back(*it1);
            order.push_back(*it2);
            return true;
        }
        
        if (secondS.size() < firstS.size()) {
            return false;
        }
        return true;
    }
    
public:
    string alienOrder(vector<string>& words) {
        unordered_map<char, vector<char>> childParentDict;
        unordered_map<char, int> childNumDict;
        string result;
        result.reserve(words.size());
        
        vector<char> order;
        order.reserve(2);
        
        for (const char& c : words.front()) {
            childNumDict[c];
        }
        
        for (auto it = words.begin() + 1; it != words.end(); ++it) {
            if (!genOrder(*(it - 1), *it, order)) {
                return result;
            }
            
            for (const char& c : *it) {
                childNumDict[c];
            }
            
            if (order.empty()) {
                continue;
            }
            
            assert(order.size() == 2);
            childParentDict[order[0]].push_back(order[1]);
            childNumDict[order[0]];
            ++childNumDict[order[1]];
        }
        
        bool canContinue = false;
        while (!childNumDict.empty()) {
            for (auto it = childNumDict.begin(); it != childNumDict.end();) {
                auto nextIt = next(it);
                if (it->second == 0) {
                    char c = it->first;
                    result.push_back(c);
                    canContinue = true;
                    childNumDict.erase(it);
                    
                    vector<char>& parents = childParentDict[c];
                    for (const char& parent : parents) {
                        --childNumDict[parent];
                    }
                }
                
                it = nextIt;
            }
            
            if (!canContinue) {
                result.clear();
                return result;
            }
            canContinue = false;
        }
        
        return result;
    }
};

int main() {
//    vector<string> words{"wrt","wrf","er","ett","rftt"};
    vector<string> words{"wrt","wrtkj"};
    Solution S;
    cout << S.alienOrder(words) << endl;
    return 0;
}
