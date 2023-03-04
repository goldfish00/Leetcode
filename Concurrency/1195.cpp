#include <iostream>
// unordered_multiset here
#include <unordered_set>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <deque>
using namespace std;

void printFizz() {
    cout << "Fizz\n";
}

void printBuzz() {
    cout << "Buzz\n";
}

void printFizzbuzz() {
    cout << "Fizzbuzz\n";
}

void printNumber(int i) {
    cout << i << endl;
}

/* 1195. Fizz Buzz Multithreaded */
class FizzBuzz {
private:
    mutex mtx;
    condition_variable cv;
    int n;
    int nextToPrint;
    
    bool is5Multiple() {
        return nextToPrint % 5 == 0;
    }
    
    bool is3Multiple() {
        return nextToPrint % 3 == 0;
    }
    
    bool shouldStop() {
        return nextToPrint > n;
    }
    
public:
    FizzBuzz(int n) {
        this->n = n;
        nextToPrint = 1;
    }

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz) {
        while (1) {
            unique_lock<mutex> lk(mtx);
            cv.wait(lk, [this]{return (is3Multiple() && !is5Multiple()) || shouldStop();});
            if (shouldStop()) {
                return;
            }
            printFizz();
            ++nextToPrint;
            cv.notify_all();
        }
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz) {
        while (1) {
            unique_lock<mutex> lk(mtx);
            cv.wait(lk, [this]{return (!is3Multiple() && is5Multiple()) || shouldStop();});
            if (shouldStop()) {
                return;
            }
            printBuzz();
            ++nextToPrint;
            cv.notify_all();
        }
    }

    // printFizzBuzz() outputs "fizzbuzz".
    void fizzbuzz(function<void()> printFizzBuzz) {
        while (1) {
            unique_lock<mutex> lk(mtx);
            cv.wait(lk, [this]{return (is3Multiple() && is5Multiple()) || shouldStop();});
            if (shouldStop()) {
                return;
            }
            printFizzBuzz();
            ++nextToPrint;
            cv.notify_all();
        }
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber) {
        while (1) {
            unique_lock<mutex> lk(mtx);
            cv.wait(lk, [this]{return (!is3Multiple() && !is5Multiple()) || shouldStop();});
            if (shouldStop()) {
                return;
            }
            printNumber(nextToPrint++);
            cv.notify_all();
        }
    }
};

int main() {
    FizzBuzz fb(15);
    thread t1(&FizzBuzz::number, &fb, printNumber);
    thread t2(&FizzBuzz::fizz, &fb, printFizz);
    thread t3(&FizzBuzz::buzz, &fb, printBuzz);
    thread t4(&FizzBuzz::fizzbuzz, &fb, printFizzbuzz);
    
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    return 0;
}
