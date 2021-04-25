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





int main(){
    Solution S;
    //vector<string> words{"zzyy","zy","zyy"};
    //vector<vector<char>> board{{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}};
    vector<int> nums{94,89,54,26,54,54,99,64};
    vector<string> words{"cat","cats","and","sand","dog"};
    S.wordBreak("catsanddog", words);
    return 0;
}

