/*
 * Author: Rafael Schreiber (i16066)
 * Project: 03_sync1
 * File: account.hpp
 * Date: 30-10-2020
 */

#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include <mutex>

class Account {
    private:
        int balance{0};
        std::mutex m;
    public:
        int get_balance();
        void deposit(int amount);
        bool withdraw(int amount);
};

class Depositer {
    private:
        Account* account;
        int start_deposits{0};
    public:
        Depositer(Account* account, int init_deposits);
        void operator()();
};

#endif // ACCOUNT_HPP
