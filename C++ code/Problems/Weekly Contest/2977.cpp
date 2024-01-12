class Solution {
private:
    int getId(const string& c, const unordered_map<string, int>& dict) {
        auto it = dict.find(c);
        if (it == dict.end()) {
            return -1;
        }

        return it->second;
    }
    
    void addPath(vector<vector<int>>& costDict, int sourceId, int destId, int cost) {
        int& curCost = costDict[sourceId][destId];
        if (curCost <= cost) { // no need to update
            return;
        }
        
        curCost = cost;
        vector<pair<int, int>> updatedIdCosts;
        updatedIdCosts.reserve(26);
        // update all path source-dest-i
        {
            for (int i = 0; i < costDict.size(); ++i) {
                if (i == destId) {
                    updatedIdCosts.push_back({destId, cost});
                    continue;
                }
                
                int secondHalfCost = costDict[destId][i];
                if (secondHalfCost != INT_MAX) {
                    int& curFullCost = costDict[sourceId][i];
                    int newCost = cost + secondHalfCost;
                    if (curFullCost > newCost) {
                        updatedIdCosts.push_back({i, newCost});
                        curFullCost = newCost;
                    }
                }
            }
        }
        
        // update all path i-source-j
        {
            for (int i = 0; i < costDict.size(); ++i) {
                int firstHalfCost = costDict[i][sourceId];
                if (firstHalfCost == INT_MAX) {
                    continue;
                }
                
                for (const auto& info : updatedIdCosts) {
                    int& curFullCost = costDict[i][info.first];
                    int newFullCost = firstHalfCost + info.second;
                    if (curFullCost > newFullCost) {
                        curFullCost = newFullCost;
                    }
                }
            }
        }
    }

    void initialize(unordered_map<string, int>& stringMap, const vector<string>& ss) {
        for (const auto& s : ss) {
            auto it = stringMap.find(s);
            if (it == stringMap.end()) {
                stringMap.insert({s, (int)stringMap.size()});
            }
        }
    }

    long long getCost(int i, const vector<long long>& costMeme) {
        if (i < 0) {
            return 0;
        }
        return costMeme[i];
    }
    
    int getCost(const string& source, const string& target, const unordered_map<string, int>& stringMap, const vector<vector<int>>& costDict) {
        if (source == target) {
            return 0;
        }
        
        int curSourceId = getId(source, stringMap);
        int curTargetId = getId(target, stringMap);
        if (curSourceId == -1 || curTargetId == -1) {
            return INT_MAX;
        }
        
        return costDict[curSourceId][curTargetId];
    }
  
public:
    long long minimumCost(string source, string target, vector<string>& original, vector<string>& changed, vector<int>& cost) {
        unordered_map<string, int> stringMap;
        initialize(stringMap, original);
        initialize(stringMap, changed);

        unordered_set<int> subLens;
        vector<vector<int>> costDict(stringMap.size(), vector<int>(stringMap.size(), INT_MAX));
        for (int i = 0; i < original.size(); ++i) {
            addPath(costDict, getId(original[i], stringMap), getId(changed[i], stringMap), cost[i]);
            subLens.insert((int)original[i].size());
        }

        // dp
        vector<long long> costMeme(target.size(), LONG_LONG_MAX);
        string curSource;
        string curTarget;
        curSource.reserve(target.size());
        curTarget.reserve(target.size());
        
        for (int i = 0; i < target.size(); ++i) {
            if (getCost(i - 1, costMeme) == LONG_LONG_MAX) {
                continue;
            }
            
            // jump through identicals
            curSource.clear();
            curTarget.clear();
            for (int k = i; k < target.size(); ++k) {
                curSource.push_back(source[k]);
                curTarget.push_back(target[k]);
                if (curSource == curTarget) {
                    costMeme[k] = min(costMeme[k], getCost(i - 1, costMeme));
                } else {
                    break;
                }
            }

            for (const int& len : subLens) {
                int j = i + len - 1;
                if (j >= target.size()) {
                    continue;
                }
                curSource = source.substr(i, len);
                curTarget = target.substr(i, len);
                
                int cost = getCost(curSource, curTarget, stringMap, costDict);
                if (cost == INT_MAX) {
                    continue;
                } else {
                    costMeme[j] = min(costMeme[j], getCost(i - 1, costMeme) + cost);
                }
            }
        }

        if (costMeme.back() == LONG_LONG_MAX) {
            return -1;
        }
        return costMeme.back();
    }
};
