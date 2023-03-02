#include <iostream>
// unordered_multiset here
#include <unordered_set>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <deque>
#include <semaphore>
using namespace std;

void printNumber(int i) {
    cout << i;
}

/* 1116. Print Zero Even Odd */

class ZeroEvenOddWithSem {
private:
  int n;
  binary sem_zero, sem_even, sem_odd;

public:
  ZeroEvenOddWithSem(int n) {
    this->n = n;
    sem_init(&sem_zero, 0, 1);
    sem_init(&sem_even, 0, 0);
    sem_init(&sem_odd, 0, 0);
  }

  // printNumber(x) outputs "x", where x is an integer.
  void zero(function<void(int)> printNumber) {
    for (int i = 0; i < n; i++) {
      sem_wait(&sem_zero);
      printNumber(0);
      if (i % 2 == 0)
        sem_post(&sem_odd);
      else
        sem_post(&sem_even);
    }
  }

  void even(function<void(int)> printNumber) {
    for (int i = 2; i <= n; i += 2) {
      sem_wait(&sem_even);
      printNumber(i);
      sem_post(&sem_zero);
    }
  }

  void odd(function<void(int)> printNumber) {
    for (int i = 1; i <= n; i += 2) {
      sem_wait(&sem_odd);
      printNumber(i);
      sem_post(&sem_zero);
    }
  }
};

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

int main() {
    ZeroEvenOddWithSem zeo(1);
    thread t1(&ZeroEvenOdd::zero, &zeo, printNumber);
    thread t2(&ZeroEvenOdd::even, &zeo, printNumber);
    thread t3(&ZeroEvenOdd::odd, &zeo, printNumber);

    t1.join();
    t2.join();
    t3.join();
    return 0;
}