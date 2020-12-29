/*
 * Author: Rafael Schreiber (i16066)
 * Project: 06_future
 * File: main.cpp
 * Date: 07-12-2020
 */

#include <iostream>
#include <vector>
#include "CLI11.hpp"
#include "calc_factors.h"
#include "InfInt.h"

using namespace std;

vector<InfInt> convert_to_infint_vector(vector<string> s_vector){
    vector<InfInt> infint_vector;
    for(auto s_number : s_vector){
        InfInt infint_number = s_number;
        infint_vector.push_back(infint_number);
    }
    return infint_vector;
}

int main(int argc, char** argv) {
    vector<string> factor_numbers;
    bool async{false};

    CLI::App app("Factor numbers");
    app.add_option("number", factor_numbers, "numbers to factor") -> required() 
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

    vector<InfInt> infint_factor_numbers = convert_to_infint_vector(factor_numbers);

    for(auto elem : infint_factor_numbers){
        cout << elem << ": ";
        auto elem_factors = get_factors(elem);
        for (auto factor : elem_factors){
            cout << factor << " ";
        }
        cout << endl;
    }
    cout << "Async: " << async << endl;
    return 0;
}
