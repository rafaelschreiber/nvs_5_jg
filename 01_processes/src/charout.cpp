#include <iostream>
#include <chrono>
#include <thread>

int main(int argc, const char* argv[]){
    if (argc >= 2){
        while(1){
            std::cout << argv[1] << std::flush;
            std::chrono::milliseconds sleeptime(500);
            std::this_thread::sleep_for(sleeptime);
        }
    }
}
