#include <iostream>
#include <memory>
using namespace std;

class Trie {
private:
    static int getId(const char& c) {
        return int(c - 'a');
    }

    const static int CHILD_NUM = 26;

    class TrieNode {
    private:
        TrieNode* children[CHILD_NUM];
        int prefixCount;
        int existCount;

    public:
        friend class Trie;
        
        TrieNode(): prefixCount(0), existCount(0) {
            memset(children, 0, __SIZEOF_POINTER__ * CHILD_NUM);
        }

        int existsCount() {
            return existCount;
        }

        int prifixCount() {
            return prefixCount;
        }
        
        void addPrefix() {
            ++prefixCount;
        }
        
        void removePrefix() {
            --prefixCount;
        }
        
        void insert() {
            ++prefixCount;
            ++existCount;
        }
        
        void erase() {
            --prefixCount;
            --existCount;
        }

        TrieNode* getChildNode(const char& c) {
            return children[getId(c)];
        }
        
        TrieNode* createChildNode(const char& c) {
            int id = getId(c);
            return children[id] = new TrieNode();
        }
        
    };
    
    TrieNode* root;
    
    void recInsert(const string& word, int i, int end, TrieNode* curNode) {
        const char& c = word[i];
        TrieNode* nextNode = curNode->getChildNode(c);
        if (!nextNode) {
            nextNode = curNode->createChildNode(c);
        }
        
        if (i == end) {
            nextNode->insert();
            return;
        }
        
        nextNode->addPrefix();
        recInsert(word, i + 1, end, nextNode);
    }
    
    void recErase(const string& word, int i, int end, TrieNode* curNode) {
        const char& c = word[i];
        TrieNode* nextNode = curNode->getChildNode(c);
        if (!nextNode) {
            throw runtime_error("trying to erase word that is not inserted");
        }
        
        if (i == end) {
            nextNode->erase();
            return;
        }
        
        nextNode->removePrefix();
        recErase(word, i + 1, end, nextNode);
    }
    
    int recFind(const string& word, int i, int end, TrieNode* curNode, bool isPrefix) {
        const char& c = word[i];
        TrieNode* nextNode = curNode->getChildNode(c);
        if (!nextNode) {
            return 0; //  the word/prefix never exists
        }
        
        if (i == end) {
            return isPrefix ? nextNode->prifixCount() : nextNode->existsCount();
        }
        
        return recFind(word, i + 1, end, nextNode, isPrefix);
    }
    
    void recPop(TrieNode* curNode) {
        for (int i = 0; i < CHILD_NUM; ++i) {
            TrieNode* child = curNode->children[i];
            if (!child) {
                continue;
            }
            
            recPop(child);
            delete child;
        }
    }
    
public:
    Trie(): root(new TrieNode()) {}
    
    // ban copy constructor and = assignment
    Trie(const Trie& other) = delete;
    Trie operator=(const Trie& other) = delete;
    
    void insert(string word) {
        recInsert(word, 0, static_cast<int>(word.size()) - 1, root);
    }
    
    int countWordsEqualTo(string word) {
        return recFind(word, 0, static_cast<int>(word.size()) - 1, root, false);
    }
    
    int countWordsStartingWith(string prefix) {
        return recFind(prefix, 0, static_cast<int>(prefix.size() - 1), root, true);
    }
    
    void erase(string word) {
        recErase(word, 0, static_cast<int>(word.size()) - 1, root);
    }
    
    ~Trie() {
        recPop(root);
        delete root;
    }
};
