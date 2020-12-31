/*
 * Author: Rafael Schreiber (i16066)
 * Project: 07_future
 * File: main.cpp
 * Date: 31-12-2020
 */

#include <thread>
#include "clock.hpp"
#include "pipe.h"

using namespace std;

class Channel{
    Pipe<long> pipe1;  // input pipe
    Pipe<long> pipe2;  // output pipe

    public:
        Channel(){ }

        Pipe<long>& get_pipe1(){
            return pipe1;
        }

        Pipe<long>& get_pipe2(){
            return pipe2;
        }
};

class TimeSlave{
    Clock machine_clock;

    public:
        TimeSlave(string machine_name, int hours, int minutes, int seconds){
            machine_clock = Clock(machine_name + "'s clock", hours, minutes, seconds);
        }

        void operator()(){ }
};

class TimeMaster{
    Clock machine_clock;

    public:
        TimeMaster(string machine_name, int hours, int minutes, int seconds){
            machine_clock = Clock(machine_name + "'s clock", hours, minutes, seconds);
        }

        void operator()(){ }
};

int main() {
    thread master{TimeMaster("master", 9, 41, 0)};
    thread slave1{TimeSlave("slave1", 9, 41, 0)};
    thread slave2{TimeSlave("slave2", 9, 41, 0)};
    
    master.join();
    slave1.join();
    slave2.join();

    return 0;
}
