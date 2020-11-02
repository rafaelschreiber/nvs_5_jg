/*
 * Author: Rafael Schreiber (i16066)
 * Project: 03_sync1
 * File: account.cpp
 * Date: 30-10-2020
 */

#include <thread>
#include <mutex>
#include "account.hpp"

int Account::get_balance(){
    return this->balance;
}

void Account::deposit(int amount){
    this->balance += amount;
}

bool Account::withdraw(int amount){
    std::lock_guard<std::mutex> guard{m};
    if (amount > this->balance){
        return false;
    } else {
        std::this_thread::yield();
        this->balance -= amount;
        return true;
    }
}
