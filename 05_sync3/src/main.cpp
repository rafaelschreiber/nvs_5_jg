/*
 * Author: Rafael Schreiber (i16066)
 * Project: 05_sync
 * File: main.cpp
 * Date: 01-12-2020
 */

#include <thread>
#include <mutex>
#include "philosopher.h"

using namespace std;

int main() {
    mutex cout_mtx;

    mutex fork_1;
    mutex fork_2;
    mutex fork_3;
    mutex fork_4;
    mutex fork_5;

    Philosopher p1(1, ref(fork_1), ref(fork_5));
    Philosopher p2(2, ref(fork_2), ref(fork_1));
    Philosopher p3(3, ref(fork_3), ref(fork_2));
    Philosopher p4(4, ref(fork_4), ref(fork_3));
    Philosopher p5(5, ref(fork_5), ref(fork_4));

    thread t1(p1, ref(cout_mtx));
    thread t2(p2, ref(cout_mtx));
    thread t3(p3, ref(cout_mtx));
    thread t4(p4, ref(cout_mtx));
    thread t5(p5, ref(cout_mtx));

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    return 0;
}
