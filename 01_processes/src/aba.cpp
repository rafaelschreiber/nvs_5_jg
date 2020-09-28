#include <iostream>
#include <chrono>
#include <thread>
#include <csignal>
#include <unistd.h>

int main(){
    pid_t pid{fork()};
    if (pid == 0){
        exit(EXIT_SUCCESS);
        while(1){
            std::cout << "A" << std::flush;
            std::chrono::milliseconds sleeptime(500);
            std::this_thread::sleep_for(sleeptime);
        }
    } else {
        std::cout << "Child Process pid is: " << pid << std::endl;
        sleep(10);
        /*
        int counter{0};
        while(counter < 6){
            counter++;
            std::cout << "B" << std::flush;
            std::chrono::milliseconds sleeptime(500);
            std::this_thread::sleep_for(sleeptime);
        }
        kill(pid, SIGKILL);
        std::cout << "Killed child process w/ pid: " << pid << std::endl;
        */
    }
}
