/*
 * Author: Rafael Schreiber (i16066)
 * Project: 06_future
 * File: main.cpp
 * Date: 07-12-2020
 */

#include <iostream>
#include <vector>
#include "CLI11.hpp"

using namespace std;

int main(int argc, char** argv) {
    vector<string> large_numbers;
    bool async{false};

    CLI::App app("Factor numbers");
    app.add_option("number", large_numbers, "numbers to factor") -> required() 
    ->  check([](const std::string &str) {
            auto is_valid = str.find_first_not_of("0123456789");
            if(is_valid == string::npos){
                return std::string();
            } else {
                return std::string(str + " contains not numeric character");
            }
        });
    app.add_flag("-a, --async", async, "async");
    CLI11_PARSE(app, argc, argv);

    for(auto elem : large_numbers){
        cout << elem << endl;
    }
    cout << "Async: " << async << endl;
    return 0;
}
