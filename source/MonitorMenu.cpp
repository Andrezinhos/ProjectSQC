#include <iostream>
#include <string>
#include <codecvt> 
#include <locale>
#include "states.hpp"
#include "menu.hpp"
#include "mainMenu.hpp"
#include "Monitor.hpp"

void Menu::Monito(States& state){
    static Monitor moni;
    while (true)
    {
        std::cout << "\n--- SQC MONITOR ---\n" << "\n";
        std::cout << "Select a Item:" << "\n";
        std::cout << "1 - list process" << "\n";
        std::cout << "0 - return to menu" << "\n";
        std::cout << ">> ";
        std::cin >> state.choice;

        switch(state.choice){
            case 1:
            auto process = moni.listProcess();
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
            for (const auto& p : process){
                std::cout << "PID: " << p.pid
                          << " | Name: " << conv.to_bytes(p.name)
                          << " | Mem: " << p.memoryUsage / 1024 << " KB\n"; 
            }
                break;
        }

        if (state.choice == 0)  {
            state.clearScreen(); 
            break;
        }
    }
}