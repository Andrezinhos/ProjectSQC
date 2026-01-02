#include <iostream>
#include <string>
#include <filesystem>
#include "states.hpp"
#include "menu.hpp"
#include "mainMenu.hpp"
#include "SmashConfig.hpp"

namespace fs = std::filesystem;

void Menu::Smasher(States& state){
    Smash comp;
    while (true)
    {
        std::cout << "\n--- SQC SMASHER ---\n" << "\n";
        std::cout << "Select a Item:" << "\n";
        std::cout << "1 - Compress a file" << "\n";
        std::cout << "0 - return to menu" << "\n"; 
        std::cin >> state.choice;

        switch(state.choice){
            case 1: {
                std::string input, output;
                std::cout << "Enter File to Compress: ";
                std::cin >> input;
                std::cout << "Enter the ZIP output: ";
                std::cin >> output;
                if (comp.compFile(input, output)){
                    state.clearScreen();
                    std::cout << "Succesfully Compressed the File\n" << "\n";
                } else {
                    state.clearScreen();
                    std::cout << "Fail to Compress\n" << "\n";
                }
                break;
            }
            case 2: {
                std::string zip, dir;
                std::cout << "Enter ZIP File: ";
                std::cin >> zip;
                std::cout << "Enter the output directory: ";
                std::cin >> dir;
                if (comp.extrZip(zip, dir)){
                    state.clearScreen();
                    std::cout << "Succesfully extracted the File\n" << "\n";
                } else {
                    state.clearScreen();
                    std::cout << "Fail to extract\n" << "\n";
                }
                break;
            }
        }
        
        if (state.choice == 0)  {
            state.clearScreen(); 
            break;
        }
    }
}

