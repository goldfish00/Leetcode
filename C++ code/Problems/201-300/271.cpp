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

/* 269. Alien Dictionary */
//class Solution {
//public:
//    string alienOrder(vector<string>& words) {
//
//    }
//};

/* 271. Encode and Decode Strings */
// 0 <= strs[i].length <= 200
/*
 The basic idea: since the length is no greater than 200, for every string to serialize, we can store
 the length of it using three char and then read according to the length
 */
class Codec {
private:
    string produceThreeByteLen(size_t len) {
        string lenS = to_string(len);
        return string(3 - lenS.length(), '0') + lenS;
    }
    
public:
    // Encodes a list of strings to a single string.
    string encode(vector<string>& strs) {
        string serializedS;
        // calculate the space that needs to reserve
        size_t serializedLen = 0;
        for (const string& s : strs) {
            serializedLen += 3 + s.length();
        }
        serializedS.reserve(serializedLen);
        
        for (const string& s : strs) {
            serializedS += produceThreeByteLen(s.length()) + s;
        }
        return serializedS;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(string s) {
        vector<string> strs;
        string str;
        for (auto it = s.begin(); it != s.end();) {
            // read the length
            int len = stoi(string(it, it + 3));
            str.clear();
            str.reserve(len);
            it += 3;
            auto strEndIt = it + len;
            
            for (; it != strEndIt; ++it) {
                str.push_back(*it);
            }
            strs.push_back(str);
        }
        return strs;
    }
};

