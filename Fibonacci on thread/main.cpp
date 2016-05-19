
#include <memory>
#include <thread>
#include <vector>
#include <iostream>

#include <unistd.h>
#include <termios.h>

#include "fibonacci.hpp"

const int MAX_THREAD = 20;

int getch();
void Preview();
void Start();

int main() {
    Start();
    return 0;
}

void Preview() {
    std::cout << "Fibonacci numbers" << std::endl;
    std::cout << "Press '+' to add process" << std::endl;
    std::cout << "Press '-' to stop process" << std::endl;
    std::cout << "Press 'q' to exit" << std::endl;
}

void Start() {
    bool work = true;
    std::vector<std::unique_ptr<spo::Fibonacci>> object;
    Preview();
    while(work) {
        switch(char s = getch()) {
        case '+' :
        {
            if(object.size() > MAX_THREAD) {
                break;
            }
            std::unique_ptr<spo::Fibonacci> fib =
                std::unique_ptr<spo::Fibonacci>(new spo::Fibonacci());
            fib->Start();
            object.push_back(std::move(fib));

        }
        break;
        case '-' :
        {
            if(object.size() == 0) {
                break;
            }
            object.back()->Stop();
            object.pop_back();
        }
        break;
        case 'q' :
        {
            work = false;
        }
        break;
        }
    }
    for(auto& o : object) {
        o->Stop();
    }
    object.clear();
}

int getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    fflush(STDIN_FILENO);
    return ch;
}

