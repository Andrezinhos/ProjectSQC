#include <iostream>
#include <string>
#include <filesystem>
#include "states.hpp"
#include "menu.hpp"
#include "mainMenu.hpp"

namespace fs = std::filesystem;

void Menu::Crawler(States& state){
    while (true)
    {
        std::cout << "\n--- SQC CRAWLER ---\n" << "\n";
        std::cout << "Select a Item:" << "\n";
        std::cout << "1 - Search for file" << "\n";
        std::cout << "2 - Partial search" << "\n";
        std::cout << "0 - return to menu" << "\n"; 
        std::cin >> state.choice;
        
        std::string folder;
        fs::path root = "C:\\";
        std::string filename;

        switch(state.choice){
            case 1: {
                // std::cout << "Root Directory: ";
                // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                // std::getline(std::cin, folder);
                
                // if (!folder.empty()){
                //     root /= folder;
                // }
                
                // std::cout << "File Name: ";
                // std::getline(std::cin, filename);

                // auto results = crawler.searchFiles(root.string(), filename);
                // state.clearScreen();
                // crawler.listResults(results);

                system("crawler");
                break;
            }
            case 2: {
                // std::cout << "Root Directory: ";
                // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                // std::getline(std::cin, folder);
                
                // if (!folder.empty()) {
                //     root /= folder;
                // }

                // std::cout << "File Word: ";
                // std::getline(std::cin, filename);

                // auto partialResults = crawler.searchFilesPartial(root.string(), filename);
                // state.clearScreen();
                // crawler.listResults(partialResults);
                break;
            }
        }
        
        if (state.choice == 0)  {
            state.clearScreen(); 
            break;
        }
    }
}

