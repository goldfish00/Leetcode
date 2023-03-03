#include <iostream>
// unordered_multiset here
#include <unordered_set>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <deque>
using namespace std;

void printNumber(int i) {
    cout << i;
}

/* 1116. Print Zero Even Odd */
class ZeroEvenOdd {
private:
    mutex mtx;
    condition_variable shouldPrintZero;
    condition_variable shouldPrintNumber;
    bool hasZeroPrinted;
    int n;
    int nextNumberToPrint;
    
    // 0 for even and 1 for odd
    void printPureNumber(int i, function<void(int)> printNumber) {
        while (1) {
            unique_lock<mutex> lk(mtx);
            shouldPrintNumber.wait(lk, [this, &i]{
                return (hasZeroPrinted && nextNumberToPrint % 2 == i) || nextNumberToPrint > n;
            });
            if (nextNumberToPrint > n) {
                return;
            }
            printNumber(nextNumberToPrint++);
            hasZeroPrinted = false;
            shouldPrintZero.notify_one();
        }
    }

public:
    ZeroEvenOdd(int n) {
        this->n = n;
        nextNumberToPrint = 1;
        hasZeroPrinted = false;
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        while (1) {
            unique_lock<mutex> lk(mtx);
            shouldPrintZero.wait(lk, [this]{return !hasZeroPrinted || nextNumberToPrint > n;});
            if (nextNumberToPrint > n) {
                shouldPrintNumber.notify_all();
                return;
            }
            printNumber(0);
            hasZeroPrinted = true;
            shouldPrintNumber.notify_all();
        }
    }

    void even(function<void(int)> printNumber) {
        printPureNumber(0, printNumber);
    }

    void odd(function<void(int)> printNumber) {
        printPureNumber(1, printNumber);
    }
};

// Note that semaphores can be used instead here
class ZeroEvenOddWith3Locks {
private:
    mutex zeroLock;
    mutex oddLock;
    mutex evenLock;
    int n;
    int nextNumberToPrint;

public:
    ZeroEvenOddWith3Locks(int n) {
        this->n = n;
        nextNumberToPrint = 1;
        
        oddLock.lock();
        evenLock.lock();
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        while (1) {
            zeroLock.lock();
            if (nextNumberToPrint > n) {
                oddLock.unlock();
                evenLock.unlock();
                return;
            }
            printNumber(0);
            if (nextNumberToPrint % 2 == 0) {
                evenLock.unlock();
            } else {
                oddLock.unlock();
            }
        }
    }

    void even(function<void(int)> printNumber) {
        while (1) {
            evenLock.lock();
            if (nextNumberToPrint > n) {
                return;
            }
            printNumber(nextNumberToPrint++);
            zeroLock.unlock();
        }
    }

    void odd(function<void(int)> printNumber) {
        while (1) {
            oddLock.lock();
            if (nextNumberToPrint > n) {
                return;
            }
            printNumber(nextNumberToPrint++);
            zeroLock.unlock();
        }
    }
};

int main() {
    ZeroEvenOdd zeo(1);
    thread t1(&ZeroEvenOdd::zero, &zeo, printNumber);
    thread t2(&ZeroEvenOdd::even, &zeo, printNumber);
    thread t3(&ZeroEvenOdd::odd, &zeo, printNumber);

    t1.join();
    t2.join();
    t3.join();
    return 0;
}
