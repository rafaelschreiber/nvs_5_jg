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
        double race_time{0.0};
    public:
        static double random_sleep();
        Car(string name);
        ~Car();
        void operator()();
        string get_car_name();
        double get_race_time();
};

Car::Car(string name){
    car_name = name;
}

string Car::get_car_name(){
    return car_name;
}

double Car::get_race_time(){
    return race_time;
}

double Car::random_sleep(){
    random_device rd;
    mt19937 gen{rd()};
    uniform_real_distribution<> dis{0, 1};
    double sleep_time{dis(gen)};
    this_thread::sleep_for(chrono::milliseconds{u_int (sleep_time * 1000)});
    return sleep_time;
}

void Car::operator()(){
    int counter{0};
    string startingracemsg = {car_name + " starting race...\n"};
    cout << startingracemsg;
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
}

Car::~Car(){
    return;
}

void fiat_punto(double& race_time){
    string car_name{"Fiat Punto"};
    int counter{0};
    string startingracemsg = {car_name + " starting race...\n"};
    cout << startingracemsg;
    while(counter < 10){
        counter++;
        double lap_time = Car::random_sleep();
        race_time += lap_time;
        ostringstream buf;
        buf << setprecision(3) << lap_time << "s";     
        string info = {car_name + " finished Lap " + to_string(counter)};
        string lapinfo = {info + " (" + buf.str() + ")\n"};
        buf.str("");
        cout << lapinfo;
    }
}

int main() {
    Car corsa("Opel Corsa");
    thread t1{ref(corsa)};

    double total_time_punto{0.0};
    thread t2(fiat_punto, ref(total_time_punto));

    t1.join();
    t2.join();

    double total_time_corsa{corsa.get_race_time()};
    ostringstream buf;

    if (total_time_corsa < total_time_punto){
        buf << setprecision(4) << total_time_corsa << "s"; 
        string totalinfo_corsa {"Sieger ist: " + corsa.get_car_name() +
            " mit " + buf.str() + '\n'};
        buf.str("");
        cout << totalinfo_corsa;

        buf << setprecision(4) << total_time_punto << "s"; 
        string totalinfo_punto {"Verlierer ist: Fiat Punto mit " + 
            buf.str() + '\n'};
        buf.str("");
        cout << totalinfo_punto;
    } else if (total_time_corsa > total_time_punto) {
        buf << setprecision(4) << total_time_punto << "s"; 
        string totalinfo_punto {"Sieger ist: Fiat Punto mit " + 
            buf.str() + '\n'};
        buf.str("");
        cout << totalinfo_punto;

        buf << setprecision(4) << total_time_corsa << "s"; 
        string totalinfo_corsa {"Verlierer ist: " + corsa.get_car_name() +
            " mit " + buf.str() + '\n'};
        buf.str("");
        cout << totalinfo_corsa;
    } else {
        buf << setprecision(4) << total_time_punto << "s"; 
        string totalinfo_punto {"Unentschieden mit " + buf.str() + '\n'};
        buf.str("");
        cout << totalinfo_punto;
    }

    return 0;
}
