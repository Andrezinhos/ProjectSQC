#include <iostream>
#include <string>
#include "states.hpp"
#include "menu.hpp"
#include "mainMenu.hpp"
#include "SmashConfig.hpp"

Smash comp;
bool tZIP = false;
bool tTAR = false;

void typeComp(std::string file, std::string entry, std::string out) {
    if (entry == "zip"){
        if (comp.compZipFile(file, out)){
            state.clearScreen();
            std::cout << "Succesfully Compressed the File\n" << "\n";
        } else {
            state.clearScreen();
            std::cout << "Fail to Compress\n" << "\n";
        }
    }
    else if (entry == "tar"){
        if (comp.compTarFile(file, out)){
            state.clearScreen();
            std::cout << "Succesfully Compressed the File\n" << "\n";
        } else {
            state.clearScreen();
            std::cout << "Fail to Compress\n" << "\n";
        }
    }
}

void typeExtr(std::string file, std::string entry, std::string out) {
    if (entry == "zip"){
        if (comp.extrZip(file, out)){
            state.clearScreen();
            std::cout << "Succesfully extracted the File\n" << "\n";
        } else {
            state.clearScreen();
            std::cout << "Fail to extract\n" << "\n";
        }
    }
    else if (entry == "tar"){
        if (comp.extrTar(file, out)){
            state.clearScreen();
            std::cout << "Succesfully extracted the File\n" << "\n";
        } else {
            state.clearScreen();
            std::cout << "Fail to extract\n" << "\n";
        }
    }
}

void Menu::Smasher(States& state){
    while (true)
    {
        std::cout << "\n--- SQC CRUSHER ---\n" << "\n";
        std::cout << "Select a Item:" << "\n";
        std::cout << "1 - Compact file" << "\n";
        std::cout << "2 - Extract File" << "\n";
        std::cout << "0 - return to menu" << "\n"; 
        std::cin >> state.choice;

        std::string input, output;
        std::string file;
        std::string ext;

        switch(state.choice){
            case 1: {
                std::cout << "Enter File to Compress: ";
                std::cin >> file;
                std::cout << "Enter format type:\n";
                std::cout << "zip\n";
                std::cout << "tar\n" << "\n";
                std::cout << ">> ";
                std::cin >> input;
                if (input == "zip") tZIP = true;
                if (input == "tar") tTAR = true;
                std::cout << "Enter the " << input << " output name: ";
                std::cin >> output;
                if (tZIP == true) ext = ".zip";
                if (tTAR == true) ext = ".tar";
                typeComp(file, input, output + ext);
                break;
            }
            case 2: {
                std::cout << "Enter File Name: ";
                std::cin >> file;
                std::cout << "Enter format type:\n";
                std::cout << "zip\n";
                std::cout << "tar\n" << "\n";
                std::cout << ">> ";
                std::cin >> input;
                std::cout << "Enter the " << input << " output directory name: ";
                std::cin >> output;
                typeExtr(file, input, output);
                break;
            }
        }
     
        if (state.choice == 0)  {
            state.clearScreen(); 
            break;
        }
    }
}
