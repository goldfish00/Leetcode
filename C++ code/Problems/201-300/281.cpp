#include <iostream>
// unordered_multiset here
#include <unordered_set>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>
#include <assert.h>
#include <set>
#include <deque>
#include <unordered_map>
#include <queue>
using namespace std;

/* 281. Zigzag Iterator */
class ZigzagIterator {
private:
    vector<int>::iterator it1;
    vector<int>::iterator it2;
    vector<int>::iterator it1End;
    vector<int>::iterator it2End;
    bool isNext1 = true;
    
public:
    ZigzagIterator(vector<int>& v1, vector<int>& v2) {
        it1 = v1.begin();
        it2 = v2.begin();
        it1End = v1.end();
        it2End = v2.end();
    }

    int next() {
        int val = 0;
        if (isNext1) {
            isNext1 = !isNext1;
            if (it1 != it1End) {
                val = *it1;
                ++it1;
                return val;
            }
        }
        
        if (!isNext1){
            isNext1 = !isNext1;
            if (it2 == it2End) {
                val = *it1;
                ++it1;
                return val;
            }
            val = *it2;
            ++it2;
        }
        
        return val;
    }

    bool hasNext() {
        return it1 != it1End || it2 != it2End;
    }
};

int main() {
    vector<int> v1{2, 3, 4, 5};
    vector<int> v2{1, 6};
    ZigzagIterator it(v1, v2);
    while (it.hasNext()) {
        cout << it.next() << endl;
    }
    
    return 0;
}

