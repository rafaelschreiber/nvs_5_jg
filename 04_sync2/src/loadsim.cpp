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
#include "work_queue.h"
#include "work_packet.h"

using namespace std;

void worker(int id, WorkQueue& q){
    ostringstream buf;
    while(true){
        buf << "W" << id << ": Want work packet" << endl;
        cout << buf.str() << flush;
        buf.str("");
        WorkPacket current_packet = q.pop();
        buf << "W" << id << ": Got work packet " 
             << current_packet.get_work_id() << endl;
        cout << buf.str() << flush;
        buf.str("");
        this_thread::sleep_for(chrono::milliseconds(1000));
        buf << "W" << id << ": Processed work packet "
             << current_packet.get_work_id() << endl;
        cout << buf.str() << flush;
        buf.str("");
    }
}

int main() {
    WorkQueue wq{};
    for (int counter{0}; counter <= 10; counter++){
        wq.push(WorkPacket{counter});
        cout << "B: Submitted work packet " << counter << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }

    thread worker1{worker, 1, ref(wq)};
    thread worker2{worker, 2, ref(wq)};

    worker1.join();
    worker2.join();

    return EXIT_SUCCESS;
}
