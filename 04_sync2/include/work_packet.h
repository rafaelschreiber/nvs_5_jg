/*
 * Author: Rafael Schreiber (i16066)
 * Project: 04_sync
 * File: work_packet.h
 * Date: 10-11-2020
 */

#pragma once

class WorkPacket{
    private:
        int work_id;
    public:
        WorkPacket(int work_id){
            this->work_id = work_id;
        }
        int get_work_id() const {
            return this->work_id;
        }
};
