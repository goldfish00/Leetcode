//
//  method2_usingMutex.cpp
//  test
//
//  Created by Junyi Huang on 5/5/21.
//  Copyright © 2021 Junyi Huang. All rights reserved.
//

#include <stdio.h>
#include <mutex>
#include<thread>
#include <iostream>

/* this is like a spin lock -- we use busy waiting to solve the problem*/
int number = 0;
int MAX_NUMBER = 100;
std::mutex numberLock;

void print(int i){
    while (1) {
        if (numberLock.try_lock()) {
            if (number > MAX_NUMBER) {
                numberLock.unlock();
                return;
            }
            // busy waiting
            while (number % 2 != i) {
                numberLock.unlock();
                numberLock.lock();
            }
            if (number > MAX_NUMBER) {
                numberLock.unlock();
                return;
            }
            std::cout << number << "\n";
            ++number;
            numberLock.unlock();
        }
    }
}

int main(){
    std::thread t1(print, 0);
    std::thread t2(print, 1);
    t2.join();
    t1.join();

    return 0;
}
