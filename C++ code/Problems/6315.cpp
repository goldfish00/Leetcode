/* 6315. Count the Number of Vowel Strings in Range */
class Solution {
private:
    const unordered_set<char> vowals{'a', 'e', 'i', 'o', 'u'};
    
    bool isVowalWord(const string& word) {
        if (vowals.find(word.front()) == vowals.end()) {
            return false;
        }
        if (vowals.find(word.back()) == vowals.end()) {
            return false;
        }
        return true;
    }
    
public:
    int vowelStrings(vector<string>& words, int left, int right) {
        int numVowel = 0;
        for (int i = left; i <= right; ++i) {
            if (isVowalWord(words[i])) {
                ++numVowel;
            }
        }
        return numVowel;
    }
};
