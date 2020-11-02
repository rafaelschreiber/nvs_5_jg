/*
 * Author: Rafael Schreiber (i16066)
 * Project: 03_sync1
 * File: account.hpp
 * Date: 30-10-2020
 */

#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

class Account {
    private:
        int balance{0};
    public:
        int get_balance();
        void deposit(int amount);
        bool withdraw(int amount);
};

#endif // ACCOUNT_HPP
