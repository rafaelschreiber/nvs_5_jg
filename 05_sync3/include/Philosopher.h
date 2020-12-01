/*
 * Author: Rafael Schreiber (i16066)
 * Project: 05_sync
 * File: philosopher.h
 * Date: 01-12-2020
 */

#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <thread>
#include <mutex>

using namespace std;

class Philosopher {
private:
    int number;
    mutex &left_fork;
    mutex &right_fork;

public:
    Philosopher(int _number, mutex &_left_fork, mutex &_right_fork) : left_fork(_left_fork),
                                                                      right_fork(_right_fork)
    {
        number = _number;
    }
    void operator()(mutex &cout_mtx);
};

#endif // PHILOSOPHER_H
