//
//  Method2-usingTwoMutex.cpp
//  test
//
//  Created by Junyi Huang on 5/5/21.
//  Copyright © 2021 Junyi Huang. All rights reserved.
//

#include <stdio.h>
#include <mutex>
#include <iostream>
#include <thread>

std::mutex evenLock;
std::mutex oddLock;
int number = 0;
int MAX_NUMBER = 100;

void lock(int i){
    if (i) oddLock.lock();
    else evenLock.lock();
}

void unlock(int i){
    if (i) evenLock.unlock();
    else oddLock.unlock();
}

void print(int i){
    while (1) {
        lock(i);
        if (number > MAX_NUMBER){
            unlock(i);
            return;
        }
        std::cout << number << "\n";
        ++number;
        unlock(i);
    }
}

int main(){
    oddLock.lock();
    std::thread t1(print, 0);
    std::thread t2(print, 1);
    
    t1.join();
    t2.join();
    return 0;
}
