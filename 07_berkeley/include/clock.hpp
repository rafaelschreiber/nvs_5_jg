/*
 * Author: Rafael Schreiber (i16066)
 * Project: 07_future
 * File: clock.hpp
 * Date: 31-12-2020
 */

#ifndef _CLOCK_HPP_
#define _CLOCK_HPP_

#include <chrono>
#include "timeutils.h"

using namespace std;

class Clock{
private:
    string clock_name;
    chrono::time_point<chrono::system_clock> curr_time;

public:
    Clock(){ };

    Clock(string name) : clock_name(name){
        curr_time = chrono::system_clock::now();
    }

    Clock(string name, int hours, int minutes, int seconds) : clock_name(name){
        curr_time = ::set_time(curr_time, hours, minutes, seconds);
    }

    void operator()();

    void set_time(int hours, int minutes, int seconds);

    tuple<int, int, int> get_time();
};

#endif // _CLOCK_HPP_