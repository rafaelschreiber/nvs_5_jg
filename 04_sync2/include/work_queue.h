/*
 * Author: Rafael Schreiber (i16066)
 * Project: 04_sync
 * File: work_queue.h
 * Date: 10-11-2020
 */

#ifndef WORK_QUEUE
#define WORK_QUEUE

#include "work_packet.h"
#include <mutex>
#include <queue>

class WorkQueue{
    private:
        std::queue<WorkPacket> work_queue;
        std::mutex m;
    public:
        WorkQueue();
        void push(WorkPacket wp);
        bool pop();
};

#endif // WORK_QUEUE