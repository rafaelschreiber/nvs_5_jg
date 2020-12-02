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
#inlcude <mutex>

using namespace std;

class Semaphore{
private:
    atomic<int> counter;
    mutex mtx;
    condition_variable not_empty;

public:
    Semaphore();
    Semaphore(int start_value);
    void acquire();
    void release();
    int available_permits();
};

#endif // SEMAPHORE_H
