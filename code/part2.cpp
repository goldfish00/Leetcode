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

/*class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};*/

/* #133 *//*
class Solution {
private:
    unordered_map<Node*, Node*> dict;
    
public:
    Node* cloneGraph(Node* node) {
        if (!node) return nullptr;
        if (dict.find(node) != dict.end()) return dict[node];
        if (node->neighbors.empty()) {
            Node* generate = new Node(node->val);
            dict[node] = generate;
            return generate;
        }
        Node* generate = new Node(node->val);
        dict[node] = generate;
        for (Node* neighbor : node->neighbors) {
            generate->neighbors.push_back(cloneGraph(neighbor));
        }
        return generate;
    }
};*/


/* #134 *//*
class Solution {
private:
    bool isValid(const vector<int>& netCost, int startingInd){
        int gasTank = 0;
        // travel
        for (int gasStation = startingInd; gasStation < netCost.size(); ++gasStation) {
            gasTank += netCost[gasStation];
            if (gasTank < 0) return false;
        }
        // rewind
        for (int gasStation = 0; gasStation < startingInd; ++gasStation){
            gasTank += netCost[gasStation];
            if (gasTank < 0) return false;
        }
        return true;
    }
    
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int sum = 0;
        vector<int> netCost(cost.size());
        for (size_t i = 0; i < cost.size(); ++i){
            netCost[i] = gas[i] - cost[i];
        }
        if (sum < 0) return -1;
        // find the set of indices where the netCost is the smallest
        set<int> indices;
        for (int i = 0; i < gas.size(); ++i){
            if (netCost[i] >= 0){
                indices.insert(i);
            }
        }
        for (auto index : indices) {
            if (isValid(netCost, index)) return index;
        }
        return -1;
    }
};*/


/* #135 *//*
class Solution {
public:
    int candy(vector<int>& ratings) {
        // the previous candies given to the first child in the decreasing sequence
        int prevCandies = 1;
        // the candies given to the previous neighbor
        int neighborCandies = 1;
        int sumCandies = 1;
        int decreasingSequence = 1;
        for (int ind = 1; ind < ratings.size(); ++ind) {
            if (ratings[ind] == ratings[ind - 1]){
                neighborCandies = 1;
                prevCandies = 1;
                ++sumCandies;
                decreasingSequence = 1;
            }
            else if (ratings[ind] > ratings[ind - 1]){
                ++neighborCandies;
                prevCandies = neighborCandies;
                sumCandies += prevCandies;
                decreasingSequence = 1;
            }
            else {
                ++decreasingSequence;
                neighborCandies = 1;
                if (prevCandies >= decreasingSequence){
                    sumCandies += decreasingSequence - 1;
                }
                else {
                    sumCandies += decreasingSequence;
                }
            }
        }
        
        return sumCandies;
    }
};*/

/* #136 *//*
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int result = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            result = result ^ nums[i];
        }
        return result;
    }
};*/


/* #137 *//*
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        
    }
};*/

/* #138 *//*
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class Solution {
private:
    // key: node in the originial list; value: node in the new list
    unordered_map<Node*, Node*> dict;
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) return nullptr;
        if (dict.find(head) != dict.end()) return dict[head];
        Node* newHead = new Node(head->val);
        dict[head] = newHead;
        newHead->random = copyRandomList(head->random);
        newHead->next = copyRandomList(head->next);
        return newHead;
    }
};*/

/* #139 *//* Using DP *//*
class Solution {
private:
    unordered_set<int> wordLen;
    set<int> validIndices;
    
    void setWordLen(const vector<string>& wordDict){
        for (const auto& word : wordDict) {
            wordLen.insert(int(word.length()));
        }
    }
    
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        //initiliaze
        setWordLen(wordDict);
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        // check
        validIndices.insert(-1);
        for (auto ind : validIndices) {
            for (int strLen : wordLen) {
                if (ind + strLen > int(s.length()) - 1) continue;
                if (validIndices.find(ind + strLen) != validIndices.end()) continue;
                if (dict.find(s.substr(ind + 1, strLen)) != dict.end()) {
                    if (ind + strLen == int(s.length()) - 1) return true;
                    validIndices.insert(ind + strLen);
                }
            }
        }
        return false;
    }
};*/


/* #140 *//* Using DP with Backtrack*//*
class Solution {
private:
    unordered_set<int> wordLen;
    // the key is the valid index and the value is the set of valid indices that can lead to the index
    map<int, set<int>> validIndices;
    vector<string> results;
    
    void setWordLen(const vector<string>& wordDict){
        for (const auto& word : wordDict) {
            wordLen.insert(int(word.length()));
        }
    }
    
    bool findPath(const string& s, const unordered_set<string>& dict){
        bool valid = false;
        validIndices[-1];
        for (auto ind_pair : validIndices) {
            for (int strLen : wordLen) {
                if (ind_pair.first + strLen > int(s.length()) - 1) continue;
                if (dict.find(s.substr(ind_pair.first + 1, strLen)) != dict.end()) {
                    if (ind_pair.first + strLen == int(s.length()) - 1) {
                        valid = true;
                    }
                    validIndices[ind_pair.first + strLen].insert(ind_pair.first);
                }
            }
        }
        return valid;
    }
    
    void genResult(const string &s, int ind){
        for (int prevInd : validIndices[ind]) {
            if (validIndices.find(prevInd) == validIndices.end()) return;
            if (prevInd == -1) {
                results.push_back(s);
                continue;
            }
            string s_copy = s;
            s_copy.insert(prevInd + 1, " ");
            genResult(s_copy, prevInd);
        }
    }
    
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        //initiliaze
        setWordLen(wordDict);
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        if (findPath(s, dict)) genResult(s, int(s.length() - 1));
        return results;
    }
};*/


/* #141 *//* Uses two pointers, fast and slow where fast takes two steps at a time and slow takes one step
           at a time. If there is a cycle, the two pointers will meet eventually. Whereas if there is not a
           cycle, fast will reach nullptr *//*
struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };

class Solution {
public:
    bool hasCycle(ListNode *head) {
        if (!head) return false;
        ListNode* slow = head;
        ListNode* fast = head;
        fast = fast->next;
        while (fast) {
            if (fast == slow) return true;
            fast = fast->next;
            if (!fast) return false;
            fast = fast->next;
            slow = slow->next;
        }
        return false;
    }
};*/


/* # 142 *//* This is a math problem. After the two pointers meet for the first time, set the slow to the head
            and the second time they meet, they will be at the beginning of the cycle*//*
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if (!head) return nullptr;
        ListNode* slow = head;
        ListNode* fast = head;
        fast = fast->next;
        while (fast) {
            if (fast == slow) break;
            fast = fast->next;
            if (!fast) return nullptr;
            fast = fast->next;
            slow = slow->next;
        }
        if (!fast) return fast;
        // if cycle
        slow = head;
        // take one step more from the tail to the start of the cycle
        fast = fast->next;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
        return slow;
    }
};*/

/* #143 *//*
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


class Solution {
public:
    void reorderList(ListNode* head) {
        vector<ListNode*> nodes;
        ListNode *iter = head;
        while (iter) {
            nodes.push_back(iter);
            iter = iter->next;
        }
        // begin weaving
        for (size_t i = 0; i < nodes.size() / 2; ++i) {
            nodes[i]->next = nodes[nodes.size() - 1 - i];
            nodes[nodes.size() - 1 - i]->next = nodes[i + 1];
        }
        nodes[nodes.size() / 2]->next = nullptr;
    }
};*/


/* #144 *//* Note that the list's iterator is a bidirectional iterator*//*
class LRUCache {
private:
    int num;
    // key: key, pair: ind, val
    unordered_map<int, pair<list<int>::iterator, int>> pairs;
    list<int> keys;
    
public:
    LRUCache(int capacity): num(capacity) {}
    
    int get(int key) {
        auto it = pairs.find(key);
        if (it == pairs.end()) return -1;
        keys.erase(it->second.first);
        keys.push_back(key);
        it->second.first = --keys.end();
        return it->second.second;
    }
    
    void put(int key, int value) {
        auto it = pairs.find(key);
        // if new key
        if (it == pairs.end()){
            // if no space left
            if (keys.size() == num){
                pairs.erase(keys.front());
                keys.pop_front();
            }
            keys.push_back(key);
            pairs[key] = make_pair(--keys.end(), value);
        }
        // if old key
        else {
            // update
            it->second.second = value;
            // erase
            keys.erase(it->second.first);
            keys.push_back(key);
            it->second.first = --keys.end();
        }
    }
};*/


/* #147 *//*
struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        if (!head) return head;
        if (!head->next) return head;
        ListNode* sorted = head;
        ListNode* unsorted = head->next;
        sorted->next = nullptr;
        while (unsorted) {
            // find and insert
            ListNode* find = sorted;
            ListNode* insertedNode = unsorted;
            unsorted = unsorted->next;
            if (insertedNode->val <= sorted->val){
                insertedNode->next = sorted;
                sorted = insertedNode;
            }
            else {
                while (find->next) {
                    if (insertedNode->val <= find->next->val) break;
                    find = find->next;
                }
                insertedNode->next = find->next;
                find->next = insertedNode;
            }
        }
        
        return sorted;
    }
};*/


/* #148 *//* this is the answer from the leetcode solution*//*
struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
};


class Solution {
public:
    ListNode* tail = new ListNode();
    ListNode* nextSubList = new ListNode();

    ListNode* sortList(ListNode* head) {
        if (!head || !head -> next)
            return head;
        int n = getCount(head);
        ListNode* start = head;
        ListNode dummyHead(0);
        for (int size = 1; size < n; size = size * 2) {
            tail = &dummyHead;
            while (start) {
                if (!start->next) {
                    tail->next = start;
                    break;
                }
                ListNode* mid = split(start, size);
                merge(start, mid);
                start = nextSubList;
            }
            start = dummyHead.next;
        }
        return dummyHead.next;
    }

    ListNode* split(ListNode* start, int size) {
        ListNode* midPrev = start;
        ListNode* end = start->next;
        //use fast and slow approach to find middle and end of second linked list
        for (int index = 1; index < size && (midPrev->next || end->next); index++) {
            if (end->next) {
                end = (end->next->next) ? end->next->next : end->next;
            }
            if (midPrev->next) {
                midPrev = midPrev->next;
            }
        }
        ListNode* mid = midPrev->next;
        nextSubList = end->next;
        midPrev->next = nullptr;
        end->next = nullptr;
        // return the start of second linked list
        return mid;
    }

    void merge(ListNode* list1, ListNode* list2) {
        ListNode dummyHead(0);
        ListNode* newTail = &dummyHead;
        while (list1 && list2) {
            if (list1->val < list2->val) {
                newTail->next = list1;
                list1 = list1->next;
                newTail = newTail->next;
            } else {
                newTail->next = list2;
                list2 = list2->next;
                newTail = newTail->next;
            }
        }
        newTail->next = (list1) ? list1 : list2;
        // traverse till the end of merged list to get the newTail
        while (newTail->next) {
            newTail = newTail->next;
        }
        // link the old tail with the head of merged list
        tail->next = dummyHead.next;
        // update the old tail with the new tail of merged list
        tail = newTail;
    }

    int getCount(ListNode* head) {
        int cnt = 0;
        ListNode* ptr = head;
        while (ptr) {
            ptr = ptr->next;
            cnt++;
        }
        return cnt;
    }
};*/


/* #149 *//*
class Solution {
private:
    // key: slope, value: number of points
    unordered_map<double, int> possibilities;
    int max_points = 2;
    
    double calSlope(const vector<int>& coor1, const vector<int>& coor2){
        // edgecase: infinity slope
        if (coor1.front() == coor2.front()) return INT_MAX;
        return double(coor1.back() - coor2.back()) / double (coor1.front() - coor2.front());
    }
    
    void calculateMax(){
        for (const auto& pair : possibilities){
            if (pair.second + 1 > max_points) max_points = pair.second + 1;
        }
        possibilities.clear();
    }
    
public:
    int maxPoints(vector<vector<int>>& points) {
        if (points.size() < 3) return int(points.size());
        for (int i = 0; i < points.size() - 1; ++i) {
            for (int j = i + 1; j < points.size(); ++j) {
                ++possibilities[calSlope(points[i], points[j])];
            }
            calculateMax();
            //if (max_points == points.size()) return max_points;
        }
        return max_points;
    }
};*/


/* #150 *//* Using stack *//*
class Solution {
private:
    stack<int> Stack;
    
    void operate(const string &c){
        if (c == "+"){
            int i = Stack.top();
            Stack.pop();
            Stack.top() = Stack.top() + i;
            return;
        }
        if (c == "-"){
            int i = Stack.top();
            Stack.pop();
            Stack.top() = Stack.top() - i;
            return;
        }
        if (c == "*"){
            int i = Stack.top();
            Stack.pop();
            Stack.top() = Stack.top() * i;
            return;
        }
        if (c == "/"){
            int i = Stack.top();
            Stack.pop();
            Stack.top() = Stack.top() / i;
            return;
        }
        Stack.push(stoi(c));
    }
    
public:
    int evalRPN(vector<string>& tokens) {
        if (tokens.size() == 1) return stoi(tokens[0]);
        for (auto iter = tokens.begin(); iter != tokens.end(); ++iter){
            operate(*iter);
        }
        return Stack.top();
    }
};*/


/* #151 *//* Using two pointers*//*
class Solution {
private:
    // return true if this is not the first word
    bool locateWord(string::iterator& end, string::iterator& start, const string::iterator& begin){
        while (*end == ' ') {
            if (end == begin) {
                start = end;
                return false;
            }
            --end;
        }
        start = end;
        if (start == begin) return false;
        while (*(start - 1) != ' ') {
            --start;
            if (start == begin) return false;
        }
        return true;
    }
    
public:
    string reverseWords(string s) {
        string reversedString(s.length(), ' ');
        auto iterOriginalEnd = s.end() - 1;
        auto iterOriginalStart = s.end() - 1;
        auto iterWriter = reversedString.begin();
        
        while (locateWord(iterOriginalEnd, iterOriginalStart, s.begin())) {
            for (auto it = iterOriginalStart; it != iterOriginalEnd + 1; ++it) {
                *iterWriter = *it;
                ++iterWriter;
            }
            iterOriginalEnd = iterOriginalStart - 1;
            *iterWriter = ' ';
            ++iterWriter;
        }
        for (auto it = iterOriginalStart; it != iterOriginalEnd + 1; ++it) {
            *iterWriter = *it;
            ++iterWriter;
        }
        //delete meaningless chars
        while (reversedString.back() == ' ') {
            reversedString.pop_back();
        }
        return reversedString;
    }
};*/

/* #152 *//* Using DP *//*
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        vector<int> maxResPos(nums.begin(), nums.end());
        vector<int> maxResNeg(nums.begin(), nums.end());
        for (int i = 1; i < nums.size(); ++i) {
            if (maxResPos[i] < 0) {
                maxResPos[i] = max(maxResPos[i], maxResPos[i] * maxResNeg[i - 1]);
                maxResNeg[i] = min(maxResNeg[i], maxResPos[i - 1] * maxResNeg[i]);
            }
            else {
                maxResNeg[i] = min(maxResNeg[i], maxResNeg[i - 1] * maxResNeg[i]);
                maxResPos[i] = max(maxResPos[i], maxResPos[i - 1] * maxResPos[i]);
            }
        }
        
        int max = maxResPos[0];
        for (int i = 1; i < maxResPos.size(); ++i) {
            if (maxResPos[i] > max) max = maxResPos[i];
        }
        return max;
    }
};*/

/* #153 *//* Binary search: find the first element smaller than both its neighbors
           To locate the interval where the target is: start of the interval id greater than the end of the iinterval
           [left, middle], [middle + 1, right]
           *//*
class Solution {
public:
    int findMin(vector<int>& nums) {
        if (nums.size() == 1) return nums.back();
        int left = 0;
        int right = int(nums.size() - 1);
        while (right - left > 1) {
            if (nums[left] < nums[right]) return nums[left];
            int middle = left + (right - left) / 2;
            if (nums[left] > nums[middle]){
                right = middle;
            }
            else if (nums[middle] > nums[right]){
                left = middle;
            }
        }
        return min(nums[left], nums[right]);
    }
};*/


/* #154 *//*
class Solution {
    int recur(vector<int>& nums, int left, int right){
        while (right - left > 1) {
            if (nums[left] < nums[right]) return nums[left];
            int middle = left + (right - left) / 2;
            if (nums[left] > nums[middle]){
                right = middle;
            }
            else if (nums[middle] > nums[right]){
                left = middle;
            }
           // the solution optimizes this step by decreasing right by 1 as an update
            else if (nums[middle] == nums[right] && nums[right] == nums[left]){
                return min(recur(nums, left, middle), recur(nums, middle, right));
            }
        }
        return min(nums[left], nums[right]);
    }
    
public:
    int findMin(vector<int>& nums) {
        if (nums.size() == 1) return nums.back();
        return recur(nums, 0, int(nums.size() - 1));
    }
};*/


/* #155 *//* This solutioin is inefficient, can use a pair to memorize the minimum number before each element, with the
           element itself inclusive *//*
class MinStack {
public:
    deque<int> vals;
    multiset<int> sortedVals;
    
    MinStack(){}
    
    void push(int val) {
        vals.push_back(val);
        sortedVals.insert(val);
    }
    
    void pop() {
        sortedVals.erase(sortedVals.find(vals.back()));
        vals.pop_back();
    }
    
    int top() {
        return vals.back();
    }
    
    int getMin() {
        return *sortedVals.begin();
    }
};*/

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */

/* #156 *//*
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    TreeNode* upsideDownBinaryTree(TreeNode* root) {
        if (!root) return root;
        if (!root->left && !root->right) return root;
        if (!root->right && !root->left->left){
            TreeNode* newRoot = root->left;
            newRoot->right = root;
            root->left = nullptr;
            return newRoot;
        }
        if (!root->left->left && !root->right->right){
            TreeNode* newRoot = root->left;
            newRoot->left = root->right;
            newRoot->right = root;
            root->left = nullptr;
            root->right = nullptr;
            return newRoot;
        }
        
        TreeNode* newRoot = upsideDownBinaryTree(root->left);
        root->left->left = root->right;
        root->left->right = root;
        root->left = nullptr;
        root->right = nullptr;
        return newRoot;
    }
};*/

/* #157 *//*
extern int read4(char *buf4);
class Solution {
public:
    int read(char *buf, int n) {
        int timesRead = n / 4;
        int lastRead = n % 4;
        int bytesRead = 0;
        for (int i = 0; i < timesRead; ++i) {
            int numRead = read4(buf + bytesRead);
            if (numRead != 4){
                bytesRead += numRead;
                return bytesRead;
            }
            bytesRead += 4;
        }
        int numRead = read4(buf + bytesRead);
        bytesRead += numRead;
        return min(bytesRead, n);
    }
};*/


/* #158 *//*
extern int read4(char *buf4);
class Solution {
public:
    char* buffBegin = buff;
    int numLeftOver = 0;
    char buff[4];
    
    int read(char *buf, int n) {
        if (n <= numLeftOver){
            for (int i = 0; i < n; ++i) {
                *buf = *buffBegin;
                ++buf;
                ++buffBegin;
                --numLeftOver;
            }
            if (numLeftOver == 0) buffBegin = buff;
            return n;
        }
        // if greater, read the numLeftOver first
        int bytesRead = 0;
        for (int i = 0; i < numLeftOver; ++i) {
            *(buf + i) = *buffBegin;
            ++buffBegin;
        }
        buffBegin = buff;
        bytesRead += numLeftOver;
        n -= numLeftOver;
        numLeftOver = 0;

        int timesRead = n / 4;
        for (int i = 0; i < timesRead; ++i) {
            int numRead = read4(buf + bytesRead);
            if (numRead != 4){
                bytesRead += numRead;
                return bytesRead;
            }
            bytesRead += 4;
        }
        int numRead = read4(buff);
        int numLastRead = min(numRead, n % 4);
        numLeftOver = numRead - numLastRead;
        
        for (int i = 0; i < numLastRead; ++i) {
            *(buf + bytesRead) = *buffBegin;
            ++buffBegin;
            ++bytesRead;
        }
        
        return bytesRead;
    }
};*/


/* #159 *//* Sliding window *//*
class Solution {
private:
    int maxSubLen = 1;
    unordered_map<char, int> distinctChars;
    
    bool exist(char c){
        return distinctChars.find(c) != distinctChars.end();
    }
    
    void erase(char c){
        auto it = distinctChars.find(c);
        if (it->second == 1) distinctChars.erase(it);
        else it->second -= 1;
    }
    
    size_t size(){
        return distinctChars.size();
    }
    
    void insert(char c){
        distinctChars[c] += 1;
    }
    
    
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        if (s.length() < 3) return int(s.length());
        // find the first window with two distinct chars
        size_t start = 0;
        size_t end = 0;
        insert(s[end]);
        // start sliding
        while (end < s.length()) {
            if (size() < 2){
                maxSubLen = max(maxSubLen, int(end - start + 1));
                ++end;
                insert(s[end]);
            }
            else if(size() == 2) {
                maxSubLen = max(maxSubLen, int(end - start + 1));
                ++end;
                insert(s[end]);
            }
            // if greater than 2
            else {
                erase(s[start]);
                ++start;
            }
        }
        return maxSubLen;
    }
};*/


/* #160 *//*
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
private:
    int getSize(ListNode* head){
        int size = 0;
        while (head) {
            head = head->next;
            ++size;
        }
        return size;
    }
    
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int sizeA = getSize(headA);
        int sizeB = getSize(headB);
        // set headA to be the one of greater size
        if (sizeA < sizeB) {
            swap(headA, headB);
            swap(sizeA, sizeB);
        }
        for (int i = 0; i < sizeA - sizeB; ++i) {
            headA = headA->next;
        }
        while (headA) {
            if (headB == headA) return headB;
            headA = headA->next;
            headB = headB->next;
        }
        return nullptr;
    }
};*/


/* #161 *//*
class Solution {
public:
    bool isOneEditDistance(string s, string t) {
        if (s.length() > t.length() + 1) return false;
        if (t.length() > s.length() + 1) return false;
        
        // case 1: the strings are of the same length and only replacing operation is considered
        if (s.length() == t.length()){
            bool oneDifference = false;
            for (size_t i = 0; i < s.length(); ++i){
                if (s[i] != t[i]){
                    if (oneDifference) return false;
                    else oneDifference = true;
                }
            }
            return oneDifference;
        }
        // case 2: two strings differ by 1 in size and consider only inserting
        // set s to be the longer string
        if (s.length() < t.length()) swap(s, t);
        bool oneDifference = false;
        for (size_t i = 0; i < s.length(); ++i) {
            if (oneDifference) {
                if (s[i] != t[i - 1]) return false;
            }
            else {
                if (s[i] != t[i]) oneDifference = true;
            }
        }
        return true;
    }
};*/


/* #162 *//*
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        if (nums.size() == 1) return 0;
        if (nums[0] > nums[1]) return 0;
        bool greaterThanRight = false;
        for (int i = 1; i + 1 < nums.size(); ++i) {
            if (greaterThanRight) {
                greaterThanRight = (nums[i] <= nums[i + 1]);
                continue;
            }
            else{
                if (nums[i] > nums[i + 1]) return i;
                else greaterThanRight = false;
            }
        }
        return int(nums.size() - 1);
    }
};*/


/* #163 *//*
class Solution {
private:
    vector<string> results;
    string arrow;
    
    void genResult(int low, int high){
        if (low > high) return;
        if (low == high) results.push_back(to_string(low));
        else results.push_back(to_string(low) + arrow + to_string(high));
    }
    
public:
    vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
        arrow = "->";
        // check the beginning
        if (nums.size() == 0){
            genResult(lower, upper);
            return results;
        }
        for (int i = 0; i < nums.size(); ++i) {
            if (i == 0){
                genResult(lower, nums[i] - 1);
            }
            else {
                if (nums[i - 1] + 1 != nums[i]) genResult(nums[i - 1] + 1, nums[i] - 1);
            }
            // add the last one
            if (i == nums.size() - 1) genResult(nums.back() + 1, upper);
        }
        return results;
    }
};*/


/* #164 *//*
class Solution {
public:
    int maximumGap(vector<int>& nums) {
        if (nums.size() == 1) return 0;
        sort(nums.begin(), nums.end());
        int maxGap = INT_MIN;
        for (int i = 1; i < nums.size(); ++i) {
            maxGap = max(maxGap, nums[i] - nums[i - 1]);
        }
        return maxGap;
    }
};*/


/* #165 *//* There are some bad coding styles with the two private member functions (redundancy) *//*
class Solution {
private:
    char dot = '.';
    
    int cmpSubstring(string& version1, string& version2, size_t& ind1, size_t& ind2){
        size_t ind1End = version1.find(dot, ind1);
        size_t ind2End = version2.find(dot, ind2);
        if (ind1End == string::npos) ind1End = version1.size();
        if (ind2End == string::npos) ind2End = version2.size();
        int ver1 = stoi(version1.substr(ind1, ind1End - ind1));
        int ver2 = stoi(version2.substr(ind2, ind2End - ind2));
        ind1 = min(ind1End + 1, version1.size());
        ind2 = min(ind2End + 1, version2.size());
        if (ver1 > ver2) return 1;
        else if (ver1 == ver2) return 0;
        else return -1;
    }
    
    bool isZero(string& version, size_t &ind){
        size_t indEnd = version.find(dot, ind);
        if (indEnd == string::npos) indEnd = version.size();
        int val = stoi(version.substr(ind, indEnd - ind));
        ind = min(indEnd + 1, version.size());
        return val == 0;
    }
    
public:
    int compareVersion(string version1, string version2) {
        size_t ind1 = 0;
        size_t ind2 = 0;
        while (ind1 < version1.size() && ind2 < version2.size()) {
            int cmpRes = cmpSubstring(version1, version2, ind1, ind2);
            if (cmpRes != 0) return cmpRes;
        }
        
        if (ind1 == version1.size() && ind2 == version2.size()) return 0;
        if (ind1 < version1.size()){
            while (ind1 < version1.size()) {
                if(!isZero(version1, ind1)) return 1;
            }
            return 0;
        }
        else{
            while (ind2 < version2.size()) {
                if (!isZero(version2, ind2)) return -1;
            }
            return 0;
        }
    }
};*/

/* #166 */
class Solution {
private:
    int maxBound9 = INT_MAX / 9;
    int maxBound10 = INT_MAX / 10;
    int times = 0;
    int num9 = 0;
    int num10 = 0;
    
    bool base10(int denominator){
        while (denominator % 10 == 0) {
            denominator /= 10;
            ++num10;
        }
        while (denominator % 2 == 0) {
            denominator /= 2;
        }
        while (denominator % 5 == 0) {
            denominator /= 5;
        }
        return denominator == 1 || denominator == -1;
    }
    
    void base9(int denominator){
        int denominator9 = 9;
        ++num9;
        while (denominator9 % denominator != 0) {
            denominator9 = denominator9 * 10 + 9;
            ++num9;
        }
        times = denominator9 / denominator;
    }
    
public:
    string fractionToDecimal(int numerator, int denominator) {
        int integerPart = numerator / denominator;
        if (numerator % denominator == 0) return to_string(integerPart);
        bool negative = false;
        if ((numerator < 0 && denominator > 0) || (numerator > 0 && denominator < 0)) {
            negative = true;
            integerPart += 1;
        }
        if (base10(denominator)) return to_string(double(numerator / denominator));
        // deal with the cycle case
        numerator -= denominator * integerPart;
        
        string result(to_string(integerPart));
        result.push_back('.');
        
    }
};


int main(){
    Solution S;
    //vector<string> words{"zzyy","zy","zyy"};
    //vector<vector<char>> board{{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}};
    vector<int> nums{94,89,54,26,54,54,99,64};
    vector<string> words{"cat","cats","and","sand","dog"};
    return 0;
}

