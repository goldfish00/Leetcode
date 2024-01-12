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

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/* 201. Bitwise AND of Numbers Range *//*
class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {
        
    }
};*/


/* #202 Happy Number*//*
class Solution {
private:
    unordered_set<int> records;
    
    int getNext(int n){
        int next = 0;
        while (n != 0) {
            int mod10 = n % 10;
            next += mod10 * mod10;
            n = n / 10;
        }
        return next;
    }
    
public:
    bool isHappy(int n) {
        while (n != 1) {
            if (records.find(n) != records.end()) {
                return false;
            }
            records.insert(n);
            n = getNext(n);
        }
        return true;
    }
};*/

/* #203 Remove Linked List Elements*//*
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
private:
    // Erase the node->next and return the new node->next.
    void erase(ListNode* node){
        if (!node->next) return;
        ListNode* newNext = node->next->next;
        delete node->next;
        node->next = newNext;
    }
    
public:
    ListNode* removeElements(ListNode* head, int val) {
        if (!head) return head;
        ListNode* dummy = new ListNode(0, head);
        head = dummy;
        while (head->next) {
            if (head->next->val == val) erase(head);
            else head = head->next;
        }
        head = dummy->next;
        delete dummy;
        return head;
    }
};*/

/* #204 Count Primes*/
/* Timed-out*//*
class Solution {
private:
    unordered_set<int> primes;
    
    bool isPrime(int n) {
        int upper = int(sqrt(n));
        for (auto prime : primes) {
            if (prime > upper) continue;
            if (n % prime == 0) return false;
        }
        return true;
    }
    
public:
    int countPrimes(int n) {
        if (n < 2) return 0;
        int count = 0;
        for (int i = 2; i < n; ++i) {
            if (isPrime(i)){
                ++count;
                primes.insert(i);
            }
        }
        return count;
    }
};*/
/*
class Solution {
public:
    int countPrimes(int n) {
        if (n <= 1) return 0;
        vector<bool> isPrime(n, true);
        isPrime[0] = false;
        for (int i = 1; i < n; ++i) {
            if (!isPrime[i]) continue;;
            int nonPrime = (i + 1) * 2;
            while (nonPrime <= n) {
                if(isPrime[nonPrime - 1]) isPrime[nonPrime - 1] = false;
                nonPrime += i + 1;
            }
        }
        
        int count = 0;
        for (auto i : isPrime) {
            if (i) ++count;
        }
        return count;
    }
};*/

/* #205. Isomorphic Strings *//*
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if (s.length() != t.length()) return false;
        if (s.length() == 0) return true;
        
        unordered_map<char, char> sToT;
        unordered_set<char> usedT;
        for (size_t i = 0; i < s.length(); ++i) {
            auto it = sToT.find(s[i]);
            if (it == sToT.end()){
                sToT[s[i]] = t[i];
                if (usedT.find(t[i]) != usedT.end()) return false;
                usedT.insert(t[i]);
            }
            else {
                if (it->second != t[i]) return false;
            }
        }
        return true;
    }
};*/

/* #209 Minimum Size Subarray Sum *//*
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int min_len = INT_MAX;
        // mark the starting index and the sum ending in the current index i [starting ind, i], for dp[i] s.t. the sum is closest to the target
        vector<pair<int, int>> dp(nums.size());
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] >= target) return 1;
            if (i == 0) {
                dp[i] = make_pair(i, nums[i]);
                continue;
            }
        
            dp[i] = make_pair(dp[i - 1].first, dp[i - 1].second + nums[i]);
            if (dp[i].second < target) {
                continue;
            }
            // shrinking the sliding window if largestSum > target if possible
            while (dp[i].second - nums[dp[i].first] >= target) {
                dp[i].second -= nums[dp[i].first];
                ++dp[i].first;
            }
            min_len = min(min_len, i + 1 - dp[i].first);
        }
        
        if (min_len == INT_MAX) return 0;
        return min_len;
    }
};*/

/* 210. Course Schedule II *//*
class Solution {
private:
    // the i-th row records all the prerequisite for course i
    vector<unordered_set<int>> prereqRelation;
    unordered_set<int> learnedCourses;
    vector<int> learnSchedule;
    
    void addToSchedule(int courseId){
        if (learnedCourses.find(courseId) == learnedCourses.end()){
            learnSchedule.push_back(courseId);
        }
    }
    
    bool canFinishSub(int courseId, unordered_set<int>& courses){
        // base case
        if (prereqRelation[courseId].empty()) return true;
        if (learnedCourses.find(courseId) != learnedCourses.end()){
            for (int preqId : prereqRelation[courseId]){
                if (courses.find(preqId) != courses.end()) return false;
            }
            return true;
        }
        // keep DFS
        courses.insert(courseId);
        for (auto preqId : prereqRelation[courseId]) {
            if (courses.find(preqId) != courses.end()) return false;
            if (!canFinishSub(preqId, courses)) return false;
            addToSchedule(preqId);
            learnedCourses.insert(preqId);
        }
        courses.erase(courseId);
        addToSchedule(courseId);
        learnedCourses.insert(courseId);
        return true;
    }
    
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        prereqRelation.resize(numCourses);
        for (const auto& pairReq : prerequisites) prereqRelation[pairReq.front()].insert(pairReq.back());
        
        for (int courseId = 0; courseId < numCourses; ++courseId) {
            if (prereqRelation[courseId].empty()) continue;
            if (learnedCourses.find(courseId) != learnedCourses.end()) continue;
            
            unordered_set<int> visited;
            if (!canFinishSub(courseId, visited)) return vector<int>{};
        }
        
        for (int courseId = 0; courseId < numCourses; ++courseId) {
            if (learnedCourses.find(courseId) == learnedCourses.end()){
                learnSchedule.push_back(courseId);
            }
        }
        return learnSchedule;
    }
};*/

/* #211 Design Add and Search Words Data Structure */
/* Method 1: Recursion: Tiime Exceeded*/
//class WordDictionary {
//private:
//    unordered_set<string> words;
//    char charA;
//    char charDot;
//
//    bool searchForPossibility(string& word, string::iterator itStart) {
//        for (auto it = itStart; it != word.end(); ++it) {
//            if (*it == charDot) {
//                for (int i = 0; i < 26; ++i) {
//                    *it = charA + i;
//                    if (searchForPossibility(word, it + 1)) {
//                        return true;
//                    }
//                }
//                *it = charDot;
//            }
//        }
//
//        return words.find(word) != words.end();
//    }
//
//public:
//    WordDictionary() {
//        charA = 'a';
//        charDot = '.';
//    }
//
//    void addWord(string word) {
//        words.insert(word);
//    }
//
//    bool search(string word) {
//        return searchForPossibility(word, word.begin());
//    }
//};

//class TrieCell {
//private:
//    TrieCell* nextEntry;
//    bool hasWord;
//
//    static void clear(TrieCell* cell) {
//        if (!cell->nextEntry) {
//            return;
//        }
//        for (int i = 0; i < 26; ++i) {
//            clear(cell->nextEntry + i);
//        }
//        delete[] cell->nextEntry;
//        cell->nextEntry = nullptr;
//    }
//
//    void genNextEntry() {
//        nextEntry = new TrieCell[26];
//    }
//
//    bool hasNextEntryInitialized() {
//        return nextEntry != nullptr;
//    }
//
//    /** Be sure that hasNextEntryInitialized is used before this one.
//     */
//    bool hasCharInNextEntry(const char& c) {
//        return nextEntry[int(c - 'a')].hasWord;
//    }
//
//public:
//    TrieCell(){
//        nextEntry = nullptr;
//        hasWord = false;
//    }
//
//    ~TrieCell(){
////        cout << "Trie Cell destructor called";
//        clear(this);
//    }
//
//    TrieCell* getNextEntryCellByChar(const char& c) {
//        if (!hasNextEntryInitialized()) {
//            genNextEntry();
//        }
//        return nextEntry + int(c - 'a');
//    }
//
//    void setExistingCharOnNextEntry(const char& c) {
//        if (!hasNextEntryInitialized()) {
//            genNextEntry();
//        }
//        nextEntry[int(c - 'a')].hasWord = true;
//    }
//
//    bool has(const string& word, int startInd) {
//        if (startInd == word.length()) {
//            return true;
//        }
//
//        if(!hasNextEntryInitialized()) {
//            return false;
//        }
//        char curChar = word[startInd];
//        if (startInd + 1 == word.length()) {
//            if (curChar == '.') {
//                for(int i = 0; i < 26; ++i) {
//                    if ((nextEntry + i)->hasWord) {
//                        return true;
//                    }
//                }
//                return false;
//            } else {
//                return hasCharInNextEntry(curChar);
//            }
//        }
//
//        if (curChar == '.') {
//            for(int i = 0; i < 26; ++i) {
//                if ((nextEntry + i)->has(word, startInd + 1)) {
//                    return true;
//                }
//            }
//            return false;
//        } else {
//            return (nextEntry + int(curChar - 'a'))->has(word, startInd + 1);
//        }
//    }
//};
//
//class Trie {
//private:
//    TrieCell* root;
//    int depth;
//
//public:
//    Trie() {
//        depth = 0;
//        root = new TrieCell;
//    }
//
//    ~Trie() {
//        delete root;
//    }
//
//    void add(const string& word) {
//        TrieCell* secondLastEntry = root;
//        for (int i = 0; i < word.length() - 1; ++i) {
//            secondLastEntry = secondLastEntry->getNextEntryCellByChar(word[i]);
//        }
//        secondLastEntry->setExistingCharOnNextEntry(word.back());
//
//        if (word.length() > depth) {
//            depth = int(word.length());
//        }
//    }
//
//    bool has(const string& word) {
//        if (word.length() > depth) {
//            return false;
//        }
//
//        return root->has(word, 0);
//    }
//};
//
//class WordDictionary {
//private:
//    Trie trie;
//
//public:
//    WordDictionary() {
//
//    }
//
//    void addWord(string word) {
//        trie.add(word);
//    }
//
//    bool search(string word) {
//        return trie.has(word);
//    }
//};

//void testTrie() {
//    WordDictionary* obj = new WordDictionary();
//    obj->addWord("bad");
//    obj->addWord("dad");
//    obj->addWord("mad");
//    obj->search("pad");
//    obj->search("bad");
//    obj->search(".ad");
//    obj->search("b..");
//    delete obj;
//}

/* 212. Word Search II */
//class Solution {
//private:
//    unordered_map<char, vector<pair<int, int>>> startingPosByChar;
//    int rowNum;
//    int colNum;
//
//    struct vector_hash{
//        std::size_t operator () (std::pair<int, int> const &v) const {
//            return std::hash<int>()(v.first * v.second + v.first);
//        }
//    };
//
//    void initializeStaringPosByChar(vector<vector<char>>& board) {
//        for (int i = 0; i < rowNum; ++i) {
//            for (int j = 0; j < colNum; ++j) {
//                startingPosByChar[board[i][j]].push_back({i, j});
//            }
//        }
//    }
//
//    vector<pair<int, int>> surroundingPos(const pair<int, int>& pos) {
//        vector<pair<int, int>> results;
//        if (pos.first != 0) {
//            results.push_back({pos.first - 1, pos.second});
//        }
//        if (pos.first + 1 != rowNum) {
//            results.push_back({pos.first + 1, pos.second});
//        }
//        if (pos.second != 0) {
//            results.push_back({pos.first, pos.second - 1});
//        }
//        if (pos.second + 1 != colNum) {
//            results.push_back({pos.first, pos.second + 1});
//        }
//        return results;
//    }
//
//    bool canFindWord(vector<vector<char>>& board, unordered_set<pair<int, int>, vector_hash>& existingCharPos, pair<int, int> lastPos, const string& word) {
//        if (existingCharPos.size() == word.length()) {
//            return true;
//        }
//
//        char nextChar = word[existingCharPos.size()];
//        for (const auto& pos : surroundingPos(lastPos)) {
//            if (existingCharPos.find(pos) != existingCharPos.end()) {
//                continue;
//            }
//            if (board[pos.first][pos.second] != nextChar) {
//                continue;
//            }
//            existingCharPos.insert(pos);
//            if (canFindWord(board, existingCharPos, pos, word)) {
//                return true;
//            }
//            existingCharPos.erase(pos);
//        }
//        return false;
//    }
//
//    bool hasWord(vector<vector<char>>& board, const string& word) {
//        auto firstCharPossiblePos = startingPosByChar[word[0]];
//        if (firstCharPossiblePos.empty()) {
//            return false;
//        }
//
//        unordered_set<pair<int, int>, vector_hash> existingChasPos;
//        for (const auto& pos : firstCharPossiblePos) {
//            existingChasPos.insert(pos);
//            if (canFindWord(board, existingChasPos, pos, word)) {
//                return true;
//            }
//            existingChasPos.erase(pos);
//        }
//        return false;
//    }
//
//public:
//    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
//        vector<string> results;
//
//        rowNum = int(board.size());
//        colNum = int(board[0].size());
//        initializeStaringPosByChar(board);
//
//        for (const string& word : words) {
//            if (hasWord(board, word)) {
//                results.push_back(word);
//            }
//        }
//        return results;
//    }
//};
//
//int main(){
//    Solution S;
//    vector<vector<char>> board{
//        {'o', 'a', 'a', 'n'},
//        {'e', 't', 'a', 'e'},
//        {'i', 'h', 'k', 'r'}
//    };
//    vector<string> words{"oath","pea","eat","rain"};
//    S.findWords(board, words);
//    return 0;
//}


/* 213. House Robber II */
//class Solution {
//private:
//    int robWithIndex(const vector<int>& nums, int startInd, int endInd) {
//        vector<int> maxRobValue(2);
//        maxRobValue[0] = nums[startInd];
//        maxRobValue[1] = max(maxRobValue[0], nums[startInd + 1]);
//        for(int i = startInd + 2; i <= endInd; ++i) {
//            int maxCur = max(maxRobValue[1], maxRobValue[0] + nums[i]);
//            maxRobValue[0] = maxRobValue[1];
//            maxRobValue[1] = maxCur;
//        }
//        return max(maxRobValue[0], maxRobValue[1]);
//    }
//
//public:
//    int rob(vector<int>& nums) {
//        if (nums.size() == 1) {
//            return nums[0];
//        }
//        if (nums.size() == 2) {
//            return max(nums[0], nums[1]);
//        }
//
//        return max(robWithIndex(nums, 0, int(nums.size() - 2)), robWithIndex(nums, 1, int(nums.size() - 1)));
//    }
//};

/* 214. Shortest Palindrome */
//class Solution {
//public:
//    string shortestPalindrome(string s) {
//        if (s.length() == 0 || s.length() == 1) {
//            return s;
//        }
//
//        int halfLength = int(s.length()) / 2;
//        int centricPossibilities = (s.length() % 2) ? (halfLength + 1) : halfLength;
//        int maxLengh = 0;
//        int maxIndex = 0;
//        for (int i = centricPossibilities - 1; i >= 0; --i) {
//            int curLength = 0;
//            bool allMatch = true;
//
//            for (int j = 0; j <= i; ++j) { //even
//                if (s[j] != s[2 * i + 1 - j]) {
//                    allMatch = false;
//                    break;
//                }
//            }
//            if (allMatch) {
//                maxLengh = 2 * i + 2;
//                maxIndex = i;
//                break;
//            }
//
//            allMatch = true;
//            for(int j = 0; j < i; ++j) { //odd
//                if (s[j] != s[2 * i - j]) {
//                    allMatch = false;
//                    break;
//                }
//            }
//            if (allMatch) {
//                maxLengh = 2 * i + 1;
//                maxIndex = i;
//                break;
//            }
//        }
//
//        string result(2 * int(s.length()) - maxLengh, 'a');
//        int newPalindromeLength = (int(s.length()) - maxLengh);
//        auto it = copy(s.rbegin(), s.rbegin() + newPalindromeLength, result.begin());
//        copy(s.begin(), s.end(), it);
//        return result;
//    }
//};

//class Solution {
//public:
//    string shortestPalindrome(string s) {
//        if (s.length() == 0 || s.length() == 1) {
//            return s;
//        }
//
//        auto endIter = s.end() - 1;
//        while (endIter != s.begin()) {
//            auto frontIter = s.begin();
//            auto behindIter = endIter;
//            while (1) {
//                if (*frontIter != *behindIter) {
//                    endIter = endIter - 1;
//                    break;
//                }
//                if (behindIter == frontIter) {
//                    int resultLen = int(s.end() - frontIter) * 2 - 1;
//                    string result(resultLen, 'a');
//                    auto firstHalf = copy(s.rbegin(), s.rbegin() + int(s.end() - frontIter), result.begin());
//                    copy(frontIter + 1, s.end(), firstHalf);
//                    return result;
//                }
//                if (frontIter + 1 == behindIter) {
//                    int resultLen = int(s.end() - behindIter) * 2;
//                    string result(resultLen, 'a');
//                    auto firstHalf = copy(s.rbegin(), s.rbegin() + int(s.end() - frontIter) - 1, result.begin());
//                    copy(behindIter, s.end(), firstHalf);
//                    return result;
//                }
//                ++frontIter;
//                --behindIter;
//            }
//        }
//
//        string result(2 * s.length() - 1, 'a');
//        auto firstHalf = copy(s.rbegin(), s.rend(), result.begin());
//        copy(s.begin() + 1, s.end(), firstHalf);
//        return result;
//    }
//};
//
//int main() {
//    Solution S;
//    S.shortestPalindrome("abbacd");
//    return 0;
//}

/* 215. Kth Largest Element in an Array */
//class Solution {
//public:
//    int findKthLargest(vector<int>& nums, int k) {
//
//    }
//};

/* 216. Combination Sum III */
//class Solution {
//private:
//    void combinationSum(int numNumber, int smallestNumber, int sum, vector<int>& result, vector<vector<int>>& results) {
//        if (smallestNumber > 9) {
//            return;
//        }
//        if (sum < 0) {
//            return;
//        }
//        if ((numNumber == 0) && (sum == 0)) {
//            results.push_back(result);
//            return;
//        }
//        if (numNumber == 1) {
//            if ((sum > 0) && (sum < 10) && (sum >= smallestNumber)) {
//                result.push_back(sum);
//                results.push_back(result);
//                result.pop_back();
//            }
//            return;
//        }
//
//        combinationSum(numNumber, smallestNumber + 1, sum, result, results);
//
//
//        result.push_back(smallestNumber);
//        combinationSum(numNumber - 1, smallestNumber + 1, sum - smallestNumber, result, results);
//        result.pop_back();
//    }
//
//public:
//    vector<vector<int>> combinationSum3(int k, int n) {
//        vector<vector<int>> results;
//
//        if (n > 9 * k || n < k) {
//            return results;
//        }
//
//        vector<int> result;
//        combinationSum(k, 1, n, result, results);
//        return results;
//    }
//};
//
//int main(){
//    Solution S;
//    auto results = S.combinationSum3(3, 7);
//    for (const auto& result : results) {
//        for (auto number : result) {
//            cout << number << " ";
//        }
//        cout << "\n";
//    }
//
//    return 0;
//}


/* 217. Contains Duplicate */
//class Solution {
//private:
//    class IntCmpLess {
//    public:
//        bool operator()(int left, int right) {
//            return left < right;
//        }
//    };
//
//public:
//    bool containsDuplicate(vector<int>& nums) {
//        if (nums.size() < 2) {
//            return false;
//        }
//
//        IntCmpLess less;
//        sort(nums.begin(), nums.end(), less);
//        for (auto it = nums.begin(); it != nums.end() - 1; ++it) {
//            if (*it == *(it + 1)) {
//                return true;
//            }
//        }
//        return false;
//    }
//};

/* 218. The Skyline Problem */
//class Solution {
//private:
//    class WindowCmpLess {
//    public:
//        bool operator()(const vector<int>& left, const vector<int>& right) {
//            return left[1] < right[0];
//        }
//    };
//
//    class HeightCmpGreater {
//    public:
//        bool operator()(const vector<int>& left, const vector<int>& right) {
//            return left[2] > right[2];
//        }
//    };
//
//    void addSlices(deque<vector<int>>& slicesBuildingQueue, const vector<int>& building, WindowCmpLess& winCmp) {
//        if (slicesBuildingQueue.empty()) {
//            slicesBuildingQueue.push_back(building);
//            return;
//        }
//
//        auto lowerBound = lower_bound(slicesBuildingQueue.begin(), slicesBuildingQueue.end(), building, winCmp);
//        if (lowerBound == slicesBuildingQueue.end()) {
//            slicesBuildingQueue.push_back(building);
//            return;
//        }
//
//        auto upperBound = upper_bound(lowerBound, slicesBuildingQueue.end(), building, winCmp);
//        if (upperBound == slicesBuildingQueue.begin()) {
//            slicesBuildingQueue.push_front(building);
//            return;
//        }
//
//        for (auto it = lowerBound; it != upperBound;) {
//            auto nextIt = it + 1;
//            if (it == lowerBound && building[0] < (*it)[0]) {
//                slicesBuildingQueue.insert(it, {building[0], (*it)[0], building[2]});
//            }
//
//            int newStart = max(building[0], (*it)[1]);
//            if (nextIt == slicesBuildingQueue.end()) {
//                if (newStart < building[1]) {
//                    slicesBuildingQueue.push_back({newStart, building[1], building[2]});
//                }
//                break;
//            }
//
//            int newEnd = min((*nextIt)[0], building[1]);
//            if (newStart < newEnd) {
//                slicesBuildingQueue.insert(nextIt, {newStart, newEnd, building[2]});
//                ++nextIt;
//                if (upperBound != slicesBuildingQueue.end()) {
//                    ++upperBound;
//                }
//            }
//
//            it = nextIt;
//        }
//    }
//
//public:
//    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
//        if (buildings.size() == 1) {
//            auto building = buildings[0];
//            return {{building[0], building[2]}, {building[1], 0}};
//        }
//
//        WindowCmpLess winCmp;
//        HeightCmpGreater heightCmp;
//        sort(buildings.begin(), buildings.end(), heightCmp);
//
//        deque<vector<int>> slicesBuildingQueue;
//        for (const vector<int>& building : buildings) {
//            if (building[2] == 1329 && building[0] == 1329) {
//                cout << "I think something's wrong here";
//            }
//            addSlices(slicesBuildingQueue, building, winCmp);
//        }
//
//        vector<vector<int>> results;
//        int prevHeight = -1;
//        int prevRightBorder = -1;
//        for (const auto& buildingBlock : slicesBuildingQueue) {
//            if (prevHeight < 0) { // initialize
//                prevHeight = buildingBlock[2];
//                prevRightBorder = buildingBlock[1];
//                results.push_back({buildingBlock[0], prevHeight});
//                continue;
//            }
//
//            if (buildingBlock[2] == prevHeight && buildingBlock[0] == prevRightBorder) {
//                prevRightBorder = buildingBlock[1];
//                continue;
//            }
//
//            if (buildingBlock[0] != prevRightBorder) {
//                results.push_back({prevRightBorder, 0});
//            }
//            prevHeight = buildingBlock[2];
//            results.push_back({buildingBlock[0], prevHeight});
//            prevRightBorder = buildingBlock[1];
//        }
//        results.push_back({prevRightBorder, 0});
//        return results;
//    }
//};
//
//int main() {
//    vector<vector<int>> buildings{{1329,1672,1329},{1330,1671,1330},{1331,1670,1331},{1332,1669,1332},{1333,1668,1333},{1334,1667,1334},{1335,1666,1335},{1336,1665,1336},{1337,1664,1337},{1338,1663,1338},{1339,1662,1339},{1340,1661,1340},{1341,1660,1341},{1342,1659,1342},{1343,1658,1343},{1344,1657,1344},{1345,1656,1345},{1346,1655,1346},{1347,1654,1347},{1348,1653,1348},{1349,1652,1349},{1350,1651,1350},{1351,1650,1351},{1352,1649,1352},{1353,1648,1353},{1354,1647,1354},{1355,1646,1355},{1356,1645,1356},{1357,1644,1357},{1358,1643,1358},{1359,1642,1359},{1360,1641,1360},{1361,1640,1361},{1362,1639,1362},{1363,1638,1363},{1364,1637,1364},{1365,1636,1365},{1366,1635,1366},{1367,1634,1367},{1368,1633,1368},{1369,1632,1369},{1370,1631,1370},{1371,1630,1371},{1372,1629,1372},{1373,1628,1373},{1374,1627,1374},{1375,1626,1375},{1376,1625,1376},{1377,1624,1377},{1378,1623,1378},{1379,1622,1379},{1380,1621,1380},{1381,1620,1381},{1382,1619,1382},{1383,1618,1383},{1384,1617,1384},{1385,1616,1385},{1386,1615,1386},{1387,1614,1387},{1388,1613,1388},{1389,1612,1389},{1390,1611,1390},{1391,1610,1391},{1392,1609,1392},{1393,1608,1393}};
//    Solution S;
//    S.getSkyline(buildings);
//}

/* 219. Contains Duplicate II */
//class Solution {
//public:
//    bool containsNearbyDuplicate(vector<int>& nums, int k) {
//        unordered_set<int> windowValues;
//
//        // initialize window values
//        for (int i = 0; i <= k; ++i) {
//            if (i == nums.size()) {
//                return false;
//            }
//
//            int currentVal = nums[i];
//            if (windowValues.find(currentVal) != windowValues.end()) {
//                return true;
//            }
//            windowValues.insert(currentVal);
//        }
//
//        // slide the windows
//        for (int i = k + 1, j = 0; i < nums.size(); ++i, ++j) {
//            windowValues.erase(nums[j]);
//
//            int currentVal = nums[i];
//            if (windowValues.find(currentVal) != windowValues.end()) {
//                return true;
//            }
//            windowValues.insert(currentVal);
//        }
//
//        return false;
//    }
//};

/* 220. Contains Duplicate III *//* Time exceeded */
//class Solution {
//private:
//    int valDiff = 0;
//    deque<int> nearbyValues;
//
//    bool findOrInsert(int val) {
//        if (nearbyValues.empty()) {
//            nearbyValues.push_back(val);
//            return false;
//        }
//
//        // use binary search
//        auto upperIt = upper_bound(nearbyValues.begin(), nearbyValues.end(), val, less<int>());
//        if (upperIt != nearbyValues.end()) {
//            if (*upperIt - val <= valDiff) {
//                return true;
//            }
//        }
//        if (upperIt != nearbyValues.begin()) {
//            if (val - *(upperIt - 1) <= valDiff) {
//                return true;
//            }
//        }
//
//        nearbyValues.insert(upperIt, val);
//        return false;
//    }
//
//    void removeValue(int val) {
//        auto it = find(nearbyValues.begin(), nearbyValues.end(), val);
//        nearbyValues.erase(it);
//    }
//
//public:
//    bool containsNearbyAlmostDuplicate(vector<int>& nums, int indexDiff, int valueDiff) {
//        // initialize
//        valDiff = valueDiff;
//        nearbyValues.clear();
//
//        // the first k+1 values
//        for (int i = 0; i <= indexDiff; ++i) {
//            if (i == nums.size()) {
//                return false;
//            }
//
//            if (findOrInsert(nums[i])) {
//                return true;
//            }
//        }
//
//        // sliding the window
//        for (int newValIndex = indexDiff + 1, indexToLeave = 0; newValIndex < nums.size(); ++newValIndex, ++indexToLeave) {
//            removeValue(nums[indexToLeave]);
//
//            if(findOrInsert(nums[newValIndex])) {
//                return true;
//            }
//        }
//
//        return false;
//    }
//};

//class Solution {
//private:
//    int valDiff = 0;
//    set<int, less<int>> nearbyValues;
//
//    bool findOrInsert(int val) {
//        if (nearbyValues.empty()) {
//            nearbyValues.insert(val);
//            return false;
//        }
//
//        // use binary search
//        auto upperIt = upper_bound(nearbyValues.begin(), nearbyValues.end(), val, less<int>());
//        if (upperIt != nearbyValues.end()) {
//            if (*upperIt - val <= valDiff) {
//                return true;
//            }
//        }
//        if (upperIt != nearbyValues.begin()) {
//            auto lowerIt = next(upperIt, -1);
//            if (val - *lowerIt <= valDiff) {
//                return true;
//            }
//        }
//
//        nearbyValues.insert(upperIt, val);
//        return false;
//    }
//
//public:
//    bool containsNearbyAlmostDuplicate(vector<int>& nums, int indexDiff, int valueDiff) {
//        // initialize
//        valDiff = valueDiff;
//        nearbyValues.clear();
//
//        // the first k+1 values
//        for (int i = 0; i <= indexDiff; ++i) {
//            if (i == nums.size()) {
//                return false;
//            }
//
//            if (findOrInsert(nums[i])) {
//                return true;
//            }
//        }
//
//        // sliding the window
//        for (int newValIndex = indexDiff + 1, indexToLeave = 0; newValIndex < nums.size(); ++newValIndex, ++indexToLeave) {
//            nearbyValues.erase(nums[indexToLeave]);
//
//            if(findOrInsert(nums[newValIndex])) {
//                return true;
//            }
//        }
//
//        return false;
//    }
//};

//int main() {
//    vector<int> nums{1,5,9,1,5,9};
//    Solution S;
//    S.containsNearbyAlmostDuplicate(nums, 2, 3);
//
//    return 0;
//}

/* 222. Count Complete Tree Nodes */
//struct TreeNode {
//     int val;
//     TreeNode *left;
//     TreeNode *right;
//     TreeNode() : val(0), left(nullptr), right(nullptr) {}
//     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
//     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
//};
//
//class Solution {
//public:
//    int countNodes(TreeNode* root) {
//        
//    }
//};

/* 223. Rectangle Area */
//class Solution {
//private:
//    class Range {
//    private:
//        int startCoor;
//        int endCoor;
//
//    public:
//        Range(int startCoor, int endCoor): startCoor(startCoor), endCoor(endCoor) {}
//
//        int overlapLength(Range range) {
//            if (range.Start() >= endCoor || range.End() <= startCoor) {
//                return 0;
//            }
//
//            return min(endCoor, range.End()) - max(startCoor, range.Start());
//        }
//
//        int Start() {
//            return startCoor;
//        }
//
//        int End() {
//            return endCoor;
//        }
//    };
//
//    class Point {
//    private:
//        int x;
//        int y;
//    public:
//        Point(int x, int y): x(x), y(y) {}
//
//        int X() {
//            return x;
//        }
//
//        int Y() {
//            return y;
//        }
//    };
//
//    class Rectangle {
//    private:
//        Point buttomLeftPt;
//        Point topRightPt;
//
//        Range xRange() {
//            return Range(buttomLeftPt.X(), topRightPt.X());
//        }
//
//        Range yRange() {
//            return Range(buttomLeftPt.Y(), topRightPt.Y());
//        }
//
//    public:
//        Rectangle(Point buttomLeftPt, Point topRightPt): buttomLeftPt(buttomLeftPt), topRightPt(topRightPt){}
//
//        bool doesContain(Point pt) {
//            return pt.X() >= buttomLeftPt.X() && pt.X() <= topRightPt.X()
//                && pt.Y() >= buttomLeftPt.Y() && pt.Y() <= topRightPt.Y();
//        }
//
//        int overlapArea(Rectangle rect) {
//            return rect.xRange().overlapLength(xRange()) * rect.yRange().overlapLength(yRange());
//        }
//
//        int area() {
//            return (topRightPt.X() - buttomLeftPt.X()) * (topRightPt.Y() - buttomLeftPt.Y());
//        }
//    };
//
//public:
//    int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2) {
//        Rectangle R1(Point(ax1, ay1), Point(ax2, ay2));
//        Rectangle R2(Point(bx1, by1), Point(bx2, by2));
//
//        return R1.area() + R2.area() - R1.overlapArea(R2);
//    }
//};
//
//int main() {
//    Solution S;
//    S.computeArea(-3, 0, 3, 4, 0, -1, 9, 2);
//
//    return 0;
//}


/* 224. Basic Calculator */
//class Solution {
//private:
//    bool isMinus(const char& c) {
//        return c == '-';
//    }
//
//    bool isPlus(const char& c) {
//        return c == '+';
//    }
//
//    bool isLeftBracket(const char& c) {
//        return c == '(';
//    }
//
//    bool isRightBracket(const char& c) {
//        return c == ')';
//    }
//
//    bool isSpace(const char& c) {
//        return c == ' ';
//    }
//
//    void calc(int& result, int& curNumber, int curOperator) {
//        if (curOperator == 1) {
//            result += curNumber;
//            curNumber = 0;
//        } else if (curOperator == 2) {
//            result -= curNumber;
//            curNumber = 0;
//        }
//    }
//
//    int calculateWithBracket(string s, size_t& startInd) {
//        int result = 0;
//        int curNumber = 0;
//        int curOperator = 1; // 1 for plus and 2 for minus
//
//        while (startInd < s.length()) {
//            char c = s[startInd];
//
//            if (isSpace(c)) {
//                ++startInd;
//            } else if (isdigit(c)) {
//                curNumber = curNumber * 10 + int(c - '0');
//                ++startInd;
//            } else if (isPlus(c)) {
//                calc(result, curNumber, curOperator);
//                curOperator = 1;
//                ++startInd;
//            } else if (isMinus(c)) {
//                calc(result, curNumber, curOperator);
//                curOperator = 2;
//                ++startInd;
//            } else if (isLeftBracket(c)) {
//                ++startInd;
//                curNumber = calculateWithBracket(s, startInd);
//            } else if (isRightBracket(c)) {
//                calc(result, curNumber, curOperator);
//                ++startInd;
//                return result;
//            }
//        }
//
//        calc(result, curNumber, curOperator);
//        return result;
//    }
//
//public:
//    int calculate(string s) {
//        size_t startInd = 0;
//        // let's pretend that there is a left bracket at the start of s
//        return calculateWithBracket(s, startInd);
//    }
//};
//
//int main() {
//    Solution S;
//    S.calculate("(1+(4+5+2)-3)+(6+8)");
//}

/* 225. Implement Stack using Queues */
//class MyStack {
//private:
//    list<int> q1; // try to keep the top elements in q1
//    list<int> q2; // and keep the rest element in q2, in FIFO order
//
//public:
//    MyStack() {
//
//    }
//
//    void push(int x) {
//        if (q1.empty()) {
//            q1.push_back(x);
//        } else {
//            q1.push_back(x);
//            q2.push_back(q1.front());
//            q1.pop_front();
//        }
//    }
//
//    int pop() {
//        if(!q1.empty()) {
//            int front = q1.front();
//            q1.pop_front();
//            return front;
//        }
//
//        if (q2.size() == 1) {
//            int front = q2.front();
//            q2.pop_front();
//            return front;
//        }
//
//        while (q2.size() > 1) {
//            q1.push_back(q2.front());
//            q2.pop_front();
//        }
//        int front = q2.front();
//        q2.pop_front();
//        swap(q1, q2);
//        return front;
//    }
//
//    int top() {
//        if(!q1.empty()) {
//            int front = q1.front();
//            return front;
//        }
//
//        if (q2.size() == 1) {
//            int front = q2.front();
//            return front;
//        }
//
//        while (q2.size() > 1) {
//            q1.push_back(q2.front());
//            q2.pop_front();
//        }
//        int front = q2.front();
//        swap(q1, q2);
//        return front;
//    }
//
//    bool empty() {
//        return q1.empty() && q2.empty();
//    }
//};
//
//int main() {
//    MyStack S;
//    S.push(1);
//    S.push(2);
//    S.top();
//
//    return 0;
//}

/* 226. Invert Binary Tree */
//struct TreeNode {
//     int val;
//     TreeNode *left;
//     TreeNode *right;
//     TreeNode() : val(0), left(nullptr), right(nullptr) {}
//     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
//     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
//};
//
//class Solution {
//public:
//    TreeNode* invertTree(TreeNode* root) {
//        if (!root) {
//            return nullptr;
//        }
//
//        swap(root->left, root->right);
//
//        if (root->left) invertTree(root->left);
//        if (root->right) invertTree(root->right);
//
//        return root;
//    }
//};

/* 227. Basic Calculator II */
//class Solution {
//private:
//    bool isMinus(const char& c) {
//        return c == '-';
//    }
//
//    bool isPlus(const char& c) {
//        return c == '+';
//    }
//
//    bool isMultiple(const char& c) {
//        return c == '*';
//    }
//
//    bool isDivision(const char& c) {
//        return c == '/';
//    }
//
//    bool isSpace(const char& c) {
//        return c == ' ';
//    }
//
//    bool isOperator(const char& c) {
//        return isMinus(c) || isPlus(c) || isMultiple(c) || isDivision(c);
//    }
//
//    bool isOperatorPrioritized(const char& c) {
//        return isMultiple(c) || isDivision(c);
//    }
//
//    int getResult(int a, int b, char c) {
//        if (isMinus(c)) {
//            return a - b;
//        }
//        if (isPlus(c)) {
//            return a + b;
//        }
//        if (isMultiple(c)) {
//            return a * b;
//        }
//        // division
//        return a / b;
//    }
//
//    int readInt(const string& s, size_t& startInd) {
//        int curNumber = 0;
//        while (isdigit(s[startInd])) {
//            curNumber = curNumber * 10 + int(s[startInd] - '0');
//            ++startInd;
//        }
//        return curNumber;
//    }
//
//public:
//    int calculate(string s) {
//        deque<int> numbers;
//        deque<char> operators;
//
//        // read the string
//        size_t startInd = 0;
//        operators.push_back('+');
//        while (startInd < s.length()) {
//            char c = s[startInd];
//            if (isSpace(c)) {
//                ++startInd;
//                continue;
//            }
//            if (isOperator(c)) {
//                operators.push_back(c);
//                ++startInd;
//                continue;
//            }
//            // digit
//            numbers.push_back(readInt(s, startInd));
//        }
//
//        // start calculating
//        int result = 0;
//        while (!operators.empty()) {
//            char currentOperator = operators.front();
//            operators.pop_front();
//
//            int a = numbers.front();
//            numbers.pop_front();
//
//            if (operators.empty() || isOperatorPrioritized(currentOperator)) {
//                result = getResult(result, a, currentOperator);
//                continue;
//            }
//
//            char prevOperator = operators.front();
//            if (isOperatorPrioritized(prevOperator)) {
//                operators.pop_front();
//                int b = numbers.front();
//                numbers.pop_front();
//                numbers.push_front(getResult(a, b, prevOperator));
//                operators.push_front(currentOperator);
//                continue;
//            }
//
//            result = getResult(result, a, currentOperator);
//        }
//
//        return result;
//    }
//};

//int main(){
//    Solution S;
//    S.calculate("1-1+1");
//
//    return 0;
//}

/* 228. Summary Ranges */
//class Solution {
//public:
//    vector<string> summaryRanges(vector<int>& nums) {
//        vector<string> results;
//        if (nums.empty()) {
//            return results;
//        }
//
//        int prevStart = nums.front();
//        for (int i = 0; i < nums.size() - 1; ++i) {
//            if(nums[i] + 1 != nums[i + 1]) {
//                if (nums[i] == prevStart) {
//                    results.push_back(std::to_string(prevStart));
//                } else {
//                    results.push_back(std::to_string(prevStart) + "->" + std::to_string(nums[i]));
//                }
//                prevStart = nums[i + 1];
//            }
//        }
//
//        if (nums.back() == prevStart) {
//            results.push_back(std::to_string(prevStart));
//        } else {
//            results.push_back(std::to_string(prevStart) + "->" + std::to_string(nums.back()));
//        }
//
//        return results;
//    }
//};

/* 229. Majority Element II */
//class Solution {
//public:
//    vector<int> majorityElement(vector<int>& nums) {
//        unordered_map<int, int> numCount;
//
//        for (const int& i : nums) {
//            ++numCount[i];
//        }
//
//        int threshold = int(nums.size()) / 3;
//        vector<int> result;
//        for(const auto& keyValPair: numCount) {
//            if (keyValPair.second > threshold) {
//                result.push_back(keyValPair.first);
//            }
//        }
//        return result;
//    }
//};


/* 230. Kth Smallest Element in a BST */
//struct TreeNode {
//    int val;
//    TreeNode *left;
//    TreeNode *right;
//    TreeNode() : val(0), left(nullptr), right(nullptr) {}
//    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
//    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
//};
//
///* Recursive Solution calculating everything */
//class Solution {
//private:
//    unordered_map<TreeNode*, int> nodeRankDict; // node - k th smallest
//    unordered_map<TreeNode*, int> nodeNumDict; // node - number of nodes under the node
//
//    int getNum(TreeNode* node) {
//        if (!node) {
//            return 0;
//        }
//
//        if (nodeNumDict.find(node) != nodeNumDict.end()) {
//            return nodeNumDict[node];
//        }
//
//        nodeNumDict[node] = 1 + getNum(node->left) + getNum(node->right);
//        return nodeNumDict[node];
//    }
//
//    int getRank(TreeNode* node) {
//        if (!node) {
//            return 0;
//        }
//        if (!node->left) {
//            if (nodeRankDict.find(node->left) == nodeRankDict.end()) nodeRankDict[node] = 1;
//            return 1;
//        }
//
//        if (nodeRankDict.find(node) != nodeRankDict.end()) {
//            return nodeRankDict[node];
//        }
//
//        nodeRankDict[node] = getRank(node->left) + getNum(node->left->right) + 1;
//        return nodeRankDict[node];
//    }
//
//    int kthSmallestRecur(TreeNode* root, int k) {
//        int curRank = getRank(root);
//        if (curRank == k) {
//            return root->val;
//        }
//
//        if (curRank < k) {
//            return kthSmallest(root->right, k - curRank);
//        }
//
//        // curRank > k
//        return kthSmallest(root->left, k);
//    }
//
//public:
//    int kthSmallest(TreeNode* root, int k) {
//        nodeRankDict.clear();
//        return kthSmallestRecur(root, k);
//    }
//};

/* Use of Inorder Traversal */
//class Solution {
//private:
//    int targetK;
//
//    TreeNode* inorderTraverseAndFind(TreeNode* root) {
//        if (!root) {
//            return nullptr;
//        }
//
//        TreeNode* leftFind = inorderTraverseAndFind(root->left);
//        if (leftFind) return leftFind;
//
//        --targetK;
//        if (targetK == 0) {
//            return root;
//        }
//
//        TreeNode* rightFind = inorderTraverseAndFind(root->right);
//        return rightFind;
//    }
//
//public:
//    int kthSmallest(TreeNode* root, int k) {
//        targetK = k;
//        return inorderTraverseAndFind(root)->val;
//    }
//};

/* 231. Power of Two */
//class Solution {
//public:
//    bool isPowerOfTwo(int n) {
//        if (n <= 0) {
//            return false;
//        }
//
//        if (n == 1) {
//            return true;
//        }
//
//        if (n % 2 == 0) {
//            return isPowerOfTwo(n / 2);
//        }
//
//        return false;
//    }
//};

/* 232. Implement Queue using Stacks */
//class MyStack {
//private:
//    deque<int> container;
//
//public:
//    MyStack(){}
//
//    void push(int n) {
//        container.push_back(n);
//    }
//
//    int& front() {
//        return container.back();
//    }
//
//    void pop() {
//        return container.pop_back();
//    }
//
//    size_t size() {
//        return container.size();
//    }
//
//    bool empty() {
//        return container.empty();
//    }
//};
//
//class MyQueue {
//private:
//    MyStack head; // head stack is popping in the right order as a queue
//    MyStack tail; // keep the rest of the elements here
//
//    void buildHead() {
//        while (!tail.empty()) {
//            head.push(tail.front());
//            tail.pop();
//        }
//    }
//
//public:
//    MyQueue() {}
//
//    void push(int x) {
//        if (empty()) {
//            head.push(x);
//        } else {
//            tail.push(x);
//        }
//    }
//
//    int pop() {
//        if (!head.empty()) {
//            int ele = head.front();
//            head.pop();
//            return ele;
//        }
//
//        buildHead();
//        int ele = head.front();
//        head.pop();
//        return ele;
//    }
//
//    int peek() {
//        if (!head.empty()) {
//            return head.front();
//        }
//
//        buildHead();
//        return head.front();
//    }
//
//    bool empty() {
//        return head.empty() && tail.empty();
//    }
//};
//
//int main() {
//    MyQueue queue;
//    queue.push(1);
//    queue.push(2);
//    queue.push(3);
//    queue.pop();
//    queue.push(5);
//    queue.pop();
//
//    return 0;
//}

/* 233. Number of Digit One */
//class Solution {
//public:
//    int countDigitOne(int n) {
//        int numLevel = 1;
//        int num1 = 0;
//
//        while (n / numLevel != 0 && numLevel != 1000000000) {
//            int nextNumberLevel = numLevel * 10;
//            int header = n / nextNumberLevel;
//            int currentDigit = (n / numLevel) % 10;
//
//            if (numLevel == 1) {
//                num1 += (currentDigit == 0) ? header * numLevel : (header + 1) * numLevel;
//            } else {
//                switch (currentDigit) {
//                    case 0: // header won't be zero in this case; otherwise the while loop should be broken
//                        num1 += header * numLevel;
//                        break;
//
//                    case 1:
//                        if (header == 0) {
//                            num1 += n % numLevel + 1;
//                        } else {
//                            num1 += int(n / nextNumberLevel) * numLevel + n % numLevel + 1;
//                        }
//                        break;
//
//                    default:
//                        if (header == 0) {
//                            num1 += numLevel;
//                        } else {
//                            num1 += (int(n / nextNumberLevel) + 1) * numLevel;
//                        }
//                        break;
//                }
//            }
//
//            numLevel = nextNumberLevel;
//        }
//
//        if (n == 1000000000) {
//            num1 += 1;
//        }
//
//        return num1;
//    }
//};
//
//int main() {
//    Solution S;
//    S.countDigitOne(1000000000);
//    return 0;
//}

/* 234. Palindrome Linked List */
//struct ListNode {
//     int val;
//     ListNode *next;
//     ListNode() : val(0), next(nullptr) {}
//     ListNode(int x) : val(x), next(nullptr) {}
//     ListNode(int x, ListNode *next) : val(x), next(next) {}
// };
//
//class Solution {
//public:
//    bool isPalindrome(ListNode* head) {
//        // find the middle one while storing the found node into the stack
//        ListNode* slowPtr = head;
//        ListNode* fastPtr = head->next;
//        deque<int> valueStack;
//
//        while (fastPtr) {
//            valueStack.push_back(slowPtr->val);
//            slowPtr = slowPtr->next;
//
//            fastPtr = fastPtr->next;
//            if (!fastPtr) {
//                break;
//            }
//            fastPtr = fastPtr->next;
//            if (!fastPtr) {
//                slowPtr = slowPtr->next;
//                break;
//            }
//        }
//
//        // check for palindrome
//        while (slowPtr && !valueStack.empty()) {
//            if (slowPtr->val != valueStack.back()) {
//                return false;
//            }
//            slowPtr = slowPtr->next;
//            valueStack.pop_back();
//        }
//
//        return true;
//    }
//};

/* 237. Delete Node in a Linked List */
//class Solution {
//public:
//    void deleteNode(ListNode* node) {
//        ListNode* prevNode = node;
//        while (node->next) {
//            node->val = node->next->val;
//            prevNode = node;
//            node = node->next;
//        }
//
//        prevNode->next = nullptr;
//        delete node;
//    }
//};

/* 238. Product of Array Except Self */
//class Solution {
//public:
//    vector<int> productExceptSelf(vector<int>& nums) {
//        vector<int> prefixProduct;
//        vector<int> surfixProduct;
//        prefixProduct.resize(nums.size());
//        surfixProduct.resize(nums.size());
//
//        // produce prefix product
//        for(int i = 0; i < nums.size(); ++i) {
//            if (i == 0) {
//                prefixProduct[i] = 1;
//                continue;
//            }
//            prefixProduct[i] = prefixProduct[i - 1] * nums[i - 1];
//        }
//
//        // produce surfic product
//        for (int i = int(nums.size()) - 1; i >= 0; --i) {
//            if (i == int(nums.size()) - 1) {
//                surfixProduct[i] = 1;
//                continue;
//            }
//            surfixProduct[i] = surfixProduct[i + 1] * nums[i + 1];
//        }
//
//        // generate result using prefix table
//        for (int i = 0; i < nums.size(); ++i) {
//            prefixProduct[i] *= surfixProduct[i];
//        }
//
//        return prefixProduct;
//    }
//};
//
//int main() {
//    Solution S;
//    vector<int> nums{1, 2, 3, 4};
//    S.productExceptSelf(nums);
//    return 0;
//}

/* 239. Sliding Window Maximum */
//class Solution {
//public:
//    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
//        multiset<int, std::less<int>> windowNums;
//        vector<int> maxWindows;
//        maxWindows.reserve(nums.size() - k + 1);
//
//        // initialize the windowNums to the greatest
//        for (int i = 0; i < k; ++i) {
//            windowNums.insert(nums[i]);
//        }
//        // initialize the first max ele in maxWindows
//        maxWindows.push_back(*prev(windowNums.end()));
//
//        for (int i = k, j = 0; i < nums.size(); ++i, ++j) {
//            auto it = windowNums.find(nums[j]);
//            windowNums.erase(it);
//            windowNums.insert(nums[i]);
//
//            maxWindows.push_back(*prev(windowNums.end()));
//        }
//
//        return maxWindows;
//    }
//};
//
//int main() {
//    Solution S;
//    vector<int> nums{1,3,-1,-3,5,3,6,7};
//    S.maxSlidingWindow(nums, 3);
//    return 0;
//}

/* 241. Different Ways to Add Parentheses */
class Solution {
private:
    deque<char> operators;
    deque<int> numbers;
    vector<int> possibilities;
    
    bool isMinus(const char& c) {
        return c == '-';
    }

    bool isPlus(const char& c) {
        return c == '+';
    }

    bool isMultiple(const char& c) {
        return c == '*';
    }

    bool isDivision(const char& c) {
        return c == '/';
    }

    bool isOperator(const char& c) {
        return isMinus(c) || isPlus(c) || isMultiple(c) || isDivision(c);
    }

    int getResult(int a, int b, char c) {
        if (isMinus(c)) {
            return a - b;
        }
        if (isPlus(c)) {
            return a + b;
        }
        if (isMultiple(c)) {
            return a * b;
        }
        // division
        return a / b;
    }

    int readInt(const string& s, size_t& startInd) {
        int curNumber = 0;
        while (isdigit(s[startInd])) {
            curNumber = curNumber * 10 + int(s[startInd] - '0');
            ++startInd;
        }
        return curNumber;
    }
    
    deque<int>::iterator getCorrespondingNumberIter(deque<char>::iterator operatorIt) {
        return numbers.begin() + (operatorIt - operators.begin());
    }
    
    vector<int> genPossibilities(deque<char>::iterator operatorStart, deque<char>::iterator operatorEnd) {
        // base case 1: no operator
        if (operatorStart == operatorEnd) {
            return vector<int>{*getCorrespondingNumberIter(operatorStart)};
        }
        // base case 2: only 1 operator
        if (operatorStart + 1 == operatorEnd) {
            auto numberStartIt = getCorrespondingNumberIter(operatorStart);
            return vector<int>{getResult(*numberStartIt, *(numberStartIt + 1), *operatorStart)};
        }
        
        // else, iterate through all possibilities
        vector<int> possibilities;
        for (auto iterIt = operatorStart; iterIt != operatorEnd; ++iterIt) {
            vector<int> prevPossibilities = genPossibilities(operatorStart, iterIt);
            vector<int> followingPossibilities = genPossibilities(iterIt + 1, operatorEnd);
            for (auto &i : prevPossibilities) {
                for (auto &j : followingPossibilities) {
                    possibilities.push_back(getResult(i, j, *iterIt));
                }
            }
        }
        return possibilities;
    }
    
public:
    vector<int> diffWaysToCompute(string expression) {
        // read the numbers and operators
        for (size_t i = 0; i < expression.size();) {
            if (isOperator(expression[i])) {
                operators.push_back(expression[i]);
                ++i;
                continue;
            }
            numbers.push_back(readInt(expression, i));
        }
        assert(numbers.size() == operators.size() + 1);
        if (operators.size() == 0) {
            return vector<int>{numbers.front()};
        }
                
        return genPossibilities(operators.begin(), operators.end());
    }
};

int main() {
    Solution S;
    S.diffWaysToCompute("2-1-1");
    
    return 0;
}
