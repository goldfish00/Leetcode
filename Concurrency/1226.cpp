#include <iostream>
// unordered_multiset here
#include <unordered_set>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>
using namespace std;

/* 1226. The Dining Philosophers */
class DiningPhilosophers {
private:
    mutex mtx;
    condition_variable canTryEating;
    int numPhilosopher;
    vector<bool> forkStates; // true means that the fork is available
    
    int getRightForkIndex(int i) {
        return (i + 1) % numPhilosopher;
    }
    
    void putDownForks(int i) {
        forkStates[i] = true;
        forkStates[getRightForkIndex(i)] = true;
    }
    
    void pickUpForks(int i) {
        forkStates[i] = false;
        forkStates[getRightForkIndex(i)] = false;
    }
    
    bool canPickUpForks(int i) {
        return forkStates[i] && forkStates[getRightForkIndex(i)];
    }
    
public:
    DiningPhilosophers(): forkStates(vector<bool>(5, true)) {
        numPhilosopher = 5;
    }

    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork) {
        {
            unique_lock<mutex> lk(mtx);
            canTryEating.wait(lk, [this, philosopher]{return canPickUpForks(philosopher);});
            pickUpForks(philosopher);
            pickLeftFork();
            pickRightFork();
        }
        
        eat();
        
        mtx.lock();
        putDownForks(philosopher);
        putLeftFork();
        putRightFork();
        canTryEating.notify_all();
        mtx.unlock();
    }
};
