#include <iostream>
#include <chrono>
#include <thread>
#include <csignal>
#include <unistd.h>
#include <cerrno>

int main(){
    pid_t pid{fork()};
    if (pid == 0){
        execl("./charout", "charout", "A", nullptr);
        std::cerr << strerror(errno) << std::endl;
        exit(1);
    } else {
        int counter{0};
        while(counter < 6){
            counter++;
            std::cout << "B" << std::flush;
            std::chrono::milliseconds sleeptime(500);
            std::this_thread::sleep_for(sleeptime);
        }
        kill(pid, SIGKILL);
        std::cout << "Killed child process w/ pid: " << pid << std::endl;
    }
}
