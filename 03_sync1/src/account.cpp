/*
 * Author: Rafael Schreiber (i16066)
 * Project: 03_sync1
 * File: account.cpp
 * Date: 30-10-2020
 */

#include "account.hpp"

int Account::get_balance(){
    return this->balance;
}

void Account::deposit(int amount){
    this->balance += amount;
}

bool Account::withdraw(int amount){
    if (amount > this->balance){
        return false;
    } else {
        this->balance -= amount;
        return true;
    }
}
