#include <iostream>
// unordered_multiset here
#include <unordered_set>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <deque>
using namespace std;

/* 1188. Design Bounded Blocking Queue */
class BoundedBlockingQueue {
private:
    mutex mtx;
    condition_variable waitForNotFull;
    condition_variable waitForNotEmpty;
    deque<int> queue;
    int cap;
    
    bool isFull() {
        return queue.size() == cap;
    }
    
    bool isEmpty() {
        return queue.empty();
    }
    
public:
    BoundedBlockingQueue(int capacity) {
        cap = capacity;
    }
    
    void enqueue(int element) {
        unique_lock<mutex> lk(mtx);
        waitForNotFull.wait(lk, [this]{return !isFull();});
        queue.push_front(element);
        waitForNotEmpty.notify_one();
    }
    
    int dequeue() {
        int element;
        {
            unique_lock<mutex> lk(mtx);
            waitForNotEmpty.wait(lk, [this]{return !isEmpty();});
            element = queue.back();
            queue.pop_back();
            waitForNotFull.notify_one();
        }
        return element;
    }
    
    int size() {
        unique_lock<mutex> lk(mtx);
        return (int)queue.size();
    }
};
