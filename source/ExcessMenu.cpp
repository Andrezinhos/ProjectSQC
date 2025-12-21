#include <iostream>
#include <string>
#include "states.hpp"
#include "menu.hpp"
#include "mainMenu.hpp"
#include "ExcessData.hpp"

void Menu::Excess(States& state){
    static ExcessData datas;
    const std::string saveIDPath = "C:/SQC/bin/data/dataID.json";
    while (true)
    {
        std::cout << "\n--- SQC EXCESS ---\n" << "\n";
        std::cout << "Select a Item:" << "\n";
        std::cout << "1 - add new ID" << "\n";
        std::cout << "2 - add to existing ID" << "\n";
        std::cout << "3 - read data list" << "\n";
        std::cout << "4 - delete ID" << "\n";
        std::cout << "5 - delete data from ID" << "\n"; 
        std::cout << "0 - return to menu" << "\n";
        std::cout << ">> ";
        std::cin >> state.choice;
        
        std::string id;
        std::string type;
        std::string content;

        switch(state.choice){
            case 1:
                std::cout << "\nID Name: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, id);
                datas.addDataID(id);
                datas.SaveDataFile(saveIDPath);
                break;
            case 2:
                std::cout << "\nSet ID: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, id);
                
                if (!datas.hasID(id)){
                    state.clearScreen();
                    std::cout << "\nNot Found ID: " << id << "\n";
                    break;
                }

                std::cout << "Set Type: ";
                std::getline(std::cin, type);
                
                std::cout << "Set Content: ";
                std::getline(std::cin, content);

                datas.addDataToID(id, type, content);
                datas.SaveDataFile(saveIDPath);
                break;
            case 3:
                datas.LoadDataFile(saveIDPath);
                std::cout << "Enter ID: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, id);
                state.clearScreen();
                datas.showID(id);
                break;
            case 4:
                datas.LoadDataFile(saveIDPath);
                state.clearScreen();
                datas.listData();

                std::cout << "\nWrite the ID Number to delete: ";
                size_t numData;
                std::cin >> numData;
                datas.DelDataFile(numData);
                state.clearScreen();
                std::cout << "\nDeleted: " << numData << "\n";
                break;
            case 5:
                state.clearScreen();
                std::cout << "\nEnter ID: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, id);
                
                if (!datas.hasID(id)){
                    state.clearScreen();
                    std::cout << "\nNot Found ID: " << id << "\n";
                    break;
                }

                datas.showID(id);

                std::cout << "\nEnter item number to delete: ";
                size_t num;
                std::cin >> num;
                datas.DelInsideID(id, num);
                state.clearScreen();
                std::cout << "Deleted from the ID: " << id;
                break;
        }

        if (state.choice == 0)  {
            state.clearScreen(); 
            break;
        }
    }
}