/*
 * Author: Rafael Schreiber (i16066)
 * Project: 04_sync
 * File: work_queue.h
 * Date: 10-11-2020
 */

#ifndef WORK_QUEUE
#define WORK_QUEUE


#include <mutex>
#include <queue>
#include <condition_variable>
#include "work_packet.h"

class WorkQueue{
    private:
        std::queue<WorkPacket> work_queue;
        std::mutex m;
        std::condition_variable not_empty;
        std::condition_variable is_full;
        size_t max_packets;
    public:
        WorkQueue(size_t max) {max_packets = max;};
        void push(WorkPacket wp);
        WorkPacket pop();
};

#endif // WORK_QUEUE