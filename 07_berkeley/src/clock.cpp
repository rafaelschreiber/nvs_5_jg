/*
 * Author: Rafael Schreiber (i16066)
 * Project: 07_future
 * File: clock.cpp
 * Date: 31-12-2020
 */


#include <iostream>
#include <thread>
#include <sstream>
#include "clock.hpp"
#include "timeutils.h"

using namespace std;

void Clock::operator()(){
    ostringstream buf;
    while (true){
        this_thread::sleep_for(chrono::duration<unsigned int>(1));
        curr_time += chrono::seconds(1);
        buf << clock_name << ": " << curr_time << '\n';
        cout << buf.str() << flush;
        buf.str(""); // empty buffer
    }
}

void Clock::set_time(int hours, int minutes, int seconds){
    curr_time = ::set_time(curr_time, hours, minutes, seconds);
}

tuple<int, int, int> Clock::get_time(){
    return ::get_time(curr_time);
}
