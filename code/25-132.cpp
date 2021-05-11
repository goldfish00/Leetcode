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
#include <stack>
#include <queue>
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

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

/* #25 *//* Iterative *//*
class Solution {
public:
  ListNode* reverseKGroup(ListNode* head, int k) {
      if(head == nullptr) return head;
      if(k == 1) return head;
      ListNode* first = head;
      ListNode* last = head;
      ListNode* newHead = head;
      while(true){
          if(first == nullptr) return newHead;
          
          ListNode* iterPtr = first;
          for(int i = 0; i < k - 1; ++i){
              iterPtr = iterPtr->next;
              if(iterPtr == nullptr) return newHead;
          }
          
          //change head and tail
          ListNode* reverseHead = first;
          //last = first;
          ListNode* next = first->next;
          first->next = nullptr;
          ListNode* nextNext = nullptr;
          for(int i = 0; i < k - 1; ++i){
              nextNext = next->next;
              next->next = reverseHead;
              reverseHead = next;
              next = nextNext;
          }
          //update the head
          if(newHead == head) newHead = iterPtr;
          else{
              last = last->next;
              head->next = reverseHead;
              head = last;
          }
          first->next = nextNext;
          first = nextNext;
      }
      
      return newHead;
  }
};*/

/* #25 *//* Recursive *//*
class Solution {
public:
  ListNode* reverseKGroup(ListNode* head, int k) {
      // check edge cases
      if (k ==  0) return head;
      if (!head) return head;
      // check if there is k node, starting from head
      ListNode* end = head;
      for (int i = 0; i < k; ++i) {
          if (!end) return head;
          end = end->next;
      }
      // start reversing
      ListNode* tail = head;
      ListNode* reversed = head;
      head = head->next;
      while (head != end) {
          ListNode* temp = head->next;
          head->next = reversed;
          reversed = head;
          head = temp;
      }
      tail->next = reverseKGroup(end, k);
      return reversed;
  }
};*/

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

/* # 94 *//* iteration method *//*
class Solution {
private:
    stack<TreeNode*> Stack;
    vector<int> nums;
public:
    vector<int> inorderTraversal(TreeNode* root) {
        while (root != nullptr) {
            Stack.push(root);
            root = root->left;
        }
        
        while (!Stack.empty()) {
            TreeNode* currentNode = Stack.top();
            Stack.pop();
            // this is for inorder traversal; left nodes comes first
            nums.push_back(currentNode->val);
            currentNode = currentNode->right;
            while (currentNode != nullptr) {
                Stack.push(currentNode);
                currentNode = currentNode->left;
            }
        }
        
        return nums;
    }
                                 
    //#144
    vector<int> preOrderTraversal(TreeNode* root){
        while (root) {
            Stack.push(root);
            //preorder traversal
            nums.push_back(root->val);
            root = root->left;
        }
        
        while(!Stack.empty()){
            //This node's value is already stored in the nums vector
            TreeNode* current = Stack.top();
            Stack.pop();
            current = current->right;
            while (current) {
                //preorder
                nums.push_back(current->val);
                Stack.push(current);
                current = current->left;
            }
        }
        
        return nums;
    }
    
    //#145
    vector<int> postOrderTraversal(TreeNode* root){
        while (root) {
            Stack.push(root);
            root = root->left;
        }
        
        while (!Stack.empty()) {
            TreeNode* current = Stack.top();
            if (current->right) {
                current = current->right;
                while (current) {
                    Stack.push(current);
                    current = current->left;
                }
            }
            else{
                Stack.pop();
                if (Stack.empty()) nums.push_back(current->val);
                else{
                    TreeNode* next = Stack.top();
                    nums.push_back(current->val);
                    while (next->right == current) {
                        current = next;
                        nums.push_back(current->val);
                        Stack.pop();
                        if (Stack.empty()) break;
                        else next = Stack.top();
                    }
                }
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

/* #97 *//* Using DP *//*
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if (s1.length() + s2.length() != s3.length()) return false;
        if (s1.empty() && s2.empty() && s3.empty()) return true;
        if (s1.empty()) return s2 == s3;
        if (s2.empty()) return s1 == s3;
        
        //initialize
        vector<vector<bool>> table(s2.length() + 1, vector<bool>(s1.length() + 1));
        table[0][0] = true;
        for (int i = 1; i <= s1.length(); ++i) {
            if (table[0][i - 1] && s1[i - 1] == s3[i -1]) table[0][i] = true;
            else table[0][i] = false;
        }
        for (int i = 1; i <= s2.length(); ++i) {
            if (table[i - 1][0] && s2[i - 1] == s3[i - 1]) table[i][0] = true;
            else table[i][0] = false;
        }
        
        for (int i = 1; i <= s2.length(); ++i) {
            for(int j = 1; j <= s1.length(); ++ j){
                if ((table[i - 1][j] && s2[i - 1] == s3[i + j - 1]) || (table[i][j - 1] && s1[j - 1] == s3[i + j - 1])) {
                    table[i][j] = true;
                }
                else table[i][j] = false;
            }
        }
        
        return table[s2.length()][s1.length()];
    }
};*/


/* #98 *//*
class Solution {
private:
    bool hadINTMIN = false;
    bool hadINTMAX = false;
    
    bool isValidRecur(TreeNode *root, int upperbound, int lowerbound){
        if (root == nullptr) return true;
        //check upperbound
        if (upperbound != INT_MAX && root->val >= upperbound) return false;
        else if (upperbound == INT_MAX && hadINTMAX && root->val == INT_MAX) return false;
        if (root->val == INT_MAX) hadINTMAX = true;
        //check lowerbound
        if (lowerbound != INT_MIN && root->val <= lowerbound) return false;
        else if (lowerbound == INT_MIN && hadINTMIN && root->val == INT_MIN) return false;
        if (root->val == INT_MIN) hadINTMIN = true;
        
        return isValidRecur(root->left, min(root->val, upperbound), lowerbound) && isValidRecur(root->right, upperbound, max(root->val, lowerbound));
    }
    
public:
    bool isValidBST(TreeNode* root) {
        if (root == nullptr) return true;
        if (root->val == INT_MIN) hadINTMIN = true;
        else if (root->val == INT_MAX) hadINTMAX = true;
        return isValidRecur(root->left, root->val, INT_MIN) && isValidRecur(root->right, INT_MAX, root->val);
    }
};*/

/* #101 *//*
class Solution {
private:
    bool isSymmetric(TreeNode* left, TreeNode* right){
        if (!left) return right == nullptr;
        if (!right) return left == nullptr;
        if (left->val == right->val) return isSymmetric(left->left, right->right) && isSymmetric(left->right, right->left);
        else return false;
    }
    
public:
    bool isSymmetric(TreeNode* root) {
        if (!root) return true;
        return isSymmetric(root->left, root->right);
    }
};*/

/* #102 *//*
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> layers;
        vector<int> layer;
        deque<TreeNode*> queue;
        TreeNode* start = nullptr;
        bool found = false;
        if (root) {
            queue.push_back(root);
            start = root;
            found = true;
        }
        
        while (!queue.empty()) {
            TreeNode* current = queue.front();
            if (current == start){
                if (!layer.empty()) layers.push_back(layer);
                layer.clear();
                found = false;
            }
            layer.push_back(current->val);
            queue.pop_front();
            if (current->left) {
                queue.push_back(current->left);
                if (!found) {
                    start = current->left;
                    found = true;
                }
            }
            if (current->right) {
                queue.push_back(current->right);
                if (!found) {
                    start = current->right;
                    found = true;
                }
            }
        }
        
        if (!layer.empty()) layers.push_back(layer);
        return layers;
    }
};*/


/* #103 *//*
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> layers;
        if (root == nullptr) return layers;
        vector<int> layer;
        int numNode = 1;
        int numNodeNext = 0;
        bool ascending = true;
        deque<TreeNode*> queue;
        queue.push_back(root);
        
        while (1) {
            if (numNode == 0){
                ascending = !ascending;
                layers.push_back(layer);
                layer.clear();
                if(!ascending) layer.resize(numNodeNext);
                if (queue.empty()) break;
                numNode = numNodeNext;
                numNodeNext = 0;
                continue;
            }
            TreeNode* current = queue.front();
            queue.pop_front();
            if (ascending) layer.push_back(current->val);
            else layer[numNode - 1] = current->val;
            //check the children
            if (current->left){
                queue.push_back(current->left);
                ++numNodeNext;
            }
            if (current->right) {
                queue.push_back(current->right);
                ++numNodeNext;
            }
            --numNode;
        }
        
        return layers;
    }
};*/


/* #104 *//* Iterative Method*//*
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (!root) return 0;
        deque<TreeNode*> queue;
        queue.push_back(root);
        int depth = 0;
        while (!queue.empty()) {
            ++depth;
            int numNode = int(queue.size());
            for (int i = 0; i < numNode; ++i) {
                TreeNode* current = queue.front();
                queue.pop_front();
                if (current->left) queue.push_back(current->left);
                if (current->right) queue.push_back(current->right);
            }
        }
        return depth;
    }
};*/


/* #105 */
/* Preorder: node -> left -> right
    Inorder: left -> ndoe -> right *//*
class Solution {
private:
    // key: node value; value: index in inorder traversal
    unordered_map<int, int> inorderMap;
    
    void initMap(vector<int>& inorder){
        for (int i = 0; i < int(inorder.size()); ++i) {
            inorderMap[inorder[i]] = i;
        }
    }
    
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (preorder.size() == 0) return nullptr;
        
        stack<TreeNode*> nodes;
        TreeNode* root = new TreeNode(preorder.front());
        nodes.push(root);
        initMap(inorder);
        
        for (int i = 1; i < int(preorder.size()); ++i) {
            TreeNode* current = new TreeNode(preorder[i]);
            //if to the left
            if (inorderMap[preorder[i]] < inorderMap[nodes.top()->val]){
                nodes.top()->left = current;
                nodes.push(current);
            }
            //if to the right
            else{
                TreeNode* middleNode = nodes.top();
                while (nodes.size() > 1) {
                    nodes.pop();
                    if (inorderMap[preorder[i]] < inorderMap[nodes.top()->val]){
                        middleNode->right = current;
                        nodes.push(current);
                        break;
                    }
                    middleNode = nodes.top();
                }
                if (nodes.size() == 1){
                    nodes.top()->right = current;
                    nodes.pop();
                    nodes.push(current);
                }
            }
        }
        
        return root;
    }
};*/


/* #106 */
/* Postorder: left -> right -> node
     Inorder: left -> ndoe -> right*//*
class Solution {
private:
    // key: node value; value: index in inorder traversal
    unordered_map<int, int> inorderMap;
    
    void initMap(vector<int>& inorder){
        for (int i = 0; i < int(inorder.size()); ++i) {
            inorderMap[inorder[i]] = i;
        }
    }
    
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if (inorder.size() == 0) return nullptr;
        initMap(inorder);
        stack<TreeNode*> nodes;
        TreeNode* root = new TreeNode(postorder.back());
        postorder.pop_back();
        nodes.push(root);
        while (!postorder.empty()) {
            //make new node
            TreeNode* current = new TreeNode(postorder.back());
            postorder.pop_back();
            // if to the right
            if (inorderMap[current->val] > inorderMap[nodes.top()->val]){
                nodes.top()->right = current;
                nodes.push(current);
            }
            // if to the left
            else{
                // find the node of which the current node is the left child
                TreeNode* possiblePar = nodes.top();
                while (nodes.size() > 1) {
                    nodes.pop();
                    // if to the right of the prev node, then left child of possiblePar
                    if (inorderMap[nodes.top()->val] < inorderMap[current->val]){
                        possiblePar->left = current;
                        nodes.push(current);
                        break;
                    }
                    else possiblePar = nodes.top();
                }
                if (nodes.size() == 1){
                    nodes.top()->left = current;
                    nodes.pop();
                    nodes.push(current);
                }
            }
        }
        
        return root;
    }
};*/


/* #107 *//*
class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        if (!root) return vector<vector<int>>();
        deque<vector<int>> layers;
        vector<int> layer;
        deque<TreeNode*> nodes;
        nodes.push_back(root);
        int numNode = 1;
        
        while (!nodes.empty()) {
            int numNodeNext = 0;
            for (int i = 0; i < numNode; ++i) {
                assert(!nodes.empty());
                layer.push_back(nodes.front()->val);
                if (nodes.front()->left) {
                    nodes.push_back(nodes.front()->left);
                    ++numNodeNext;
                }
                if (nodes.front()->right) {
                    nodes.push_back(nodes.front()->right);
                    ++numNodeNext;
                }
                nodes.pop_front();
            }
            layers.push_front(layer);
            layer.clear();
            numNode = numNodeNext;
        }
        
        return vector<vector<int>>(layers.begin(), layers.end());
    }
};*/


/* #108 *//* Recursion *//*
class Solution {
private:
    // build subtress using values from nums[begin] to nums[end], inclusive
    TreeNode* buildTreeNode(const vector<int>& nums, int begin, int end){
        if (begin > end) return nullptr;
        if (begin == end) return new TreeNode(nums[begin]);
        int mid = (begin + end) / 2;
        return new TreeNode(nums[mid], buildTreeNode(nums, begin, mid - 1), buildTreeNode(nums, mid + 1, end));
    }
    
public:
    
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return buildTreeNode(nums, 0, int(nums.size()) - 1);
    }
};*/


/* #110 *//*
class Solution {
private:
    int height(TreeNode* node){
        if (!node) return 0;
        else return max(height(node->left), height(node->right)) + 1;
    }
    
public:
    bool isBalanced(TreeNode* root) {
        if (root == nullptr) return true;
        if (abs(height(root->left) - height(root->right)) > 1) return false;
        return isBalanced(root->left) && isBalanced(root->right);
    }
};*/


/* #114 *//*
class Solution {
private:
    void preorderTraverse(TreeNode* root, deque<TreeNode*>& nodes){
        if (!root) return;
        nodes.push_back(root);
        preorderTraverse(root->left, nodes);
        preorderTraverse(root->right, nodes);
    }
    
    void buildTree(deque<TreeNode*>& nodes){
        TreeNode* prev = nodes.front();
        nodes.pop_front();
        while (!nodes.empty()) {
            prev->left = nullptr;
            prev->right = nodes.front();
            prev = nodes.front();
            nodes.pop_front();
        }
        prev->left = nullptr;
        prev->right = nullptr;
    }
    
public:
    void flatten(TreeNode* root) {
        if (!root) return;
        
        deque<TreeNode*> preTraverse;
        preorderTraverse(root, preTraverse);
        buildTree(preTraverse);
    }
};*/

/* #115 *//* Using DP*//*
class Solution {
public:
    int numDistinct(string s, string t) {
        size_t numSubString[t.size()][s.size()];
        //initialize the first row
        for (size_t i = 0; i < s.size(); ++i) {
            if (i == 0){
                if (s[0] == t[0]) numSubString[0][i] = 1;
                else numSubString[0][i] = 0;
                continue;
            }
            numSubString[0][i] = numSubString[0][i - 1];
            if (s[i] == t[0]) numSubString[0][i] += 1;
        }
        //initialize the first column
        for (size_t i = 1; i < t.size(); ++i) {
            numSubString[i][0] = 0;
        }
        // DP
        for (size_t row = 1; row < t.size(); ++row){
            for (size_t column = 1; column < s.size(); ++column) {
                numSubString[row][column] = numSubString[row][column - 1];
                if (s[column] == t[row]) numSubString[row][column] += numSubString[row - 1][column - 1];
            }
        }
        return numSubString[t.size() - 1][s.size() - 1];
    }
};*/

// This is an optimized version of DP
/*
class Solution {
public:
    int numDistinct(string s, string t) {
        deque<size_t*> twoRows;
        size_t row1[s.length()];
        twoRows.push_back(row1);
        size_t row2[s.length()];
        if (t.length() > 1){
            twoRows.push_back(row2);
        }
        
        //initialize the first row
        for (size_t i = 0; i < s.size(); ++i) {
            if (i == 0){
                if (s[0] == t[0]) twoRows.front()[i] = 1;
                else twoRows.front()[i] = 0;
                continue;
            }
            twoRows.front()[i] = twoRows.front()[i - 1];
            if (s[i] == t[0]) twoRows.front()[i] += 1;
        }
        
        // DP
        for (size_t row = 1; row < t.size(); ++row){
            if (row != 1) {
                twoRows.push_back(twoRows.front());
                twoRows.pop_front();
            }
            
            for (size_t column = 0; column < s.size(); ++column) {
                if (column == 0){
                    twoRows.back()[column] = 0;
                    continue;
                }
                twoRows.back()[column] = twoRows.back()[column - 1];
                if (s[column] == t[row]) twoRows.back()[column] += twoRows.front()[column - 1];
            }
        }
        
        return twoRows.back()[s.length() - 1];
    }
};*/


/* #116 *//* Can be done by BFS, but would require O(N) space where N is the number of nodes*//*
class Solution {
public:
    Node* connect(Node* root) {
        
    }
};*/

/* #117 *//*
class Solution {
public:
    Node* connect(Node* root) {
        Node* leftmost = root;
        while (leftmost) {
            Node* nextLeftmost = nullptr;
            Node* prev = nullptr;
            while (leftmost) {
                if (leftmost->left){
                    if (prev) prev->next = leftmost->left;
                    if (!nextLeftmost) nextLeftmost = leftmost->left;
                    if (leftmost->right) {
                        leftmost->left->next = leftmost->right;
                        prev = leftmost->right;
                    }
                    else prev = leftmost->left;
                }
                else if (leftmost->right){
                    if (prev) prev->next = leftmost->right;
                    if (!nextLeftmost) nextLeftmost = leftmost->right;
                    prev = leftmost->right;
                }
                leftmost = leftmost->next;
            }
            leftmost = nextLeftmost;
            prev = nullptr;
        }
        return root;
    }
};*/

/* #118 *//*
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> results;
        results.resize(numRows);
        for (int i = 0; i < numRows; ++i) {
            results[i].resize(i + 1);
            //tail and head
            results[i][0] = 1;
            results[i][i] = 1;
            for (int j = 1; j < i; ++j) {
                results[i][j] = results[i - 1][j - 1] + results[i - 1][j];
            }
        }
        return results;
    }
};*/
        
/* #120 *//* Using DP *//*
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        vector<int> pathSum(triangle.back().size());
        pathSum[0] = triangle[0][0];
        for (int row = 1; row < triangle.size(); ++row) {
            for (int column = row; column >= 0; --column) {
                // consider the edge first
                if (column == 0) {
                    pathSum[column] += triangle[row][column];
                    continue;
                }
                if (column == row) {
                    pathSum[column] = pathSum[column - 1] + triangle[row][column];
                    continue;
                }
                pathSum[column] = min(pathSum[column - 1], pathSum[column]) + triangle[row][column];
            }
        }
        
        int minSum = INT_MAX;
        for (auto sum : pathSum){
            if (sum < minSum) minSum = sum;
        }
        return minSum;
    }
};*/


/* #121 *//*
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() == 1) return 0;
        int buyInd = 0;
        int profit = 0;
        for (int i = 1; i < prices.size(); ++i) {
            if (prices[i] - prices[buyInd] > profit){
                profit = prices[i] - prices[buyInd];
            }
            if (prices[i] < prices[buyInd]) buyInd = i;
        }
        return profit;
    }
};*/


/* #122 *//*
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int profit = 0;
        for (int i = 1; i < int(prices.size()); ++i){
            if (prices[i] > prices[i - 1]) profit += prices[i] - prices[i - 1];
        }
        return profit;
    }
};*/

/* #123 *//* Time Exceeded *//*
class Solution {
private:
    int maxProfit(const vector<int>& prices, int start, int end) {
        if (end - start < 1) return 0;
        if (start < 0) return 0;
        int buyInd = start;
        int profit = 0;
        for (int i = start + 1; i <= end; ++i) {
            if (prices[i] - prices[buyInd] > profit){
                profit = prices[i] - prices[buyInd];
            }
            if (prices[i] < prices[buyInd]) buyInd = i;
        }
        return profit;
    }
    
    void trim(vector<int>& prices){
        if (prices.size() == 1) return;
        vector<int> trimedPrices;
        trimedPrices.reserve(prices.size());
        trimedPrices.push_back(prices.front());
        for (auto price : prices) {
            if (price != trimedPrices.back()) trimedPrices.push_back(price);
        }
        prices = trimedPrices;
    }
    
public:
    int maxProfit(vector<int>& prices) {
        int profit = 0;
        trim(prices);
        for (int i = -1; i < int(prices.size()); ++i) {
            int newProfit = maxProfit(prices, 0, i) + maxProfit(prices, i + 1, int(prices.size() - 1));
            if (newProfit > profit) profit = newProfit;
        }
        return profit;
    }
};*/

/* #123 *//* Try DP: this can be further improved by maintaining two consecutive day information*//*
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // day  transaction times left  status (0: not having; 1: having)
        int dp[prices.size()][3][2];
        for (size_t day = 0; day < prices.size(); ++day){
            for (int leftTransactionTime = 0; leftTransactionTime < 3; ++leftTransactionTime){
                // initializetion
                if (day == 0){
                    if (leftTransactionTime == 0){
                        dp[day][leftTransactionTime][0] = INT_MIN / 2;
                        dp[day][leftTransactionTime][1] = INT_MIN / 2;
                    }
                    else if (leftTransactionTime == 1){
                        // transaction happens on day 1
                        dp[day][leftTransactionTime][0] = INT_MIN / 2;
                        dp[day][leftTransactionTime][1] = -prices[day];
                    }
                    else if (leftTransactionTime == 2){
                        dp[day][leftTransactionTime][0] = 0;
                        dp[day][leftTransactionTime][1] = INT_MIN / 2;
                    }
                    continue;
                }
                
                if (leftTransactionTime == 2){
                    dp[day][leftTransactionTime][0] = 0;
                    dp[day][leftTransactionTime][1] = INT_MIN / 2;
                }
                else {
                    dp[day][leftTransactionTime][0] = max(dp[day - 1][leftTransactionTime][0], dp[day - 1][leftTransactionTime][1] + prices[day]);
                    if (dp[day][leftTransactionTime + 1][0] == INT_MIN){
                        dp[day][leftTransactionTime][1] = dp[day - 1][leftTransactionTime][1];
                    }
                    else {
                    dp[day][leftTransactionTime][1] = max(dp[day - 1][leftTransactionTime][1], dp[day - 1][leftTransactionTime + 1][0] - prices[day]);
                    }
                }
            }
        }
        int profit = max(dp[prices.size() - 1][0][0], dp[prices.size() - 1][1][0]);
        profit = max(profit, dp[prices.size() - 1][2][0]);
        return profit;
    }
};*/

/* #124 *//* Recursion Method: the difficult point lies in seperating different cases
            This method has very good running result *//*
class Solution {
private:
    int recurMaxSum(TreeNode* root, int& maxSum){
        // if leaf
        if (!root->left && !root->right){
            maxSum = max(maxSum, root->val);
            return root->val;
        }
        int leftSum, rightSum;
        if (!root->right){
            leftSum = recurMaxSum(root->left, maxSum);
            if (leftSum > 0){
                leftSum += root->val;
                maxSum = max(maxSum, leftSum);
                return leftSum;
            }
            else{
                maxSum = max(maxSum, root->val);
                return root->val;
            }
        }
        if (!root->left){
            rightSum = recurMaxSum(root->right, maxSum);
            if (rightSum > 0){
                rightSum += root->val;
                maxSum = max(maxSum, rightSum);
                return rightSum;
            }
            else {
                maxSum = max(maxSum, root->val);
                return root->val;
            }
        }
        // if root has both the left and the right
        leftSum = recurMaxSum(root->left, maxSum);
        rightSum = recurMaxSum(root->right, maxSum);
        if (leftSum > 0){
            if (rightSum > 0){
                int fullsum = rightSum + leftSum + root->val;
                maxSum = max(maxSum, fullsum);
                leftSum = max(leftSum, rightSum);
                maxSum = max(maxSum, leftSum);
                return leftSum + root->val;
            }
            else{
                if (root->val < 0) maxSum = max(maxSum, leftSum);
                else maxSum = max(maxSum, leftSum + root->val);
                return leftSum + root->val;
            }
        }
        else {
            if (rightSum > 0){
                if (root->val > 0) maxSum = max(maxSum, root->val + rightSum);
                else maxSum = max(maxSum, rightSum);
                return rightSum + root->val;
            }
            else {
                maxSum = max(max(leftSum, rightSum), max(root->val, maxSum));
                return root->val;
            }
        }
    }
    
public:
    int maxPathSum(TreeNode* root) {
        int maxSum = INT_MIN;
        recurMaxSum(root, maxSum);
        return maxSum;
    }
};*/


/* #125 *//*
class Solution {
public:
    bool isPalindrome(string s) {
        if (s.length() < 2) return true;
        size_t head = 0;
        size_t tail = s.length() - 1;
        while (head < tail) {
            //ignore space
            if (!isalnum(s[head])){
                ++head;
                continue;
            }
            if (!isalnum(s[tail])){
                --tail;
                continue;
            }
            if (s[head] != s[tail]){
                if (s[head] >= 'a' && s[tail] >= 'A' && s[head] - 'a' == s[tail] - 'A');
                else if (s[head] >= 'A' && s[tail] >= 'a' && s[head] - 'A' == s[tail] - 'a');
                else return false;
            }
            ++head;
            --tail;
        }
        return true;
    }
};*/

/* #126 Using BFS*//*
class Solution {
private:
    unordered_set<string> words;
    unordered_set<string> already;
    unordered_set<string> temp;
    // key word; value word can be the parent of word
    unordered_map<string, set<string>> findPath;
    vector<vector<string>> paths;
    vector<string> path;
    size_t steps = 1;
    string* beginW;
    
    void genTransitions(deque<string>& breadth, unordered_set<string>& temp){
        string word(breadth.front());
        for (char& c : word){
            char init = c;
            for (int i = 0; i < 26; ++i){
                c = 'a' + i;
                if (words.find(word) != words.end() && c != init && already.find(word) == already.end()){
                    if (temp.find(word) == temp.end()){
                        breadth.push_back(word);
                        temp.insert(word);
                    }
                    findPath[word].insert(breadth.front());
                }
            }
            c = init;
        }
        breadth.pop_front();
    }
    
    void updateAlready(deque<string>& breadth){
        for (const auto& s : breadth) already.insert(s);
    }
    
    void genTransitions(string s){
        string word(s);
        for (char& c : s){
            char init = c;
            for (int i = 0; i < 26; ++i){
                c = 'a' + i;
                if (words.find(s) != words.end() && c != init){
                    findPath[word].insert(s);
                }
            }
            c = init;
        }
    }
    
    // backtrack
    void backtrackGenPath(size_t ind){
        if (ind == 0){
            if(findPath[path[1]].find(*beginW) != findPath[path[1]].end()) paths.push_back(path);
            return;
        }
        auto it = findPath.find(path[ind + 1]);
        if (it == findPath.end()) return;
        for (const auto& s : it->second) {
            path[ind] = s;
            backtrackGenPath(ind - 1);
        }
    }
        
    void genPath(const string& beginWord, const string& endWord){
        path.resize(steps);
        path.back() = endWord;
        path.front() = beginWord;
        if (steps == 1){
            paths.push_back(path);
            return;
        }
        backtrackGenPath(steps - 2);
    }
    
    bool findSteps(string beginWord, string endWord, vector<string>& wordList){
        words = unordered_set<string>(wordList.begin(), wordList.end());
        if (words.find(endWord) == words.end()) return false;
        genTransitions(endWord);
        if (findPath[endWord].size() == 0) return false;
        auto winningIter = findPath.find(endWord);
        already.insert(beginWord);
        already.insert(endWord);
        string current = beginWord;
        deque<string> breadthElements{beginWord};
        
        size_t numEle = breadthElements.size();
        unordered_set<string> temp;
        while (numEle > 0) {
            if (steps > wordList.size()) return false;
            --numEle;
            if (winningIter->second.find(breadthElements.front()) != winningIter->second.end()){
                ++steps;
                return true;
            }
            genTransitions(breadthElements, temp);
            if (numEle == 0){
                ++steps;
                numEle = breadthElements.size();
                updateAlready(breadthElements);
                temp.clear();
            }
        }
        return false;
    }
    
    
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        beginW = &beginWord;
        if(findSteps(beginWord, endWord, wordList)) genPath(beginWord, endWord);
        return paths;
    }
};*/

/* #127 *//*
class Solution {
private:
    unordered_set<string> words;
    unordered_set<string> already;
    unordered_set<string> winningSet;
    int steps = 1;
    string* beginW;
    
    void genTransitions(deque<string>& breadth){
        string word(breadth.front());
        for (char& c : word){
            char init = c;
            for (int i = 0; i < 26; ++i){
                c = 'a' + i;
                if (words.find(word) != words.end() && c != init && already.find(word) == already.end()){
                    breadth.push_back(word);
                    already.insert(word);
                }
            }
            c = init;
        }
        breadth.pop_front();
    }
    
    void updateAlready(deque<string>& breadth){
        for (const auto& s : breadth) already.insert(s);
    }
    
    void genTransitions(string s){
        for (char& c : s){
            char init = c;
            for (int i = 0; i < 26; ++i){
                c = 'a' + i;
                if (c != init) winningSet.insert(s);
            }
            c = init;
        }
    }
    
    
    bool findSteps(string beginWord, string endWord, vector<string>& wordList){
        words = unordered_set<string>(wordList.begin(), wordList.end());
        if (words.find(endWord) == words.end()) return false;
        genTransitions(endWord);
        if (winningSet.empty()) return false;
        already.insert(beginWord);
        already.insert(endWord);
        string current = beginWord;
        deque<string> breadthElements{beginWord};
        
        size_t numEle = breadthElements.size();
        while (numEle > 0) {
            if (steps > wordList.size()) return false;
            --numEle;
            if (winningSet.find(breadthElements.front()) != winningSet.end()){
                ++steps;
                return true;
            }
            genTransitions(breadthElements);
            if (numEle == 0){
                ++steps;
                numEle = breadthElements.size();
                updateAlready(breadthElements);
            }
        }
        return false;
    }
    
    
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        beginW = &beginWord;
        if(findSteps(beginWord, endWord, wordList)) return steps;
        return 0;
    }
};*/

/* #128 *//*
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if (nums.size() < 2) return int(nums.size());
        sort(nums.begin(), nums.end());
        int length = 1;
        int newLength = 1;
        for (int i = 1; i < int(nums.size()); ++i) {
            if (nums[i] == nums[i - 1] + 1) ++newLength;
            else if (nums[i] == nums[i - 1]);
            else{
                length = max(length, newLength);
                newLength = 1;
            }
        }
        length = max(length, newLength);
        return length;
    }
};*/


/* #129 *//*
class Solution {
private:
    int sum = 0;
    
    void recurSum(TreeNode *root, string& s){
        s.push_back('0' + root->val);
        //if child node
        if (!root->left && !root->right){
            sum += stoi(s);
            s.pop_back();
            return;
        }
        if(root-> left) recurSum(root->left, s);
        if (root->right) recurSum(root->right, s);
        s.pop_back();
    }
    
public:
    int sumNumbers(TreeNode* root) {
        if (!root) return 0;
        string s;
        recurSum(root, s);
        return sum;
    }
};*/


/* #130 *//* BFS *//*
struct pair_hash {
    inline std::size_t operator()(const std::pair<int,int> & v) const {
        return v.first*31 + v.second;
    }
};

class Solution {
private:
    int numRow;
    int numColumn;
    unordered_set<pair<int, int>, pair_hash> visited;
    unordered_set<pair<int, int>, pair_hash> oCoors;
    queue<pair<int, int>> breadth;

    bool isBoarder(const pair<int, int>& coor, const vector<vector<char>>& board){
        bool isBoarder = false;
        if (coor.first == 0) isBoarder = true;
        else if (board[coor.first - 1][coor.second] == 'O' && visited.find(make_pair(coor.first - 1, coor.second)) == visited.end()){
            breadth.push(make_pair(coor.first - 1, coor.second));
            visited.insert(make_pair(coor.first - 1, coor.second));
        }
        if (coor.first == numRow - 1) isBoarder = true;
        else if (board[coor.first + 1][coor.second] == 'O' && visited.find(make_pair(coor.first + 1, coor.second)) == visited.end()){
            breadth.push(make_pair(coor.first + 1, coor.second));
            visited.insert(make_pair(coor.first + 1, coor.second));
        }
        if (coor.second == 0) isBoarder = true;
        else if (board[coor.first][coor.second - 1] == 'O' && visited.find(make_pair(coor.first, coor.second - 1)) == visited.end()){
            breadth.push(make_pair(coor.first, coor.second - 1));
            visited.insert(make_pair(coor.first, coor.second - 1));
        }
        if (coor.second == numColumn - 1) isBoarder = true;
        else if (board[coor.first][coor.second + 1] == 'O' && visited.find(make_pair(coor.first, coor.second + 1)) == visited.end()){
            breadth.push(make_pair(coor.first, coor.second + 1));
            visited.insert(make_pair(coor.first, coor.second + 1));
        }
        return isBoarder;
    }
    
public:
    void solve(vector<vector<char>>& board) {
        numRow = int(board.size());
        numColumn = int(board[0].size());
        visited.reserve(numRow * numColumn);
        //find all coordiantes marked 'O'
        for (int i = 0; i < numRow; ++i) {
            for (int j = 0; j < numColumn; ++j) {
                if (board[i][j] == 'O') oCoors.insert(make_pair(i, j));
            }
        }
        //iterate all the coor
        while (!oCoors.empty()){
            breadth.push(*oCoors.begin());
            visited.insert(*oCoors.begin());
            bool border = false;
            //doing BFS
            while (!breadth.empty()){
                pair<int, int> current = breadth.front();
                breadth.pop();
                border = border | isBoarder(current, board);
            }
            // update searching points
            for(const auto& coor : visited){
                // if border, mark all 'O' with 'X'
                if (!border) board[coor.first][coor.second] = 'X';
                oCoors.erase(coor);
            }
            // clear visited for the next point
            visited.clear();
        }
    }
};*/

/* #131 *//*
class Solution {
public:
    vector<vector<string>> partition(string s) {
        
    }
};*/


/* #132 *//*
class Solution {
private:
    vector<vector<int>> dp;
    
    int solve(int start, int end){
        if (dp[start][end] != INT_MAX) return dp[start][end];
        for (int mid = start; mid < end; ++mid){
            if (dp[start][mid] == 1 && dp[mid + 1][end] == 1){
                dp[start][end] = 2;
                break;
            }
            else if (dp[start][mid] == 1 || dp[mid + 1][end] == 1){
                dp[start][end] = min(dp[start][end], solve(start, mid) + solve(mid + 1, end));
            }
        }
        return dp[start][end];
    }
    
public:
    int minCut(string s) {
        if (s.length() < 2) return 0;
        dp.resize(s.length(), vector<int>(s.length(), INT_MAX));
        // set table
        for (int i = int(s.length() - 1); i >= 0; --i){
            for (int j = i; j < s.length(); ++j){
                // special case 1
                if (j == i) dp[i][j] = 1;
                // special case 2
                else if (j == i + 1){
                    if (s[j] == s[i]) dp[i][j] = 1;
                }
                // judge palidrome on the current dp
                else if (dp[i + 1][j - 1] == 1 && s[j] == s[i]) dp[i][j] = 1;
            }
        }
        // early trim
        if (dp[0][s.length() - 1] == 1) return 0;
        return solve(0, int(s.length() - 1)) - 1;
    }
};*/

/* Best solution*//*
class Solution {
public:
    int minCut(string s) {
        int n = s.size();
        vector<int> cut(n+1, 0);  // number of cuts for the first k characters
        for (int i = 0; i <= n; i++) cut[i] = i-1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; i-j >= 0 && i+j < n && s[i-j]==s[i+j] ; j++) // odd length palindrome
                cut[i+j+1] = min(cut[i+j+1],1+cut[i-j]);

            for (int j = 1; i-j+1 >= 0 && i+j < n && s[i-j+1] == s[i+j]; j++) // even length palindrome
                cut[i+j+1] = min(cut[i+j+1],1+cut[i-j+1]);
        }
        return cut[n];
    }
};*/




int main(){
    Solution S;
    //vector<string> words{"zzyy","zy","zyy"};
    //vector<vector<char>> board{{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}};
    //vector<int> nums{0,0,0,1,2,2,4,4};
    int result = S.minCut("fiefhgdcdcgfeibggchibffahiededbbegegdfibdbfdadfbdbceaadeceeefiheibahgececggaehbdcgebaigfacifhdbecbebfhiefchaaheiichgdbheacfbhfiaffaecicbegdgeiaiccghggdfggbebdaefcagihbdhhigdgbghbahhhdagbdaefeccfiaifffcfehfcdiiieibadcedibbedgfegibefagfccahfcbegdfdhhdgfhgbchiaieehdgdabhidhfeecgfiibediiafacagigbhchcdhbaigdcedggehhgdhedaebchcafcdehcffdiagcafcgiidhdhedgaaegdchibhdaegdfdaiiidcihifbfidechicighbcbgibadbabieaafgeagfhebfaheaeeibagdfhadifafghbfihehgcgggffgbfccgafigieadfehieafaehaggeeaaaehggffccddchibegfhdfafhadgeieggiigacbfgcagigbhbhefcadafhafdiegahbhccidbeeagcgebehheebfaechceefdiafgeddhdfcadfdafbhiifigcbddahbabbeedidhaieagheihhgffbfbiacgdaifbedaegbhigghfeiahcdieghhdabdggfcgbafgibiifdeefcbegcfcdihaeacihgdchihdadifeifdgecbchgdgdcifedacfddhhbcagaicbebbiadgbddcbagbafeadhddaeebdgdebafabghcabdhdgieiahggddigefddccfccibifgbfcdccghgceigdfdbghdihechfabhbacifgbiiiihcgifhdbhfcaiefhccibebcahidachfabicbdabibiachahggffiibbgchbidfbbhfcicfafgcagaaadbacddfiigdiiffhbbehaaacidggfbhgeaghigihggfcdcidbfccahhgaffiibbhidhdacacdfebedbiacaidaachegffaiiegeabfdgdcgdacfcfhdcbfiaaifgfaciacfghagceaaebhhibbieehhcbiggabefbeigcbhbcidbfhfcgdddgdffghidbbbfbdhcgabaagddcebaechbbiegeiggbabdhgghciheabdibefdfghbfbfebidhicdhbeghebeddgfdfhefebiiebdchifbcbahaddhbfafbbcebiigadhgcfbebgbebhfddgdeehhgdegaeedfadegfeihcgeefbbagbbacbgggciehdhiggcgaaicceeaefgcehfhfdciaghcbbgdihbhecfbgffefhgiefgeiggcebgaacefidghdfdhiabgibchdicdehahbibeddegfciaeaffgbefbbeihbafbagagedgbdadfdggfeaebaidchgdbcifhahgfdcehbahhdggcdggceiabhhafghegfdiegbcadgaecdcdddfhicabdfhbdiiceiegiedecdifhbhhfhgdbhibbdgafhgdcheefdhifgddchadbdggiidhbhegbdfdidhhfbehibiaacdfbiagcbheabaaebfeaeafbgigiefeaeheabifgcfibiddadicheahgbfhbhddaheghddceedigddhchecaghdegigbegcbfgbggdgbbigegffhcfcbbebdchffhddbfhhfgegggibhafiebcfgeaeehgdgbccbfghagfdbdfcbcigbigaccecfehcffahiafgabfcaefbghccieehhhiighcfeabffggfchfdgcfhadgidabdceediefdccceidcfbfiiaidechhbhdccccaigeegcaicabbifigcghcefaafaefd");
    return 0;
}
