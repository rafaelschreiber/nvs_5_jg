/*
 * Author: Rafael Schreiber (i16066)
 * Project: 02_threads
 * File: contest.cpp
 * Date: 29-09-2020
 */

#include <iostream>
#include <chrono>
#include <thread>
#include <random>

using namespace std;

class Car{
    private:
        string car_name;
        void random_sleep();
    public:
        Car(string name);
        ~Car();
        void operator()();
};

Car::Car(string name){
    car_name = name;
}

void Car::random_sleep(){
    random_device rd;
    mt19937 gen{rd()};
    uniform_real_distribution<> dis{1, 10};
    this_thread::sleep_for(chrono::milliseconds{u_int (dis(gen) * 1000)});
}

void Car::operator()(){
    int counter{0};
    string startingracemsg = {car_name + " starting race...\n"};
    cout << startingracemsg;
    while(1){
        random_sleep();
        counter++;
        string msg = {car_name + " finished Lap " + to_string(counter) + '\n'};
        cout << msg;
    }
}

Car::~Car(){
    return;
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
