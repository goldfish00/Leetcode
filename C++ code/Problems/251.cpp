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

/* 251. Flatten 2D Vector */
//class Vector2D {
//private:
//    int currentVecIndex;
//    int numVec;
//    vector<vector<int>> vecs;
//    vector<int>* currentVec;
//    vector<int>::iterator nextIter;
//
//    void findNextValid() {
//        for (int i = currentVecIndex + 1; i < numVec; ++i) {
//            if (vecs[i].size() == 0) {
//                continue;
//            }
//            currentVec = &vecs[i];
//            currentVecIndex = i;
//            nextIter = currentVec->begin();
//            return;
//        }
//
//        currentVec = nullptr;
//    }
//
//public:
//    Vector2D(vector<vector<int>>& vec) {
//        currentVecIndex = -1;
//        numVec = (int)vec.size();
//        vecs = vec;
//        findNextValid();
//    }
//
//    int next() {
//        int value = *nextIter;
//        ++nextIter;
//        if (nextIter == currentVec->end()) {
//            findNextValid();
//        }
//        return value;
//    }
//
//    bool hasNext() {
//        return currentVec && nextIter != currentVec->end();
//    }
//};

/* Using iterators only */
class Vector2D {
private:
    vector<vector<int>>::iterator outerIt;
    vector<vector<int>>::iterator endIt;
    vector<int>::iterator innerIt;
    
    void findNextValid() {
        while (innerIt == outerIt->end()) {
            ++outerIt;
            if (outerIt == endIt) {
                return;
            }
            innerIt = outerIt->begin();
        }
    }
    
public:
    Vector2D(vector<vector<int>>& vec) {
        endIt = vec.end();
        outerIt = vec.begin();
        if (endIt == outerIt) {
            return;
        }
        
        innerIt = outerIt->begin();
        findNextValid();
    }
    
    int next() {
        int val = *innerIt;
        ++innerIt;
        findNextValid();
        return val;
    }
    
    bool hasNext() {
        if (outerIt == endIt) {
            return false;
        }
        return true;
    }
};

/**
 * Your Vector2D object will be instantiated and called as such:
 * Vector2D* obj = new Vector2D(vec);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
int main() {
    vector<vector<int>> vec{{1, 2}, {3}, {4}};
    Vector2D* obj = new Vector2D(vec);
    cout << obj->next() << endl;
    cout << obj->next() << endl;
    cout << obj->next() << endl;
    cout << (obj->hasNext() ? "has next" : "consumed") << endl;
    cout << (obj->hasNext() ? "has next" : "consumed") << endl;
    cout << obj->next() << endl;
    cout << (obj->hasNext() ? "has next" : "consumed") << endl;

    
    delete obj;
    return 0;
}
