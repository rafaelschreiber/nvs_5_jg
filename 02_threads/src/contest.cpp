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
#include <sstream>
#include <iomanip>

using namespace std;

class Car{
    private:
        string car_name;
        double random_sleep();
    public:
        Car(string name);
        ~Car();
        void operator()();
};

Car::Car(string name){
    car_name = name;
}

double Car::random_sleep(){
    random_device rd;
    mt19937 gen{rd()};
    uniform_real_distribution<> dis{1, 10};
    double sleep_time{dis(gen)};
    this_thread::sleep_for(chrono::milliseconds{u_int (sleep_time * 1000)});
    return sleep_time;
}

void Car::operator()(){
    int counter{0};
    string startingracemsg = {car_name + " starting race...\n"};
    cout << startingracemsg;
    double race_time{0.0};
    while(counter < 10){
        counter++;
        double lap_time = random_sleep();
        race_time += lap_time;
        ostringstream buf;
        buf << setprecision(3) << lap_time << "s";     
        string info = {car_name + " finished Lap " + to_string(counter)};
        string lapinfo = {info + " (" + buf.str() + ")\n"};
        buf.str("");
        cout << lapinfo;
    }
    ostringstream buf;
    buf << setprecision(3) << race_time << "s"; 
    string totalinfo {car_name + " finished race in " + buf.str() + '\n'};
    buf.str("");
    cout << totalinfo;
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
