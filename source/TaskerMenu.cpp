#include <iostream>
#include <string>
#include "states.hpp"
#include "menu.hpp"
#include "mainMenu.hpp"
#include "TaskerList.hpp"

void Menu::Tasker(States& state){
    static TaskerList tasks;
    const std::string savePath = "C:/SQC/bin/tasks.json";
    while (true)
    {
        std::cout << "\n--- SQC TASKER ---\n" << "\n";
        std::cout << "Select a Item:" << "\n";
        std::cout << "1 - add new item" << "\n";
        std::cout << "2 - read list" << "\n";
        std::cout << "3 - delete item" << "\n"; 
        std::cout << "0 - return to menu" << "\n"; 
        std::cin >> state.choice;
        
        std::string title;
        std::string description;
        bool done = false;

        switch(state.choice){
            case 1:
                std::cout << "Task Title: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, title);

                std::cout << "Task description: ";
                std::getline(std::cin, description);

                tasks.addTask(title, description, done);
                tasks.SaveFile(savePath);
                break;
            case 2:
                tasks.LoadFile(savePath);
                tasks.listTasks();
                break;
            case 3:
                state.clearScreen();
                tasks.listTasks();
                std::cout << "Write the Task Number: ";
                size_t num;
                std::cin >> num;
                tasks.DelFile(num);
                break;
        }

        if (state.choice == 0)  {
            state.clearScreen(); 
            break;
        }
    }
}