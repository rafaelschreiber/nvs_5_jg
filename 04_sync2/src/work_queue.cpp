/*
 * Author: Rafael Schreiber (i16066)
 * Project: 04_sync
 * File: work_queue.cpp
 * Date: 10-11-2020
 */

#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include "work_queue.h"
#include "work_packet.h"

using namespace std;

void WorkQueue::push(WorkPacket wp){
    unique_lock lck{m};
    is_full.wait(lck, [this](){ return work_queue.size() < max_packets;});
    work_queue.push(wp);
    not_empty.notify_one();
}

WorkPacket WorkQueue::pop(){
    unique_lock<mutex> lck{m};
    not_empty.wait(lck, [this]{return work_queue.size();});
    WorkPacket return_elem = work_queue.front();
    work_queue.pop();
    is_full.notify_one();
    return return_elem;
}
