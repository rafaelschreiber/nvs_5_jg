#include <iostream>
#include <chrono>
#include <thread>
#include <unistd.h>

int main(){
    pid_t pid{fork()};
    if (pid == 0){
        while(1){
            std::cout << "A" << std::flush;
            std::chrono::milliseconds sleeptime(500);
            std::this_thread::sleep_for(sleeptime);
        }
    } else {
        while(1){
            std::cout << "B" << std::flush;
            std::chrono::milliseconds sleeptime(500);
            std::this_thread::sleep_for(sleeptime);
        }
    }
}
