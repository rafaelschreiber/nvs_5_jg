#include <iostream>
#include <unistd.h>

int main(){
    std::cout << "was geht jungs!" << std::endl;
    auto pid{fork()};
    if (pid == 0){
        while(1){
            std::cout << 'A' << std::flush;;
            sleep(1);
        }
    } else {
        while(1){
            std::cout << 'B' << std::flush;
            sleep(1);
        }
    }
}