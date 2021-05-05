//
//  threads_typeEvenAndOdd.cpp
//  test
//
//  Created by Junyi Huang on 5/5/21.
//  Copyright © 2021 Junyi Huang. All rights reserved.
//

#include <stdio.h>
#include <thread>
#include <condition_variable>
#include <iostream>

/* the first method: using condition variable*/
std::mutex lock;
std::condition_variable oddPrint;
std::condition_variable evenPrint;
int number = 0;
const int MAX_NUMBER = 100;

/* if i == 0, do even print, else do odd print*/
void print(int i){
    while (1) {
        std::unique_lock<std::mutex> numberMutex(lock);
        if (number >= MAX_NUMBER){
            oddPrint.notify_one();
            evenPrint.notify_one();
            numberMutex.unlock();
            return;
        }
        while (number % 2 != i) {
            if (i == 0){
                evenPrint.notify_one();
                oddPrint.wait(numberMutex);
            }
            else{
                oddPrint.notify_one();
                evenPrint.wait(numberMutex);
            }
        }
        std::cout << number << "\n";
        ++number;
    }
}

int main(){
    std::thread t1(print, 0);
    std::thread t2(print, 1);
    t1.join();
    t2.join();
    
    return 0;
}

