#include <iostream>
#include <memory> // smart pointers
//#include <sstream>
//#include <string>
// unordered_multiset here
//#include <unordered_set>
//#include <mutex>
//#include <condition_variable>
//#include <thread>
#include <vector>
//#include <assert.h>
//#include <set>
//#include <deque>
//#include <queue>
//#include <unordered_map>
//#include <queue>
//#include <map>
//#include <numeric>
//#include <list>
//#include <forward_list>
using namespace std;

class Trie {
private:
    static int getId(const char& c) {
        return int(c - 'a');
    }

    const static int CHILD_NUM = 26;

    class TrieNode {
    private:
        shared_ptr<TrieNode> children[CHILD_NUM];
        int count;
        bool exist;

    public:
        TrieNode(): count(0), exist(false) {}

        bool exists() {
            return exist;
        }

        int getNum() {
            return count;
        }

        shared_ptr<TrieNode> getChildNode(const char& c) {
            return children[getId(c)];
        }
        
        shared_ptr<TrieNode> createChildNode(const char& c) {
            int id = getId(c);
            return children[id] = make_shared<TrieNode>();
        }
    };

    unique_ptr<TrieNode> root;
    
    void recInsert(const string& word, int id) {
        
    }

public:
    Trie() {
        root = make_unique<TrieNode>();
    }

    void insert(string word) {
        
    }

    int countWordsEqualTo(string word) {
        return 1;
    }

    int countWordsStartingWith(string prefix) {
        return 1;
    }

    void erase(string word) {

    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * int param_2 = obj->countWordsEqualTo(word);
 * int param_3 = obj->countWordsStartingWith(prefix);
 * obj->erase(word);
 */


int main() {
    
    return 0;
}
