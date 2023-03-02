#include <iostream>
// unordered_multiset here
#include <unordered_set>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <deque>
using namespace std;

void printFoo() {
    cout << "Foo ";
}

void printBar() {
    cout << "Bar \n";
}

/* 1115. Print FooBar Alternately */
class FooBar {
private:
    mutex mtx;
    condition_variable fooPrintedAlready;
    condition_variable barPrintedAlready;
    int n;
    bool hasFooPrinted;

public:
    FooBar(int n) {
        this->n = n;
        hasFooPrinted = false;
    }

    void foo(function<void()> printFoo) {
        
        for (int i = 0; i < n; i++) {
            unique_lock<mutex> lk(mtx);
            barPrintedAlready.wait(lk, [this]{return !hasFooPrinted;});
            // printFoo() outputs "foo". Do not change or remove this line.
            printFoo();
            hasFooPrinted = true;
            fooPrintedAlready.notify_one();
        }
    }

    void bar(function<void()> printBar) {
        
        for (int i = 0; i < n; i++) {
            unique_lock<mutex> lk(mtx);
            fooPrintedAlready.wait(lk, [this]{return hasFooPrinted;});
            // printBar() outputs "bar". Do not change or remove this line.
            printBar();
            hasFooPrinted = false;
            barPrintedAlready.notify_one();
        }
    }
};

int main() {
    FooBar fb(10);
    thread t1(&FooBar::foo, &fb, printFoo);
    thread t2(&FooBar::bar, &fb, printBar);
    
    t1.join();
    t2.join();
    return 0;
}
