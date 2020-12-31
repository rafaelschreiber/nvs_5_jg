/*
 * Author: Rafael Schreiber (i16066)
 * Project: 07_future
 * File: main.cpp
 * Date: 31-12-2020
 */

#include <iostream>
#include <thread>
#include <future>
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

        void set_latency(long latency_duration){
            pipe1.set_latency(latency_duration);
            pipe2.set_latency(latency_duration);
        }
};

class TimeSlave{
    Clock machine_clock;
    Channel* slave_channel_ptr = new Channel();

    public:
        TimeSlave(string machine_name, int hours, int minutes, int seconds){
            machine_clock = Clock(machine_name + "'s clock", hours, minutes, seconds);
        }

        void operator()(){ 
            thread clock{ref(machine_clock)};
            Pipe<long>& in_pipe = slave_channel_ptr->get_pipe1();
            Pipe<long>& out_pipe = slave_channel_ptr->get_pipe2();
            while (!in_pipe){
                out_pipe << machine_clock.to_time();
                long value;
                in_pipe >> value;
                machine_clock.from_time(value);   
            }
            clock.join();
        }

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

        void operator()(){ 
            thread clock{ref(machine_clock)};

            Pipe<long>& in_pipe_slave1 = channel1->get_pipe1();
            Pipe<long>& in_pipe_slave2 = channel2->get_pipe1();

            Pipe<long>& out_pipe_slave1 = channel1->get_pipe2();
            Pipe<long>& out_pipe_slave2 = channel2->get_pipe2();

            long slave1_time; 
            long slave2_time;

            while (true){             
                slave1_time = 0;
                out_pipe_slave1 >> slave1_time;
                
                slave2_time = 0;
                out_pipe_slave2 >> slave2_time;
    
                long average_time = (slave1_time + slave2_time + machine_clock.to_time()) / 3;
                machine_clock.from_time(average_time);
                
                auto sync_slave1 = async(launch::async, [&]{in_pipe_slave1 << average_time;});
                auto sync_slave2 = async(launch::async, [&]{in_pipe_slave2 << average_time;});               
                this_thread::sleep_for(10s);
            }

            this_thread::sleep_for(500ms);
            in_pipe_slave1.close();
            in_pipe_slave2.close();
            clock.join();
        }

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

    master_thread.join();
    slave1_thread.join();
    slave2_thread.join();

    return 0;
}
