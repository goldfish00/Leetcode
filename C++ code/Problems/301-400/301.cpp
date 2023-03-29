/* 301. Remove Invalid Parentheses */
class Solution {
private:
    bool isLeftParenthesis(const char& c) {
        return c == '(';
    }
    
    bool isRightParenthesis(const char& c) {
        return c == ')';
    }
    
    bool noParenthesis(const string& s) {
        for (const char& c : s) {
            if (isLeftParenthesis(c)) {
                return false;
            }
            if (isRightParenthesis(c)) {
                return false;
            }
        }
        return true;
    }
    
    bool isValid(const string& s) {
        int numLeft = 0;
        for (const char& c : s) {
            if (isLeftParenthesis(c)) {
                ++numLeft;
            } else if (isRightParenthesis(c)) {
                --numLeft;
                if (numLeft < 0) {
                    return false;
                }
            }
        }
        return true;
    }
    
    string genStringWithIndexErased(const string& s, const unordered_set<int>& indices) {
        if (s.empty()) {
            return "";
        }
        
        string sCopy("");
        sCopy.reserve(s.size() - 1);
        for (int j = 0; j < s.size(); ++j) {
            if (indices.find(j) != indices.end()) {
                continue;
            }
            sCopy.push_back(s[j]);
        }
        return sCopy;
    }
    
    void deleteParenthesis(vector<string>& res, unordered_set<int>& indices, const string& s, const vector<pair<int, int>>& rightParenthesis, int numToDelete, int startPos = 0) {
        if (numToDelete == 0) {
            string trimmed = genStringWithIndexErased(s, indices);
            if (isValid(trimmed)) {
                res.push_back(trimmed);
            }
            return;
        }
        if (startPos >= rightParenthesis.size()) {
            return;
        }
        
        auto& curRight = rightParenthesis[startPos];
        for (int i = 0; i < min(curRight.second, numToDelete); ++i) {
            indices.insert(curRight.first + i);
            deleteParenthesis(res, indices, s, rightParenthesis, numToDelete - i - 1, startPos + 1);
        }
        
        for (int i = 0; i < min(curRight.second, numToDelete); ++i) {
            indices.erase(curRight.first + i);
        }
        
        deleteParenthesis(res, indices, s, rightParenthesis, numToDelete, startPos + 1);
    }
    
    vector<string> genPossibilities(const string& s, const vector<string>& ss) {
        vector<string> res;
        for (const string& member : ss) {
            res.push_back(s + member);
        }
        return res;
    }
    
    vector<string> genPossibilities(const vector<string>& prev, const vector<string>& next) {
        vector<string> res;
        for (const string& prevMemeber : prev) {
            for (const string& nextMember : next) {
                res.push_back(prevMemeber + nextMember);
            }
        }
        return res;
    }
    
    vector<string> genValidParenthesis(const string& s, int numLeftParenthesis) {
        if (numLeftParenthesis == 0 || s.empty()) {
            return vector<string>{s};
        }
        if (s.size() == abs(numLeftParenthesis)) {
            return vector<string>{""};
        }
        
        vector<string> res;
        unordered_set<int> indices;
        if (numLeftParenthesis < 0) {
            vector<pair<int, int>> rightParenthesis; // pair: {right parenthesis index, consecutive parenthesis num}
            int lastRightParenthesisId = -1;
            int numRight = 0;
            int numLeft = 0;
            for (int i = 1; i < s.size(); ++i) {
                if (isRightParenthesis(s[i])) {
                    if (!isRightParenthesis(s[i - 1])) {
                        lastRightParenthesisId = i;
                        numRight = 0;
                    }
                    ++numRight;
                    continue;
                }
                
                if (lastRightParenthesisId >= 0) {
                    rightParenthesis.push_back({lastRightParenthesisId, numRight});
                    lastRightParenthesisId = -1;
                }
                
                if (isLeftParenthesis(s[i])) {
                    if (i != 0 && !isLeftParenthesis(s[i - 1])) {
                        numLeft = 0;
                    }
                    ++numLeft;
                    continue;
                }
                
                numRight = 0;
                numLeft = 0;
            }
            rightParenthesis.push_back({lastRightParenthesisId, numRight - numLeft});
            
            deleteParenthesis(res, indices, s, rightParenthesis, -numLeftParenthesis);
            return res;
        }
        
        // numLeftParenthesis > 0
        vector<pair<int, int>> leftParenthesis; // pair: {right parenthesis index, consecutive parenthesis num that can be deleted}
        int lastDeletableLeftParenthesisId = -1;
        int numDeletableLeftParenthesis = 0;
        int numConsecutiveLeftParenthesis = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (isLeftParenthesis(s[i])) {
                if (lastDeletableLeftParenthesisId < 0) {
                    lastDeletableLeftParenthesisId = i;
                } else if (!isLeftParenthesis(s[i - 1])) {
                    leftParenthesis.push_back({lastDeletableLeftParenthesisId, min(numDeletableLeftParenthesis, numConsecutiveLeftParenthesis)});
                    lastDeletableLeftParenthesisId = i;
                    numConsecutiveLeftParenthesis = 0;
                }
                ++numDeletableLeftParenthesis;
                ++numConsecutiveLeftParenthesis;
                continue;
            }
            if (isRightParenthesis(s[i])) {
                --numDeletableLeftParenthesis;
            }
        }
        leftParenthesis.push_back({lastDeletableLeftParenthesisId, min(numDeletableLeftParenthesis, numConsecutiveLeftParenthesis)});
        
        deleteParenthesis(res, indices, s, leftParenthesis, numLeftParenthesis);
        return res;
    }
    
    vector<string> genValidParenthesis(const string& s) {
        int numLeftParathesis = 0;
        int lastNegativeId = -1;
        int lastNegativeNum = 0;
        
        for (int i = 0; i < s.size(); ++i) {
            if (isLeftParenthesis(s[i])) {
                if (lastNegativeId < 0) {
                    lastNegativeId = i;
                }
                
                ++numLeftParathesis;
                continue;
            }
            if (isRightParenthesis(s[i])) {
                --numLeftParathesis;
                if (numLeftParathesis < 0 && (i + 1 == s.size() || !isRightParenthesis(s[i + 1]))) {
                    if (numLeftParathesis < lastNegativeNum) {
                        lastNegativeNum = numLeftParathesis;
                        lastNegativeId = i;
                    } else if (numLeftParathesis == lastNegativeNum) {
                        continue;
                    } else {
                        break;
                    }
                }
            }
        }
        
        if (lastNegativeNum < 0) {
            return genPossibilities(genValidParenthesis(s.substr(0, lastNegativeId + 1), lastNegativeNum), genValidParenthesis(s.substr(lastNegativeId + 1)));
        }
        return genValidParenthesis(s, numLeftParathesis);
    }
    
public:
    vector<string> removeInvalidParentheses(string s) {
        unordered_set<int> toRemove;
        for (int i = 0; i < s.size(); ++i) {
            if (isRightParenthesis(s[i])) {
                toRemove.insert(i);
            }
            if (isLeftParenthesis(s[i])) {
                break;
            }
        }
        for (int i = (int)s.size() - 1; i >= 0; --i) {
            if (isLeftParenthesis(s[i])) {
                toRemove.insert(i);
            }
            if (isRightParenthesis(s[i])) {
                break;
            }
        }
        string trimmed = genStringWithIndexErased(s, toRemove);
        if (trimmed.empty() || noParenthesis(trimmed)) {
            return vector<string>{trimmed};
        }
        toRemove.clear();
        
        int numRight = 0;
        for (int i = 0; i < trimmed.size(); ++i) {
            if (isRightParenthesis(trimmed[i])) {
                ++numRight;
                if (i + 1 != trimmed.size() && !isRightParenthesis(trimmed[i + 1])) {
                    if (numRight > 0) {
                        for (int j = 0; j < numRight; ++j) {
                            toRemove.insert(i - j);
                        }
                    }
                    break;
                }
                continue;
            }
            if (isLeftParenthesis(trimmed[i])) {
                --numRight;
            }
        }
        
        int numLeft = 0;
        for (int i = (int)trimmed.size() - 1; i >= 0; --i) {
            if (isLeftParenthesis(trimmed[i])) {
                ++numLeft;
                if (i != 0 && !isLeftParenthesis(trimmed[i - 1])) {
                    if (numLeft > 0) {
                        for (int j = 0; j < numLeft; ++j) {
                            toRemove.insert(i + j);
                        }
                    }
                    break;
                }
                continue;
            }
            if (isRightParenthesis(trimmed[i])) {
                --numLeft;
            }
        }
        trimmed = genStringWithIndexErased(trimmed, toRemove);
        if (trimmed.empty() || noParenthesis(trimmed)) {
            return vector<string>{trimmed};
        }
        
        return genValidParenthesis(trimmed);
    }
};

int main() {
    Solution S;
    vector<string> res;
//    res = S.removeInvalidParentheses("()())()");
//    res = S.removeInvalidParentheses("(a)())()");
//    res = S.removeInvalidParentheses("((())((())");
//    res = S.removeInvalidParentheses("))");
//    res = S.removeInvalidParentheses(")(");
//    res = S.removeInvalidParentheses("(()))(()))(()))");
//    res = S.removeInvalidParentheses("(()))(()))((())");
//    res = S.removeInvalidParentheses(")(f");
//    res = S.removeInvalidParentheses("zw(()");
//    res = S.removeInvalidParentheses("()(()((");
//    res = S.removeInvalidParentheses("()((((()");
//    res = S.removeInvalidParentheses("(((k()((");
//    res = S.removeInvalidParentheses(")(()c))(");
//    res = S.removeInvalidParentheses("())()k)");
//    res = S.removeInvalidParentheses("(()))(()))");
//    res = S.removeInvalidParentheses("(()))e())()");
//    res = S.removeInvalidParentheses("((()((s((((()");
    res = S.removeInvalidParentheses("(()()))q(l)()o)(z");
    for (const auto& r : res) {
        cout << r << endl;
    }
    return 0;
}
