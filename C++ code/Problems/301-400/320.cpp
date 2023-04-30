/* 320. Generalized Abbreviation */
// backtrack
class Solution {
private:
    void findAbbrWithBacktrack(const string& word, int curIndex, string& abbr, forward_list<string>& res) {
        if (curIndex == word.length()) {
            res.push_front(abbr);
            return;
        }
        
        // abbrevation
        if (abbr.empty() || !isdigit(abbr.back())) {
            for (int nextIndex = curIndex + 1; nextIndex <= word.length(); ++nextIndex) {
                string abbrLen = to_string(nextIndex - curIndex);
                abbr += abbrLen;
                findAbbrWithBacktrack(word, nextIndex, abbr, res);
                
                for (int i = 0; i < abbrLen.length(); ++i) {
                    abbr.pop_back();
                }
            }
        }
        
        // no abbrevation
        abbr.push_back(word[curIndex]);
        findAbbrWithBacktrack(word, curIndex + 1, abbr, res);
        abbr.pop_back();
    }
    
public:
    vector<string> generateAbbreviations(string word) {
        forward_list<string> res;
        string abbr;
        findAbbrWithBacktrack(word, 0, abbr, res);
        
        return vector<string>(res.begin(), res.end());
    }
};
