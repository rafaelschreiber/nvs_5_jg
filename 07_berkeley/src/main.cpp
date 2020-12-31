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
    Channel* slave_channel_ptr = new Channel();

    public:
        TimeSlave(string machine_name, int hours, int minutes, int seconds){
            machine_clock = Clock(machine_name + "'s clock", hours, minutes, seconds);
        }

        void operator()(){ }

        Channel* get_channel(){
            return slave_channel_ptr;
        }
};

class TimeMaster{
    Clock machine_clock;
    Channel* channel1;
    Channel* channel2;

    public:
        TimeMaster(string machine_name, int hours, int minutes, int seconds){
            machine_clock = Clock(machine_name + "'s clock", hours, minutes, seconds);
        }

        void operator()(){ }

        void set_channel1(Channel* channel){
            channel1 = channel;
        }

        void set_channel2(Channel* channel){
            channel2 = channel;
        }        
};

int main() {
    TimeMaster master("master", 9,41, 0);

    TimeSlave slave1("slave1", 12, 0, 0);
    TimeSlave slave2("slave2", 0, 0, 0);

    master.set_channel1(slave1.get_channel());
    master.set_channel2(slave2.get_channel());
    
    thread master_thread{master};
    thread slave1_thread{slave1};
    thread slave2_thread{slave2};

    master_thread.join()
    slave1_thread.join()
    slave2_thread.join()

    return 0;
}
