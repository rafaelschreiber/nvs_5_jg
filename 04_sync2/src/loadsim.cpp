/*
 * Author: Rafael Schreiber (i16066)
 * Project: 04_sync
 * File: loadsim.cpp
 * Date: 10-11-2020
 */

#include <iostream>
#include <thread>
#include <chrono>
#include "work_queue.h"
#include "work_packet.h"

using namespace std;

int main() {
    int counter{0};
    WorkQueue wq;
    while (true){
        wq.push(WorkPacket{counter});
        cout << "B: Submitted work packet " << counter << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
        counter++;
    }
}
