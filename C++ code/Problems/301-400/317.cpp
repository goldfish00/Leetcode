/* 317. Shortest Distance from All Buildings */
//class Solution {
//public:
//    int shortestDistance(vector<vector<int>>& grid) {
//
//    }
//};

/* 318. Maximum Product of Word Lengths */
// TLE
//class Solution {
//private:
//    class stringLenGreater {
//    public:
//        bool operator()(const string& s1, const string& s2) const {
//            return s1.size() > s2.size();
//        }
//    };
//
//public:
//    int maxProduct(vector<string>& words) {
//        int maxRes = 0;
//
//        stringLenGreater lenGreater;
//        sort(words.begin(), words.end(), lenGreater);
//
//        for (auto it1 = words.begin(); it1 != words.end(); ++it1) {
//            if (pow(it1->size(), 2) < maxRes) {
//                break;
//            }
//
//            unordered_set<char> charDict(it1->begin(), it1->end());
//
//            for (auto it2 = it1 + 1; it2 != words.end(); ++it2) {
//                int curProduct = int(it1->size() * it2->size());
//                if (curProduct < maxRes) {
//                    break;
//                }
//
//                bool hasOverlapped = false;
//                for (const char& c : *it2) {
//                    if (charDict.find(c) != charDict.end()) {
//                        hasOverlapped = true;
//                        break;
//                    }
//                }
//
//                if (!hasOverlapped) {
//                    maxRes = curProduct;
//                }
//            }
//        }
//
//        return maxRes;
//    }
//};

// Low performance but passed
class Solution {
private:
    int getIndex(const char& c) {
        return c - 'a';
    }
    
    class stringLenGreater {
    public:
        bool operator()(const string& s1, const string& s2) const {
            return s1.size() > s2.size();
        }
    };
    
public:
    int maxProduct(vector<string>& words) {
        vector<unordered_set<char>> charDicts;
        charDicts.reserve(words.size());
        vector<vector<int>> alphabeticalOverlappedIndices;
        alphabeticalOverlappedIndices.resize(26);
        
        stringLenGreater lenGreater;
        sort(words.begin(), words.end(), lenGreater);
        
        int index = 0;
        for (const string& s : words) {
            charDicts.push_back(unordered_set<char>(s.begin(), s.end()));
            for (const char& c : charDicts.back()) {
                alphabeticalOverlappedIndices[getIndex(c)].push_back(index);
            }
            
            ++index;
        }
        
        int maxRes = 0;
        index = 0;
        for (const string& w : words) {
            if (maxRes > pow(w.size(), 2)) {
                break;
            }
            
            unordered_set<int> overlappedWordIndices;
            for (const char& c : charDicts[index]) {
                vector<int>& indices = alphabeticalOverlappedIndices[getIndex(c)];
                overlappedWordIndices.insert(indices.begin(), indices.end());
            }
            
            if (overlappedWordIndices.size() == words.size()) {
                ++index;
                continue;
            }
            
            for (int j = index + 1; j < words.size(); ++j) {
                if (overlappedWordIndices.find(j) == overlappedWordIndices.end()) {
                    maxRes = max(maxRes, int(words[index].size() * words[j].size()));
                }
            }
            
            ++index;
        }
        
        return maxRes;
    }
};

class Solution {
private:
    static bool lenGreater(const pair<int, int>& left, const pair<int, int>& right) {
        return left.second > right.second;
    }
    
    int getBitIndex(const char& c) {
        return c - 'a';
    }
    
public:
    int maxProduct(vector<string>& words) {
        // key: bit representation, value: largest len
        unordered_map<int, int> bitLenDict;
        
        for (const string& word : words) {
            int bitValue = 0;
            for (const char& c : word) {
                bitValue |= (1 << getBitIndex(c));
            }
            
            auto it = bitLenDict.find(bitValue);
            if (it == bitLenDict.end()) {
                bitLenDict.insert({bitValue, word.length()});
            } else if (it->second < word.length()) {
                it->second = (int)word.length();
            }
        }
        
        int maxRes = 0;
        vector<pair<int, int>> bitLenPairs(bitLenDict.begin(), bitLenDict.end());
        sort(bitLenPairs.begin(), bitLenPairs.end(), lenGreater);
        for (auto it1 = bitLenPairs.begin(); it1 != bitLenPairs.end(); ++it1) {
            if (maxRes > pow(it1->second, 2)) {
                break;
            }
            
            for (auto it2 = it1 + 1; it2 != bitLenPairs.end(); ++it2) {
                int curRes = it1->second * it2->second;
                if (maxRes > curRes) {
                    break;
                }
                
                if ((it1->first & it2->first) == 0) {
                    maxRes = curRes;
                }
            }
        }
        
        return maxRes;
    }
};
