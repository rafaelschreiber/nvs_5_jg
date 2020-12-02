/*
 * Author: Rafael Schreiber (i16066)
 * Project: 05_sync
 * File: Semaphore.h
 * Date: 02-12-2020
 */

#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <atomic>
#include <condition_variable>
#include <mutex>

using namespace std;

class Semaphore{
private:
    const int MAXIMUM = 4; // because not more than four forks are allowed to be occupied
    atomic<int> counter;
    mutex mtx;
    condition_variable not_empty;
    condition_variable not_maximum;

public:
    Semaphore();
    Semaphore(int start_value);
    void release();
    void acquire();
    int available_permits();
};

#endif // SEMAPHORE_H
