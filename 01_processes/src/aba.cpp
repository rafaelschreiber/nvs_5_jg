#include <iostream>
#include <chrono>
#include <thread>
#include <csignal>
#include <unistd.h>
#include <cerrno>

int main(){
    int status;
    pid_t a_pid{fork()};

    if (a_pid == 0){
        execl("./charout", "charout_a", "A", nullptr);
        std::cerr << strerror(errno) << std::endl;
        exit(1);
    } else if (a_pid != 0){
        pid_t b_pid{fork()};

        if (b_pid == 0){
            execl("./charout", "charout_b", "B", nullptr);
            std::cerr << strerror(errno) << std::endl;
            exit(1);
        } else if (b_pid != 0){
            sleep(3);
            kill(a_pid, SIGKILL);
            kill(b_pid, SIGKILL);
            waitpid(a_pid, &status, 0);
            waitpid(b_pid, &status, 0);
        } else {
            std::cerr << "Forking of process b failed. Exiting..." << std::endl;
            exit(1);
        }
    } else {
        std::cerr << "Forking of process a failed. Exiting..." << std::endl;
        exit(1);
    }
}
