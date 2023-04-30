/* 316. Remove Duplicate Letters */
// greedy
class Solution {
private:
    bool isValid(const char& c) {
        return c >= 'a' && c <= 'z';
    }
    
    bool canDelete(const char& c, const unordered_map<char, set<int>>& charIndDict, int count) {
        return charIndDict.find(c)->second.size() > count;
    }
    
public:
    string removeDuplicateLetters(string s) {
        unordered_map<char, set<int>> charIndexDict;
        
        int index = 0;
        for (const char& c : s) {
            charIndexDict[c].insert(index);
            ++index;
        }
        
        for (int i = 0; i < s.size();) {
            if (!isValid(s[i])) {
                ++i;
                continue;
            }
            
            if (!canDelete(s[i], charIndexDict, 1)) {
                ++i;
                continue;
            }
            
            cout << s[i] << endl;
            
            unordered_map<char, set<int>> possibleDelete;
            possibleDelete[s[i]].insert(i);
            
            // delete if deleting it can result in smaller leading char
            for (int j = i + 1; j < s.size(); ++j) {
                if (!isValid(s[j])) {
                    continue;
                }
                
                if (s[j] < s[i]) {
                    for (int deleteIndex = i; deleteIndex < j; ++deleteIndex) {
                        charIndexDict[s[deleteIndex]].erase(deleteIndex);
                        s[deleteIndex] = 0;
                    }
                    ++i;
                    break;
                }
                
                possibleDelete[s[j]].insert(j);
                if (!canDelete(s[j], charIndexDict, (int)possibleDelete[s[j]].size())) { // we cannot delete s[j]
                    // keep s[i] and mark all duplicate as deleted
                    cout << s[j] << endl;
                    for (const int& ind : charIndexDict[s[i]]) {
                        if (ind == i) {
                            continue;
                        }
                        s[ind] = 0;
                    }
                    
                    if (s[j] == 0 || s[i] < s[j]) {
                        ++i;
                        break;
                    }
                    
                    // delete all those greater than s[j]
                    for (const auto& pair : possibleDelete) {
                        if (pair.first > s[j]) {
                            for (const int& ind : pair.second) {
                                charIndexDict[s[ind]].erase(ind);
                                s[ind] = 0;
                            }
                        }
                    }
                    ++i;
                    break;
                }
            }
        }
        
        string res;
        res.reserve(s.length());
        for (const char& c : s) {
            if (c != 0) {
                res.push_back(c);
            }
        }
        return res;
    }
};


// Method 2: the use of stack
class Solution {
public:
    string removeDuplicateLetters(string s) {
        unordered_map<char, int> charCountDict;
        for (const char& c : s ) {
            ++charCountDict[c];
        }
        
        vector<char> resChars;
        unordered_set<char> existingChars;
        resChars.reserve(s.size());
        for (const char& c : s) {
            if (existingChars.find(c) != existingChars.end()) {
                --charCountDict[c];
                continue;
            }
            
            while (!resChars.empty() && charCountDict[resChars.back()] > 0 && c < resChars.back()) { // can be deleted and should be deleted
                existingChars.erase(resChars.back());
                resChars.pop_back();
            }
            
            resChars.push_back(c);
            --charCountDict[c];
            existingChars.insert(c);
        }
        
        return string(resChars.begin(), resChars.end());
    }
};

int main() {
//    string s("chacdcbc");
//    string s("cbacdcbc");
//    string s("cdadabcc");
//    string s("abacb");
    string s("wmxkuuoordmnpnebikzzujdpscpedcrsjphcaykjsmobturjjxxpoxvvrynmapegvtlasmyuddgxyg");
    Solution S;
    S.removeDuplicateLetters(s);
    
    return 0;
}

