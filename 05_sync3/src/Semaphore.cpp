/*
 * Author: Rafael Schreiber (i16066)
 * Project: 05_sync
 * File: Semaphore.cpp
 * Date: 02-12-2020
 */

#include <mutex>
#include "semaphore.h"

Semaphore::Semaphore(){
    counter.store(0);
}

Semaphore::Semaphore(int start_value){
    counter.store(start_value);
}

void Semaphore::acquire(){
    unique_lock<mutex> ul{mtx};
    not_empty.wait(ul, [this](){return (counter > 0);});
    counter--;
}
void Semaphore::release(){
    counter++;
    not_empty.notify_one();
}

int available_permits(){
    return counter;
}