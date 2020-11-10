/*
 * Author: Rafael Schreiber (i16066)
 * Project: 04_sync
 * File: loadsim.cpp
 * Date: 10-11-2020
 */

#include <iostream>
#include <thread>
#include <chrono>
#include <sstream>
#include <random>
#include <iomanip>
#include "work_queue.h"
#include "work_packet.h"

using namespace std;

void worker(int id, WorkQueue& q){
    random_device rd;
    mt19937 gen{rd()};
    uniform_real_distribution<> dis{1, 10};
    double sleep_time{};
    
    ostringstream buf;
    while(true){
        sleep_time = dis(gen);
        buf << "W" << id << ": Want work packet" << endl;
        cout << buf.str() << flush;
        buf.str("");
        WorkPacket current_packet = q.pop();
        buf << "W" << id << ": Got work packet " 
            << current_packet.get_work_id() << endl;
        cout << buf.str() << flush;
        buf.str("");
        this_thread::sleep_for(chrono::milliseconds(u_int (sleep_time * 1000)));
        buf << "W" << id << ": Processed work packet "
            << current_packet.get_work_id() << setprecision(2)  
            << " (" << sleep_time << "s)" << endl;
        cout << buf.str() << flush;
        buf.str("");
    }
}

int main() {
    WorkQueue wq{};
    thread worker1{worker, 1, ref(wq)};
    thread worker2{worker, 2, ref(wq)};
    thread worker3{worker, 3, ref(wq)};

    ostringstream buf;
    random_device rd;
    mt19937 gen{rd()};
    uniform_real_distribution<> dis{0, 1};
    double sleep_time{};

    for (int counter{0}; counter <= 10; counter++){
        sleep_time = dis(gen);
        buf << "B:  Waiting to submit work packet " << counter << endl;
        cout << buf.str() << flush;
        buf.str("");
        this_thread::sleep_for(chrono::milliseconds(u_int (sleep_time * 1000)));
        wq.push(WorkPacket{counter});
        buf << "B:  Submitted work packet " << counter << setprecision(2) 
            << " (" << sleep_time << "s)" << endl;
        cout << buf.str() << flush;
        buf.str("");
    }

    worker1.join();
    worker2.join();
    worker3.join();

    return EXIT_SUCCESS;
}
