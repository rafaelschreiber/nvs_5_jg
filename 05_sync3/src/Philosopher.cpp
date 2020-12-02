/*
 * Author: Rafael Schreiber (i16066)
 * Project: 05_sync
 * File: philosopher.cpp
 * Date: 01-12-2020
 */

#include <iostream>
#include <mutex>
#include <initializer_list>
#include <thread>
#include <chrono>
#include "semaphore.h"
#include "philosopher.h"
#include "utils.h"

using namespace std;

void Philosopher::operator()(Semaphore* fork_counter) {
    while (true){
        // thinking
        println("Philosopher", to_string(number), "is thinking...");
        this_thread::sleep_for(1s);

        // left fork
        println("Philosopher", to_string(number), "attempts to get left fork");
        if(fork_counter != nullptr){
            fork_counter->acquire();
        }
        left_fork.lock();
        println("Philosopher", to_string(number), "got left fork. Now he wants the right one...");

        this_thread::sleep_for(5s);

        // right fork
        println("Philosopher", to_string(number), "attempts to get right fork");
        right_fork.lock();

        // eating
        println("Philosopher", to_string(number), "got right fork. Now he is eating...");
        this_thread::sleep_for(2s);
        println("Philosopher", to_string(number), "finished eating");

        // unlocking
        left_fork.unlock();
        if(fork_counter != nullptr){
            fork_counter->release();
        }
        println("Philosopher", to_string(number), "released left fork");
        println("currently", to_string(fork_counter->available_permits()), "left forks available");
        right_fork.unlock();
        println("Philosopher", to_string(number), "released right fork");
    }
}
