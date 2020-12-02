/*
 * Author: Rafael Schreiber (i16066)
 * Project: 05_sync
 * File: main.cpp
 * Date: 01-12-2020
 */

#include <thread>
#include <mutex>
#include "philosopher.h"
#include "semaphore.h"
#include "CLI11.hpp"

using namespace std;

int main(int argc, char** argv) {
    bool nodeadlock;

    CLI::App app("Dining philosophers simulation");
    app.add_flag("-n, --nodeadlock", nodeadlock, "Prevent a deadlock at all");
    CLI11_PARSE(app, argc, argv);

    Semaphore* nodeadlock_pointer;

    if (nodeadlock){
        nodeadlock_pointer = new Semaphore();
    } else {
        nodeadlock_pointer = nullptr;
    }

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

    thread t1(p1, nodeadlock_pointer);
    thread t2(p2, nodeadlock_pointer);
    thread t3(p3, nodeadlock_pointer);
    thread t4(p4, nodeadlock_pointer);
    thread t5(p5, nodeadlock_pointer);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    return 0;
}
