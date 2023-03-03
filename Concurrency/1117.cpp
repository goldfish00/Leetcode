#include <iostream>
// unordered_multiset here
#include <unordered_set>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <deque>
using namespace std;

/* 1117. Building H2O */
class H2O {
private:
    mutex mtx;
    condition_variable releaseH;
    condition_variable releaseO;
    int remainingO;
    int remainingH;
    
    void checkAndRefill(){
        if (remainingH == 0 && remainingO == 0) {
            remainingH = 2;
            remainingO = 1;
            releaseH.notify_all();
            releaseO.notify_one();
        }
    }
    
public:
    H2O() {
        remainingH = 2;
        remainingO = 1;
    }

    void hydrogen(function<void()> releaseHydrogen) {
        unique_lock<mutex> lk(mtx);
        releaseH.wait(lk, [this]{return remainingH != 0;});
        --remainingH;
        checkAndRefill();
        // releaseHydrogen() outputs "H". Do not change or remove this line.
        releaseHydrogen();
    }

    void oxygen(function<void()> releaseOxygen) {
        unique_lock<mutex> lk(mtx);
        releaseO.wait(lk, [this]{return remainingO != 0;});
        --remainingO;
        checkAndRefill();
        // releaseOxygen() outputs "O". Do not change or remove this line.
        releaseOxygen();
    }
};
