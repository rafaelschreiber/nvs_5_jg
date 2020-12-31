/*
 * Author: Rafael Schreiber (i16066)
 * Project: 07_future
 * File: main.cpp
 * Date: 31-12-2020
 */

#include <thread>
#include "clock.hpp"

using namespace std;

int main() {
    thread clock{Clock("testclock")};
    clock.join();

    return 0;
}
