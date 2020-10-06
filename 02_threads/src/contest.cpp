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
        int laps{0};
        double race_time{0.0};
    public:
        static double random_sleep();
        Car(string name, int laps);
        ~Car();
        void operator()();
        string get_car_name();
        double get_race_time();
};

Car::Car(string name, int laps){
    car_name = name;
    this->laps = laps;
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
    uniform_real_distribution<> dis{1, 10};
    double sleep_time{dis(gen)};
    this_thread::sleep_for(chrono::milliseconds{u_int (sleep_time * 1000)});
    return sleep_time;
}

void Car::operator()(){
    int counter{0};
    string startingracemsg = {car_name + " starting race...\n"};
    cout << startingracemsg;
    while(counter < laps){
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


void fiat_punto(double& race_time, int laps){
    string car_name{"Fiat Punto"};
    int counter{0};
    string startingracemsg = {car_name + " starting race...\n"};
    cout << startingracemsg;
    while(counter < laps){
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


void race(int laps){
    Car corsa("Opel Corsa", laps);
    thread t1{&Car::operator(), ref(corsa)};

    double total_time_punto{0.0};
    thread t2(fiat_punto, ref(total_time_punto), laps);

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
}

void help(string command){
    cout << "Usage: " << command << " [-h | --help | LAPS]\n";
}

void error(string argument){
    cout << "Could not convert: " << argument << endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "No arguments given.\nRun with --help for more information.\n";
        return 1; 
    }
    if (string(argv[1]) == "-h" || string(argv[1]) == "--help"){
        help(argv[0]);
        return 0;
    }
    try {
        size_t pos = 0;
        stoi(string(argv[1]), &pos);
        if (pos != string(argv[1]).length()){
            error(string(argv[1]));
            cout << "Run with --help for more information." << endl;
            return 1; 
        } else if (stoi(string(argv[1])) >= 1 && stoi(string(argv[1])) < 16){
            cout << "Beginning race with " << string(argv[1]) << " laps...\n";
            race(stoi(string(argv[1])));
            return 0;
        } else if (stoi(string(argv[1])) < 1 || stoi(string(argv[1])) >= 16){
            cout << "Out of range (1 <= LAPS < 16): " << string(argv[1]) << endl;
            cout << "Run with --help for more information." << endl;
            return 1;
        } else {
            error(string(argv[1]));
            cout << "Run with --help for more information." << endl;
            return 1;
        }
    } catch (...){
        error(string(argv[1]));
        cout << "Run with --help for more information." << endl;
        return 1;
    }
}
