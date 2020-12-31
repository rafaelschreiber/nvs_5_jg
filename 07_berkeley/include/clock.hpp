/*
 * Author: Rafael Schreiber (i16066)
 * Project: 07_future
 * File: clock.hpp
 * Date: 31-12-2020
 */

#ifndef _CLOCK_HPP_
#define _CLOCK_HPP_

#include <chrono>

using namespace std;

class Clock{
private:
    string clock_name;
    chrono::time_point<chrono::system_clock> curr_time;

public:
    Clock(string name) : clock_name(name){
        curr_time = chrono::system_clock::now();
    }

    void operator()();
    
};

#endif // _CLOCK_HPP_