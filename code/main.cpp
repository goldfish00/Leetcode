//
//  main.cpp
//  test
//
//  Created by Junyi Huang on 9/24/20.
//  Copyright © 2020 Junyi Huang. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <deque>
#include <set>
#include <map>
#include <algorithm>
#include <assert.h>
#include <numeric>
#include <list>
using namespace std;

/**
 * Definition for singly-linked list.
 */
struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };


/* #72 Edit Distance
    DP employed
 */
/*
class Solution {
private:
    vector<vector<int>> table;
    
    void initialize(size_t len1, size_t len2){
        vector<int> row(len2, 0);
        table = vector<vector<int>>(len1, row);
    }
    
public:
    int minDistance(string word1, string word2) {
        initialize(word1.length(), word2.length());
        
        return 0;
    }
};
*/

/* #76 */
/*
class Solution {
private:
    unordered_map<char, int> charMap;
    unordered_map<char, int> extraCharMap;
    deque<int> startInd;
    deque<int> currStringInd;
    int windowSize = 0;
    int windowStart = -1;
    
    void removeChar(char c){
        auto it = charMap.find(c);
        if (it != charMap.end()) {
            if (it->second == 1) charMap.erase(it);
            else it->second -= 1;
        }
    }
    
    //return true on success
    bool removeExtraChar(char c){
        auto it = extraCharMap.find(c);
        if (it == extraCharMap.end()) return false;
        if (it->second == 1) extraCharMap.erase(it);
        else it->second -= 1;
        return true;
    }
    
    void removeChar(unordered_map<char, int>::iterator it){
        if (it->second == 1) charMap.erase(it);
        else it->second -= 1;
    }
    
    void updateWindowSize(){
        int newWindowSize = currStringInd.back() - currStringInd.front() + 1;
        if (newWindowSize < windowSize) {
            windowSize = newWindowSize;
            windowStart = currStringInd.front();
        }
    }
    
    void removeExtraneous(const string& s){
        char c = s[currStringInd.front()];
        while (removeExtraChar(c)) {
            currStringInd.pop_front();
            c = s[currStringInd.front()];
        }
    }
    
    void iterate(const string& s, const string& t){
        if (startInd.size() < t.length()) {
            windowStart = 0;
            return;
        }

        //find the first window; not necessarily the minimum
        while (!startInd.empty()) {
            //check if window is complete
            if (charMap.empty()) break;
            char c = s[startInd.front()];
            auto it = charMap.find(c);
            if (it == charMap.end()) ++extraCharMap[c];
            else removeChar(it);
            //iterate
            currStringInd.push_back(startInd.front());
            startInd.pop_front();
        }
        //if found, set values
        if (charMap.empty()) {
            removeExtraneous(s);
            windowStart = currStringInd.front();
            windowSize = currStringInd.back() + 1 - windowStart;
            //the smallest situation
            if(windowSize == int(t.length())) return;
        }
        else {
            windowStart = 0;
            return;
        }
        
        //if found, search for smaller window
        while(!startInd.empty()){
            char prevChar = s[currStringInd.front()];
            currStringInd.pop_front();
            //if can update
            if (removeExtraChar(prevChar)) updateWindowSize();
            //find the next complete window by finding the next index on which the character is prevChar
            else{
                while (!startInd.empty()) {
                    currStringInd.push_back(startInd.front());
                    startInd.pop_front();
                    if (s[currStringInd.back()] == prevChar) {
                        //remove extraneous if possible
                        removeExtraneous(s);
                        updateWindowSize();
                        break;
                    }
                    else ++extraCharMap[s[currStringInd.back()]];
                }
            }
        }
    }
    
public:
    string minWindow(string s, string t) {
        //initialize the charMap
        for (auto c : t) ++charMap[c];
        //initialize the window
        int ind = 0;
        for (char c : s){
            auto it = charMap.find(c);
            if (it != charMap.end()) {
                startInd.push_back(ind);
            }
            ++ind;
        }
        iterate(s, t);
        return s.substr(windowStart , windowSize);
    }
};*/

/* #77 */
/*
class Solution {
private:
    vector<vector<int>> results;
    vector<int> result;
    
    void permutation(deque<int>& nums, int k){
        if (k == 0) {
            results.push_back(result);
            return;
        }
        
        for (size_t i = 0; i < nums.size(); ++i) {
            //consider combination only
            if (!result.empty()){
                if (result.back() > nums.front()){
                    nums.push_back(nums.front());
                    nums.pop_front();
                    continue;
                }
            }
            result.push_back(nums.front());
            nums.pop_front();
            permutation(nums, k - 1);
            nums.push_back(result.back());
            result.pop_back();
        }
    }
    
    
public:
    vector<vector<int>> combine(int n, int k) {
        deque<int> nums;
        nums.resize(n);
        result.reserve(k);
        iota(nums.begin(), nums.end(), 1);
        
        permutation(nums, k);
        
        return results;
    }
};*/

/* #78 */
/*
class Solution {
private:
    vector<vector<int>> Subsets;
    vector<int> subset;
    
    void genPower(vector<int>& nums, size_t i){
        if (i == nums.size() - 1) {
            Subsets.push_back(subset);
            subset.push_back(nums.back());
            Subsets.push_back(subset);
            subset.pop_back();
            return;
        }
        
        genPower(nums, i + 1);
        subset.push_back(nums[i]);
        genPower(nums, i + 1);
        subset.pop_back();
    }
    
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        genPower(nums, 0);
        
        return Subsets;
    }
};*/

/* 79 *//*
class Solution {
private:
    set<pair<int, int>> markedCell;
    int m = 0;
    int n = 0;
    
    bool notAlreadyMarked(const pair<int, int>& coor){
        return markedCell.find(coor) == markedCell.end();
    }
    
    void genPossibilities(const pair<int, int>& coor, vector<pair<int, int>>& possibilities){
        //up
        if (coor.first != 0 && notAlreadyMarked(make_pair(coor.first - 1, coor.second))) possibilities.push_back(make_pair(coor.first - 1, coor.second));
        //down
        if (coor.first != m - 1 && notAlreadyMarked(make_pair(coor.first + 1, coor.second))) possibilities.push_back(make_pair(coor.first + 1, coor.second));
        //left
        if (coor.second != 0 && notAlreadyMarked(make_pair(coor.first, coor.second - 1))) possibilities.push_back(make_pair(coor.first, coor.second - 1));
        //right
        if (coor.second != n - 1 && notAlreadyMarked(make_pair(coor.first, coor.second + 1))) possibilities.push_back(make_pair(coor.first, coor.second + 1));
    }
    
    bool existFromInd(const vector<vector<char>>& board, size_t ind, const pair<int, int>& coor, const string& word){
        //if all the char's are matched
        if (ind == word.length()) return true;
        //recursion
        vector<pair<int, int>> possibilities;
        genPossibilities(coor, possibilities);
        while (! possibilities.empty()) {
            pair<int, int> coorPair = possibilities.back();
            possibilities.pop_back();
            if (board[coorPair.first][coorPair.second] == word[ind]) {
                markedCell.insert(coorPair);
                if(existFromInd(board, ind + 1, coorPair, word)) return true;
                markedCell.erase(coorPair);
            }
        }
        return false;
    }
    
public:
    bool exist(vector<vector<char>>& board, string word) {
        m = int(board.size());
        n = int(board[0].size());
        
        for (int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j){
                if (board[i][j] == word[0]) {
                    pair<int, int> coor(i, j);
                    markedCell.insert(coor);
                    if(existFromInd(board, 1, coor, word)) return true;
                    markedCell.erase(coor);
                }
            }
        }
        
        return false;
    }
};*/

/* #80 */
/*
class Solution {
private:
    void remove(vector<int>& nums){
        //edge case. Now can assume that the number of integers is greater than 3
        if(nums.size() < 3) return;
        
        int count = 0;
        
        auto iter1 = nums.begin();
        auto iter2 = iter1;
        auto writingPlace = iter1;
        
        while (iter2 != nums.end()) {
            if (count == 2){
                if (*iter2 == *iter1) ++iter2;
                else{
                    *writingPlace = *iter2;
                    count = 1;
                    iter1 = iter2;
                    ++writingPlace;
                    ++iter2;
                }
            }
            else{
                //update
                if (*iter2 == *iter1) {
                    ++count;
                }
                else{
                    count = 1;
                    iter1 = iter2;
                }
                
                if (writingPlace != iter2) *writingPlace = *iter2;
                ++writingPlace;
                ++iter2;
            }
        }
        
        //remove the remains at the tail of the vector
        while (nums.end() != writingPlace) {
            nums.pop_back();
        }
    }
    
public:
    int removeDuplicates(vector<int>& nums) {
        remove(nums);
        
        return int(nums.size());
    }
};*/

/* #82 *//*
class Solution {
private:
    bool removeDulplicate(ListNode*& start){
        if (start == nullptr) return false;
        ListNode* end = start->next;
        while (end != nullptr) {
            if (end->val != start->val) {
                break;
            }
            end = end->next;
        }
        if (end == start->next) return false;
        //clean
        while (start != end) {
            ListNode* freeNode = start;
            start = start->next;
            delete freeNode;
        }
        return true;
    }
    
public:
    ListNode* deleteDuplicates(ListNode* head) {
        while(removeDulplicate(head));
        if (head == nullptr) return head;
        ListNode* currentNode = head;
        ListNode* nextNode = head->next;
        while (nextNode != nullptr) {
            if (removeDulplicate(nextNode)){
                currentNode->next = nextNode;
                if (nextNode == nullptr) break;
            }
            else{
                currentNode = nextNode;
                nextNode = nextNode->next;
            }
        }
        return head;
    }
};*/

/* #86 *//*
class Solution {
private:
    ListNode* firstLast = nullptr;
    ListNode* secondLast = nullptr;
    
    void addToFirst(ListNode* next){
        assert(firstLast != nullptr);
        firstLast->next = next;
        firstLast = next;
    }
    
    void addToSecond(ListNode* next){
        assert(secondLast != nullptr);
        secondLast->next = next;
        secondLast = next;
    }
    
    void merge(ListNode* secondFirst){
        assert(firstLast != nullptr);
        firstLast->next = secondFirst;
        if(secondLast != nullptr) secondLast->next = nullptr;
    }
    
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode* firstPart = nullptr;
        ListNode* secondPart = nullptr;
        
        while(head != nullptr){
            if (head->val < x) {
                if(firstPart == nullptr){
                    firstPart = head;
                    firstLast = head;
                }
                else addToFirst(head);
            }
            else{
                if (secondPart == nullptr){
                    secondPart = head;
                    secondLast = head;
                }
                else addToSecond(head);
            }
            head = head->next;
        }
        if (firstLast == nullptr) {
            return secondPart;
        }
        merge(secondPart);
        return firstPart;
    }
};*/

/* #88# *//*
class Solution {
public:
    bool isScramble(string s1, string s2) {
        
    }
};*/

/* #89 *//*
class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> results;
        results.reserve(1 << n);
        
        results.push_back(0);
        results.push_back(1);
        if (n == 1) return results;
        
        results.push_back(3);
        results.push_back(4);
        if (n == 2) return results;
        
        for(int i = 3; i <= n; ++i){
            //seperate the 2^n numbers into two halves
            int firstHalf = 1 << (i - 2);
            int secondHalf = firstHalf;
            firstHalf += firstHalf << 1;
            
            for (int iterNum = 0; iterNum < secondHalf; ++iterNum) {
                results.push_back(results[iterNum] + firstHalf);
            }
            
            for (int iterNum = secondHalf; iterNum < secondHalf << 1; ++iterNum) {
                results.push_back(results[iterNum] + secondHalf);
            }
        }
        
        return results;
    }
};*/

/* #90 *//*
class Solution {
private:
    unordered_map<int, int> dict;
    
    void initialize_dict(vector<int>& nums){
        for(auto num : nums) ++dict[num];
    }
    
    int get_subset_num(){
        int num = 1;
        for(const auto& pair : dict){
            num *= pair.second;
        }
        return num;
    }
    
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        initialize_dict(nums);
        
        vector<vector<int>> results;
        results.reserve(get_subset_num());
        //initialize the empty set
        results.resize(1);
        
        //generate subsets
        for(const auto& pair : dict){
            int initialNum = int(results.size());
            
            for (int i = 0; i < initialNum; ++i) {
                vector<int> result = results[i];
                
                for(int j = 0; j < pair.second; ++j){
                    result.push_back(pair.first);
                    results.push_back(result);
                }
            }
        }
        
        return results;
    }
};*/

/* #91 DP employed */ /*
class Solution {
private:
    vector<int> numPossibility;
    
    //the substring ranges from [ind + 1 - length, ind]
    bool isValid(const string& s, int ind, size_t length){
        if (length == 1) {
            return s[ind] != '0';
        }
        //length == 2
        else {
            if (s[ind - 1] == '0') return false;
            return stoi(s.substr(ind - 1, 2)) < 27;
        }
    }
    
public:
    int numDecodings(string s) {
        //initialize
        if (s[0] == '0') return 0;
        if (s.length() == 1) return 1;
        
        numPossibility.resize(s.length());
        numPossibility[0] = 1;
        //initialize
        if (isValid(s, 1, 1)) numPossibility[1] += 1;
        if (isValid(s, 1, 2)) numPossibility[1] += 1;
        
        for (int i = 2; i < int(s.length()); ++i) {
            if (s[i - 1] == 0 && s[i - 2] == 0) return 0;
            if(isValid(s, i, 1)) numPossibility[i] += numPossibility[i - 1];
            if(isValid(s, i, 2)) numPossibility[i] += numPossibility[i - 2];
        }
        
        return numPossibility.back();
    }
};*/

/* #92 *//*
class Solution {
private:
    // Divide the linked list as
    //head ... leftEnd1 LeftEnd2 ... RightEnd1 RightEnd2
                        //left        right
     //
    ListNode* newHead = nullptr;
    ListNode* leftEnd1 = nullptr;
    ListNode* leftEnd2 = nullptr;
    ListNode* rightEnd1 = nullptr;
    ListNode* rightEnd2 = nullptr;
    
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        //edge case
        if (left == right) return head;
        if (head->next == nullptr) return head;
        //check newHead
        if (left != 1) newHead = head;
        else leftEnd2 = head;
        
        ListNode* prev = head;
        head = head->next;
        int position = 2;
        
        while (head != nullptr) {
            ListNode* next = head->next;
            //left not found
            if (leftEnd2 == nullptr) {
                //find left
                if (position == left){
                    leftEnd1 = prev;
                    leftEnd2 = head;
                }
            }
            //left already found
            else{
                //right not found
                if (rightEnd1 == nullptr){
                    //reverse
                    head->next = prev;
                    //check if is right
                    if (position == right){
                        rightEnd1 = head;
                        rightEnd2 = next;
                        break;
                    }
                }
            }
            prev = head;
            head = next;
            ++position;
        }
        
        //merge and return
        leftEnd2->next = rightEnd2;
        if (newHead == nullptr) return rightEnd1;
        else {
            leftEnd1->next = rightEnd1;
            return newHead;
        }
    }
};*/

/* #93 *//*
class Solution {
private:
    vector<string> possibilities;
    string possibility;
    
    //length can only be 1, 2, 3
    bool isValid(const string& s, size_t startInd, size_t length, int numDots){
        if (startInd + length > s.length()) return false;
        if (length == 0) return false;
        if (s[startInd] == '0' && length != 1) return false;
        string rest = s.substr(startInd, length);
        if(stoi(rest) <= 255){
            possibility.append(rest);
            if (numDots < 3) possibility.push_back('.');
            else possibilities.push_back(possibility);
            return true;
        }
        return false;
    }
    
    void backTrack(const string& s, size_t startInd, int numDots){
        if (numDots == 3) {
            if (isValid(s, startInd, s.length() - startInd, numDots)){
                possibility.erase(startInd + numDots);
            }
            return;
        }
        
        if (isValid(s, startInd, 1, numDots)){
            backTrack(s, startInd + 1, numDots + 1);
            possibility.erase(startInd + numDots);
        }
        
        if (isValid(s, startInd, 2, numDots)){
            backTrack(s, startInd + 2, numDots + 1);
            possibility.erase(startInd + numDots);
        }
        
        if (isValid(s, startInd, 3, numDots)){
            backTrack(s, startInd + 3, numDots + 1);
            possibility.erase(startInd + numDots);
        }
    }
    
public:
    vector<string> restoreIpAddresses(string s) {
        if (s.length() > 12) return possibilities;
        backTrack(s, 0, 0);
        return possibilities;
    }
};*/

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };


/* # 94 *//* iteration method *//*
class Solution {
private:
    vector<TreeNode*> stack;
    vector<int> nums;
public:
    vector<int> inorderTraversal(TreeNode* root) {
        while (root != nullptr) {
            stack.push_back(root);
            root = root->left;
        }
        
        while (!stack.empty()) {
            TreeNode* currentNode = stack.back();
            stack.pop_back();
            nums.push_back(currentNode->val);
            currentNode = currentNode->right;
            while (currentNode != nullptr) {
                stack.push_back(currentNode);
                currentNode = currentNode->left;
            }
        }
        
        return nums;
    }
};*/

/* #95 *//*
class Solution {
private:
    
    
public:
    vector<TreeNode*> generateTrees(int n) {
        
    }
};*/

/* #96 *//* Method 1: Recursion -- took too long*//*
class Solution {
private:
    //range from [left, right]
    int numSubTress(int left, int right){
        if (left >= right) return 1;
        int num = 0;
        
        for (int i = left; i <= right; ++i) {
            num += numSubTress(left, i - 1) * numSubTress(i + 1, right);
        }
        
        return num;
    }
    
public:
    int numTrees(int n) {
        return numSubTress(1, n);
    }
    
};*/

/* #96 *//* Method 2: DP *//*
class Solution {
private:
    //treeNums[n] denotes the # of subtrees given the range[i, i + n]
    vector<int> treeNums;
    
    void calculate(){
        treeNums[0] = 1;
        for (int i = 1; i < treeNums.size(); ++i) {
            for (int j = 0; j <= i; ++j){
                if (j == 0) treeNums[i] += treeNums[i - 1];
                else if (j == i) treeNums[i] += treeNums[i - 1];
                else treeNums[i] += treeNums[j - 1] * treeNums[i - j - 1];
            }
        }
    }
    
public:
    int numTrees(int n) {
        treeNums.resize(n);
        calculate();
        return treeNums.back();
    }
};*/

int main(){
    Solution S;
    //vector<string> words{"zzyy","zy","zyy"};
    //vector<vector<char>> board{{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}};
    //vector<int> nums{0,0,0,1,2,2,4,4};
    S.restoreIpAddresses("1111111");
    return 0;
}
