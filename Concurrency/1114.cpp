#include <iostream>
// unordered_multiset here
#include <unordered_set>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>
using namespace std;

/* 1114. Print in Order */
class Foo {
private:
    mutex mtx;
    condition_variable cv2;
    condition_variable cv3;
    int stage;
    
    bool isReadyForSecond() {
        return stage == 1;
    }
    
    bool isReadyForThird() {
        return stage == 2;
    }
    
public:
    Foo() {
        stage = 0;
    }

    void first(function<void()> printFirst) {
        unique_lock<mutex> lk(mtx);
        if (stage != 0) {
            return;
        }
        
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        
        stage = 1;
        cv2.notify_one();
    }

    void second(function<void()> printSecond) {
        unique_lock<mutex> lk(mtx);
        cv2.wait(lk, [this]{return isReadyForSecond();});
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        
        stage = 2;
        cv3.notify_one();
    }

    void third(function<void()> printThird) {
        unique_lock<mutex> lk(mtx);
        cv3.wait(lk, [this]{return isReadyForThird();});
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
        
        stage = 3;
    }
};

void printFirst() {
    cout << "1\n";
}

void printSecond() {
    cout << "3\n";
}

void printThird() {
    cout << "2\n";
}

int main() {
    Foo foo;
    thread t1(&Foo::first, &foo, printFirst);
    thread t2(&Foo::third, &foo, printThird);
    thread t3(&Foo::second, &foo, printSecond);
    
    t1.join();
    t2.join();
    t3.join();
    
    return 0;
}
