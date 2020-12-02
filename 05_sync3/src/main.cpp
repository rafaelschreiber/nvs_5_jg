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
    bool nodeadlock{false};
    bool livelock{false};

    CLI::App app("Dining philosophers simulation");
    app.add_flag("-n, --nodeadlock", nodeadlock, "Prevent a deadlock at all");
    app.add_flag("-l, --livelock", livelock, "Simulate a livelock");
    CLI11_PARSE(app, argc, argv);

    Semaphore* nodeadlock_pointer;

    if (nodeadlock){
        nodeadlock_pointer = new Semaphore();
    } else {
        nodeadlock_pointer = nullptr;
    }

    timed_mutex fork_1;
    timed_mutex fork_2;
    timed_mutex fork_3;
    timed_mutex fork_4;
    timed_mutex fork_5;

    Philosopher p1(1, ref(fork_1), ref(fork_5));
    Philosopher p2(2, ref(fork_2), ref(fork_1));
    Philosopher p3(3, ref(fork_3), ref(fork_2));
    Philosopher p4(4, ref(fork_4), ref(fork_3));
    Philosopher p5(5, ref(fork_5), ref(fork_4));

    thread t1(p1, nodeadlock_pointer, livelock);
    thread t2(p2, nodeadlock_pointer, livelock);
    thread t3(p3, nodeadlock_pointer, livelock);
    thread t4(p4, nodeadlock_pointer, livelock);
    thread t5(p5, nodeadlock_pointer, livelock);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    return 0;
}
