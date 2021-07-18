#include <iostream>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>
#include <set>
// onordered_multiset here
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




int main(){
    Solution S;
    //vector<string> words{"zzyy","zy","zyy"};
    //vector<vector<char>> board{{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}};
    vector<int> nums{10, 2};
    vector<string> words{"cat","cats","and","sand","dog"};
    vector<char> s{'t'};
    return 0;
}

