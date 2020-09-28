#include <iostream>
#include <chrono>
#include <thread>
#include <csignal>
#include <unistd.h>
#include <cerrno>

int main(){

    char* a_letter{getenv("ABA_LETTER_A")};
    char* b_letter{getenv("ABA_LETTER_B")};

    int status;
    pid_t a_pid{fork()};

    if (a_pid == 0){
        if (a_letter){
            execl("./charout", "charout_a", a_letter, nullptr);
        } else {
            execl("./charout", "charout_a", "A", nullptr);
        }
        if (errno){
            std::cerr << "starting charout failed: " << strerror(errno) << std::endl;
            exit(1);
        }
    } else if (a_pid != 0){
        pid_t b_pid{fork()};

        if (b_pid == 0){
            if (b_letter){
                execl("./charout", "charout_b", b_letter, nullptr);
            } else {
                execl("./charout", "charout_b", "B", nullptr);
            }
            if (errno){
                std::cerr << "starting charout failed: " << strerror(errno) << std::endl;
                exit(1);
            }
        } else if (b_pid != 0){
            std::cout << "waiting for 3 seconds" << std::endl;
            sleep(3);
            std::cout << "\nkilling both subprocesses with pids " 
                      << a_pid << " and " << b_pid << std::endl;
            kill(a_pid, SIGKILL);
            kill(b_pid, SIGKILL);
            std::cout << "waiting for both subprocesses to be dead\n";
            waitpid(a_pid, &status, 0);
            std::cout << "subprocess " << a_pid << " exited with " 
                      << WEXITSTATUS(status) << std::endl;
            waitpid(b_pid, &status, 0);
            std::cout << "subprocess " << b_pid << " exited with " 
                      << WEXITSTATUS(status) << std::endl;
        } else {
            std::cerr << "Forking of process b failed. Exiting..." << std::endl;
            exit(1);
        }
    } else {
        std::cerr << "Forking of process a failed. Exiting..." << std::endl;
        exit(1);
    }
}
