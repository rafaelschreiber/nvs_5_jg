/*
 * Author: Rafael Schreiber (i16066)
 * Project: 05_sync
 * File: philosopher.cpp
 * Date: 01-12-2020
 */

#include <iostream>
#include <thread>
#include <chrono>
#include "philosopher.h"

using namespace std;

void Philosopher::operator()(mutex &cout_mtx) {
    while (true){
        // thinking
        {
            lock_guard <mutex> lg{cout_mtx};
            cout << "Philosopher " << number << " is thinking..." << endl;
        }
        this_thread::sleep_for(1s);

        // left fork
        {
            lock_guard <mutex> lg{cout_mtx};
            cout << "Philosopher " << number << " attempts to get left fork" << endl;
        }
        left_fork.lock();
        {
            lock_guard <mutex> lg{cout_mtx};
            cout << "Philosopher " << number << " got left fork. Now he wants the right one...." << endl;
        }

        // right fork
        {
            lock_guard <mutex> lg{cout_mtx};
            cout << "Philosopher " << number << " attempts to get right fork" << endl;
        }
        right_fork.lock();

        // eating
        {
            lock_guard <mutex> lg{cout_mtx};
            cout << "Philosopher " << number << " got right fork. Now he is eating..." << endl;
        }
        this_thread::sleep_for(2s);
        {
            lock_guard <mutex> lg{cout_mtx};
            cout << "Philosopher " << number << " finished eating" << endl;
        }

        // unlocking
        left_fork.unlock();
        {
            lock_guard <mutex> lg{cout_mtx};
            cout << "Philosopher " << number << " released left fork" << endl;
        }
        right_fork.unlock();
        {
            lock_guard <mutex> lg{cout_mtx};
            cout << "Philosopher " << number << " released right fork" << endl;
        }
    }
}
