#include <iostream>
#include <string>
#include "states.hpp"
#include "menu.hpp"
#include "mainMenu.hpp"
#include "AtlasConfig.hpp"

void Menu::Atlas(States& state){
    static AtlasList links;
    const std::string saveLinkPath = "C:/ProjectSQC/bin/data/links.json";
    while (true)
    {
        std::cout << "\n--- SQC ATLAS ---\n" << "\n";
        std::cout << "Select a Item:" << "\n";
        std::cout << "1 - add new link" << "\n";
        std::cout << "2 - open link" << "\n";
        std::cout << "3 - read list" << "\n";
        std::cout << "4 - delete link" << "\n"; 
        std::cout << "0 - return to menu" << "\n"; 
        std::cin >> state.choice;
        
        std::string link;
        std::string name;

        switch(state.choice){
            case 1:
                std::cout << "Link URL: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, link);

                std::cout << "Link name: ";
                std::getline(std::cin, name);

                links.addLink(link, name);
                links.SaveLink(saveLinkPath);
                break;
            case 2:
                links.LoadLink(saveLinkPath);
                links.listLinks();
                if (links.empty()){
                    break;
                }

                std::cout << "\nWrite the Link Number to open: ";
                size_t linkNum;
                std::cin >> linkNum;
                if (linkNum == 0 || linkNum > links.size()){
                    std::cout << "Invalid link name" << "\n";  
                } else {
                    links.openLink(links.getLink(linkNum - 1).link);
                }
                break;
            case 3:
                links.LoadLink(saveLinkPath);
                links.listLinks();
                break;
            case 4:
                state.clearScreen();
                links.listLinks();
                std::cout << "Write the Link Number: ";
                size_t num;
                std::cin >> num;
                links.DelLink(num);
                break;
        }

        if (state.choice == 0) {
            state.clearScreen(); 
            break;
        }
    }
}