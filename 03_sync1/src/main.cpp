/*
 * Author: Rafael Schreiber (i16066)
 * Project: 03_sync1
 * File: main.cpp
 * Date: 30-10-2020
 * Entschuldigen Sie Herr Professor, ich habe voll auf die
 * Aufgabe vergessen ich hoffe Sie können sie trotzdem
 * beurteilen.
 */

#include <iostream>
#include "account.hpp"

using namespace std;

int main() {
    Account rich_rich;
    rich_rich.deposit(15);
    rich_rich.withdraw(6);
    bool status = rich_rich.withdraw(10);
    cout << "Status: " << status << "; Balance: " 
         << rich_rich.get_balance() << endl;
    return 0;
}
