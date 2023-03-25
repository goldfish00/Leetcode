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
#include <map>
using namespace std;

/* 288. Unique Word Abbreviation */
class ValidWordAbbr {
private:
    unordered_map<string, string> abbrWordDict; // key: abbr, val: word
    
    string genAbbr(const string& word) {
        if (word.size() < 3) {
            return word;
        }
        
        string s;
        s.reserve(4);
        s.push_back(word.front());
        s += to_string(word.size() - 2);
        s.push_back(word.back());
        return s;
    }
    
public:
    ValidWordAbbr(vector<string>& dictionary) {
        for (const string& word : dictionary) {
            string abbr = genAbbr(word);
            auto it = abbrWordDict.find(abbr);
            if (it == abbrWordDict.end()) {
                abbrWordDict.insert({abbr, word});
            } else if (it->second == word) {
                continue;
            } else {
                it->second = "";
            }
        }
    }
    
    bool isUnique(string word) {
        string abbr = genAbbr(word);
        auto it = abbrWordDict.find(abbr);
        if (it == abbrWordDict.end()) {
            return true;
        }
        if (it->second == word) {
            return true;
        }
        return false;
    }
};

