/*
 * Author: Rafael Schreiber (i16066)
 * Project: 06_future
 * File: main.cpp
 * Date: 07-12-2020
 */

#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <chrono>
#include "CLI11.hpp"
#include "InfInt.h"
#include "calc_factors.h"

using namespace std;

void check_result(vector<InfInt> &factor_numbers, vector<shared_future<vector<InfInt>>> &future_primes){
    int index{0};
    for (auto result_future : future_primes){
        InfInt factored_number{"1"};
        for (auto prime : result_future.get()){
            factored_number *= prime;
        }
        if (factor_numbers[index] != factored_number){
            cerr << "An error occured, while calculating prime factors. Factoring doesn't match with original value";
        }
        index++;
    }
}

void print_result(vector<InfInt> &factor_numbers, vector<shared_future<vector<InfInt>>> &future_primes){
    int index{0};
    for (auto result_future : future_primes){
        cout << factor_numbers[index] << ": ";
        for (auto prime : result_future.get()){
            cout << prime << " ";
        }
        cout << endl;
        index++;
    }
}

vector<InfInt> convert_to_infint_vector(vector<string> s_vector){
    vector<InfInt> infint_vector;
    for (auto s_number : s_vector){
        InfInt infint_number = s_number;
        infint_vector.push_back(infint_number);
    }
    return infint_vector;
}

int main(int argc, char** argv) {
    vector<string> factor_numbers;
    bool do_async{false};

    CLI::App app("Factor numbers");
    app.add_option("number", factor_numbers, "numbers to factor") -> required() 
    ->  check([](const std::string &str) {
            auto is_valid = str.find_first_not_of("0123456789");
            if (is_valid == string::npos){
                return std::string();
            } else {
                return std::string(str + " contains not numeric character");
            }
        });
    app.add_flag("-a, --async", do_async, "async");
    CLI11_PARSE(app, argc, argv);

    vector<InfInt> infint_factor_numbers{convert_to_infint_vector(factor_numbers)};

    /* Print numbers with prime factors single threaded without async
    for (auto number : infint_factor_numbers){
        cout << number << ": ";
        auto prime_factors = get_factors(number);
        for (auto prime : prime_factors){
            cout << prime << " ";
        }
        cout << endl;
    }
    cout << "Async: " << async << endl;
    */

    vector<shared_future<vector<InfInt>>> future_primes_vector;
    auto start = chrono::system_clock::now();
    
    for (auto number : infint_factor_numbers){
        if (do_async){
            future_primes_vector.push_back(async(launch::async, get_factors, number));
        } else {
            future_primes_vector.push_back(async(launch::deferred, get_factors, number));
        }
    }
    future_primes_vector.at(infint_factor_numbers.size() - 1).wait();
 
    auto duration = chrono::duration_cast<chrono::milliseconds> (std::chrono::system_clock::now() - start);
    
    thread t1{check_result, ref(infint_factor_numbers), ref(future_primes_vector)};
    thread t2{print_result, ref(infint_factor_numbers), ref(future_primes_vector)};
    t1.join();
    t2.join();

    cout << "Time elapsed used for factoring: " << duration.count() << "ms" << endl;

    return 0;
}
