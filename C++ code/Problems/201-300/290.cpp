/* 290. Word Pattern */
/* Given a pattern and a string s, find if s follows the same pattern. pattern and s are same if:

    each character in pattern represents a word in s
    No two distinct characters in pattern can represent the same word in s
    No single character in pattern can represent two distinct words in s.

 */
class Solution {
private:
    bool isSpace(const char& c) {
        return c == ' ';
    }
    
    vector<string> parseWordBySpace(const string& s) {
        vector<string> words;
        auto start = s.begin();
        auto end = s.begin();
        while (end != s.end()) {
            if (!isSpace(*end)) {
                ++end;
                continue;
            }
            words.push_back(string(start, end));
            ++end;
            start = end;
        }
        words.push_back(string(start, end));
        
        return words;
    }
    
    // Union find
    vector<int> genWordMap(const string& s) {
        vector<string> words = parseWordBySpace(s);
        unordered_map<string, int> wordIndexDict; // key: word, val: the first index of the word
        for (int i = 0; i < words.size(); ++i) {
            const string& s = words[i];
            auto it = wordIndexDict.find(s);
            if (it == wordIndexDict.end()) {
                wordIndexDict.insert({s, i});
            }
        }
        
        vector<int> wordIndices;
        wordIndices.reserve(words.size());
        for (const string& word : words) {
            wordIndices.push_back(wordIndexDict[word]);
        }
        return wordIndices;
    }
    
public:
    bool wordPattern(string pattern, string s) {
        auto wordIndices = genWordMap(s);
        if (wordIndices.size() != pattern.length()) {
            return false;
        }
        
        unordered_map<char, int> patternWordDict; // key: char in pattern, val: index of word in the words vector
        for (int i = 0; i < wordIndices.size(); ++i) {
            const char& c = pattern[i];
            auto it = patternWordDict.find(c);
            if (it == patternWordDict.end()) { // not found
                if (wordIndices[i] != i) {
                    return false;
                }
                patternWordDict.insert({c, i});
            } else { // already there
                if (wordIndices[it->second] != wordIndices[i]) {
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    Solution S;
//    S.wordPattern("abba", "dog cat cat dog");
    S.wordPattern("deadbeef", "d e a d b e e f");
    return 0;
}

