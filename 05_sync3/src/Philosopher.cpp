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

void Philosopher::operator()(Semaphore* fork_counter, bool livelock) {
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
        if (livelock){
            while(!right_fork.try_lock_for(chrono::seconds(3))) {
                this_thread::sleep_for(100ms);

                if (fork_counter != nullptr) {
                    fork_counter->release();
                }

                left_fork.unlock();
                println("Philosopher", to_string(number), "released left fork due to timeout getting the right one!");
            }
            this_thread::sleep_for(3s);
            continue;
        } else {
            right_fork.lock();
        }

        // eating
        println("Philosopher", to_string(number), "got right fork. Now he is eating...");
        this_thread::sleep_for(2s);
        println("Philosopher", to_string(number), "finished eating");

        // unlocking
        if(fork_counter != nullptr){
            fork_counter->release();
        }
        left_fork.unlock();
        println("Philosopher", to_string(number), "released left fork");
        println("currently", to_string(fork_counter->available_permits()), "left forks available");
        right_fork.unlock();
        println("Philosopher", to_string(number), "released right fork");
    }
}
