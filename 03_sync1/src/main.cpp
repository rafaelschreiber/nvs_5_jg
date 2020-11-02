/*
 * Author: Rafael Schreiber (i16066)
 * Project: 03_sync1
 * File: main.cpp
 * Date: 30-10-2020
 * Entschuldigen Sie Herr Professor, ich habe voll auf die
 * Aufgabe vergessen ich hoffe Sie können diese trotzdem
 * beurteilen.
 */

#include <iostream>
#include <thread>
#include "account.hpp"

using namespace std;

int main() {
    Account rich_rich;
    /* -*- Punkt 1 -*-
    rich_rich.deposit(15);
    rich_rich.withdraw(6);
    bool status = rich_rich.withdraw(10);
    cout << "Status: " << status << "; Balance: " 
         << rich_rich.get_balance() << endl;
    */

    /* -*- Punkt 2 -*-
    rich_rich.deposit(1);
    thread t1{[&]() {
             rich_rich.withdraw(1); }};
    thread t2{[&]() {
             rich_rich.withdraw(1); }};
    t1.join();
    t2.join();
    cout << "Balance: " << rich_rich.get_balance() << endl;
    */

    Depositer schreiber(&rich_rich);
    Depositer storch(&rich_rich);
    
    thread t1{&Depositer::operator(), ref(schreiber)};
    thread t2{&Depositer::operator(), ref(storch)};
    
    t1.join();
    t2.join();
    cout << "Balance: " << rich_rich.get_balance() << endl;
    
    return 0;
}
