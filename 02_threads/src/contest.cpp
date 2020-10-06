/*
 * Author: Rafael Schreiber (i16066)
 * Project: 02_threads
 * File: contest.cpp
 * Date: 29-09-2020
 */

#include <iostream>
#include <thread>

using namespace std;

class Car{
    private:
        string car_name;
    public:
        Car(string name);
        ~Car();
        void operator()();
};

Car::Car(string name){
    this.car_name = name;
}

Car::operator()(){
    int counter{0};
    cout << car_name << " starting race..." << endl;
    while(1){
        counter++;
        this_thread::sleep_for(1s);
        cout << "Lap " << counter << " finished" << endl;
    }
}

void fiat_punto(){
    int counter{0};
    cout << "Fiat Punto starting race..." << endl;
    while(1){
        counter++;
        this_thread::sleep_for(2s);
        cout << "Lap " << counter << " finished" << endl;
    }
}

int main() {
    Car punto("Fiat Punto");
    Car corsa("Opel Corsa");
    thread t1{&Car::operator(), ref(punto)};
    thread t2{&Car::operator(), ref(corsa)};
    t1.join();
    t2.join();
    return 0;
}
