#include <iostream>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>
#include <set>
// unordered_multiset here
#include <unordered_set>
#include <unordered_map>
#include <deque>
#include <set>
#include <map>
#include <algorithm>
#include <assert.h>
#include <numeric>
#include <list>
#include <stack>
#include <queue>
#include <cmath>
using namespace std;

/* 244. Shortest Word Distance II */

/* Solution 1 */
//class WordDistance {
//private:
//    // key: word, value: the indices of the word, in ascending order
//    unordered_map<string, deque<int>> wordIndicesDict;
//    int maxDistance;
//
//public:
//    WordDistance(vector<string>& wordsDict) {
//        maxDistance = int(wordsDict.size());
//        for (int i = 0; i < wordsDict.size(); ++i) {
//            string word = wordsDict[i];
//            auto dictIt = wordIndicesDict.find(word);
//            if (dictIt == wordIndicesDict.end()) {
//                wordIndicesDict.insert({word, deque<int>{i}});
//            } else {
//                dictIt->second.push_back(i);
//            }
//        }
//    }
//
//    int shortest(string word1, string word2) {
//        const deque<int>& word1IndicesDeque = wordIndicesDict.find(word1)->second;
//        const deque<int>& word2IndicesDeque = wordIndicesDict.find(word2)->second;
//
//        int minDistance = maxDistance;
//        for (const auto& i : word1IndicesDeque) {
//            auto upperBound = upper_bound(word2IndicesDeque.begin(), word2IndicesDeque.end(), i);
//            if (upperBound != word2IndicesDeque.end()) {
//                minDistance = min(minDistance, abs(i - *upperBound));
//            }
//            if (upperBound != word2IndicesDeque.begin()) {
//                minDistance = min(minDistance, abs(i - *(upperBound - 1)));
//            }
//        }
//        return minDistance;
//    }
//};

/* Solution 2: Time Limit Exceeded */
class WordDistance {
private:
    vector<string> words;
    
    bool isIndexValid(int index) {
        return index >= 0;
    }
    
public:
    WordDistance(vector<string>& wordsDict) {
        words = wordsDict;
    }
    
    int shortest(string word1, string word2) {
        int minDistance = int(words.size());
        int word1Index = -1;
        int word2Index = -1;
        
        for (int i = 0; i < words.size(); ++i) {
            if (words[i] == word1) {
                word1Index = i;
                if (isIndexValid(word2Index)) {
                    minDistance = min(minDistance, abs(word2Index - word1Index));
                }
                continue;
            }
            if (words[i] == word2) {
                word2Index = i;
                if (isIndexValid(word1Index)) {
                    minDistance = min(minDistance, abs(word2Index - word1Index));
                }
            }
        }
        return minDistance;
    }
};

int main() {
   
    return 0;
}

