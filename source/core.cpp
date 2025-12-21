#include <iostream>
#include <cstdlib>
#include <string>
#include "menu.hpp"
#include "mainMenu.hpp"
#include "states.hpp"

States state;

int main(int argc, char* argv[]) {

    MainMenu mainFace;

    if (argc > 1){
        std::string arg = argv[1];
        if (arg == "--version") {
                std::string title = R"(  ___  _  __
 / _ \| |/ /
| | | |   / 
| |_| |   \
 \___/|_|\_\
)";
            std::cout << title << "\n";
            std::cout << "SQC v0.13.2 - SEQUENCE MANAGER KIT\n";
            return 0;
        }
        if (arg == "init"){
            state.clearScreen();
            state.running = true;
            while(state.running){
                mainFace.Mainface(state);
            }
        }
        if (arg == "mail"){
            int ret = std::system("alpine");
            if (ret == -1){
                std::cout << "Not installed Alpine";
            }
            return 0;
        }
        if (arg == "help"){
            std::cout << "\nsqc init = starts the software\n";
            std::cout << "\nsqc --version = see the actual version and if is installed\n";
            std::cout << "\nsqc help = to see the commands of SQC\n";
            std::cout << "\nsqc editor = open the Micro Editor, that works with code files and text files\n\n";
            return 0;
        }
        if (arg == "editor"){
            int ret = std::system("micro ");
            if (ret == -1){
                std::cout << "Not included Micro Editor";
            }
            return 0;
        }
    }

    while(state.running){
        mainFace.Mainface(state);
    }

    return 0;
}
