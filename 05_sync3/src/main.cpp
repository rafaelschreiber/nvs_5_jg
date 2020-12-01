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
    mutex stdout_mtx;

    mutex fork_1;
    mutex fork_2;
    mutex fork_3;
    mutex fork_4;
    mutex fork_5;

    Philosopher p1(1, ref(fork_1), ref(fork_5), ref(stdout_mtx));
    Philosopher p2(2, ref(fork_2), ref(fork_1), ref(stdout_mtx));
    Philosopher p3(3, ref(fork_3), ref(fork_2), ref(stdout_mtx));
    Philosopher p4(4, ref(fork_4), ref(fork_3), ref(stdout_mtx));
    Philosopher p5(5, ref(fork_5), ref(fork_4), ref(stdout_mtx));

    thread t1(p1);
    thread t2(p2);
    thread t3(p3);
    thread t4(p4);
    thread t5(p5);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    return 0;
}
