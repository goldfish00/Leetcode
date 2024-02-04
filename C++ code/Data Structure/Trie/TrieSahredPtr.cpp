//
//  main.cpp
//  leetcode
//
//  Created by Junyi Huang on 1/23/24.
//

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
        shared_ptr<TrieNode> children[CHILD_NUM];
        int prefixCount;
        int existCount;

    public:
        TrieNode(): prefixCount(0), existCount(0) {}

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

        shared_ptr<TrieNode> getChildNode(const char& c) {
            return children[getId(c)];
        }
        
        shared_ptr<TrieNode> createChildNode(const char& c) {
            int id = getId(c);
            return children[id] = make_shared<TrieNode>();
        }
        
    };

    shared_ptr<TrieNode> root;
    
    void recInsert(const string& word, int i, int end, shared_ptr<TrieNode> curNode) {
        const char& c = word[i];
        auto nextNode = curNode->getChildNode(c);
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
    
    void recErase(const string& word, int i, int end, shared_ptr<TrieNode> curNode) {
        const char& c = word[i];
        auto nextNode = curNode->getChildNode(c);
        if (!nextNode) {
            throw runtime_error("trying to erase something that do not exists!");
        }
        
        if (i == end) {
            nextNode->erase();
            return;
        }
        
        nextNode->removePrefix();
        recErase(word, i + 1, end, nextNode);
    }
    
    int recFind(const string& s, int i, int end, bool isPrefix, shared_ptr<TrieNode> curNode) {
        const char& c = s[i];
        auto nextNode = curNode->getChildNode(c);
        if (!nextNode) {
            return 0;
        }
        
        if (i == end) {
            return isPrefix ? nextNode->prifixCount() : nextNode->existsCount();
        }
        
        return recFind(s, i + 1, end, isPrefix, nextNode);
    }

public:
    Trie(): root(make_shared<TrieNode>()) {}

    void insert(string word) {
        recInsert(word, 0, int(word.size()) - 1, root);
    }

    int countWordsEqualTo(string word) {
        return recFind(word, 0, (int)word.size() - 1, false, root);
    }

    int countWordsStartingWith(string prefix) {
        return recFind(prefix, 0, (int)prefix.size() - 1, true, root);
    }

    void erase(string word) {
        recErase(word, 0, int(word.size()) - 1, root);
    }
};

int main(int argc, const char * argv[]) {
    Trie* obj = new Trie();
    obj->insert("apple");
    obj->insert("apple");
    obj->insert("apple");
    cout << obj->countWordsStartingWith("app") << endl;
    obj->erase("apple");
    cout << obj->countWordsStartingWith("appl") << endl;
    
    obj->insert("app");
    cout << obj->countWordsEqualTo("apple") << endl;
    cout << obj->countWordsEqualTo("app") << endl;
    
    delete obj;
    
    return 0;
}

int main(int argc, const char * argv[]) {
    Trie* obj = new Trie();
    obj->insert("apple");
    obj->insert("apple");
    obj->insert("apple");
    cout << obj->countWordsStartingWith("app") << endl;
    obj->erase("apple");
    cout << obj->countWordsStartingWith("appl") << endl;
    
    obj->insert("app");
    cout << obj->countWordsEqualTo("apple") << endl;
    cout << obj->countWordsEqualTo("app") << endl;
    
    delete obj;
    
    return 0;
}
