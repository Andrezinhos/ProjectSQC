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
<<<<<<< Updated upstream
=======
<<<<<<< HEAD
        std::cout << "2 - look process info" << "\n";
        std::cout << "3 - kill process" << "\n";
        std::cout << "4 - save process PID" << "\n";
        std::cout << "5 - load process PID" << "\n";
=======
>>>>>>> 5f11c3df7aaddf7763465fe61907b5ef3fa782f6
>>>>>>> Stashed changes
        std::cout << "0 - return to menu" << "\n";
        std::cout << ">> ";
        std::cin >> state.choice;

<<<<<<< Updated upstream
=======
<<<<<<< HEAD
        

        switch(state.choice){
            case 1: {
                auto process = moni.listProcess();
                std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
                for (const auto& p : process){
                    std::cout << "PID: " << p.pid
                            << " | Name: " << conv.to_bytes(p.name)
                            << " | Mem: " << p.memoryUsage / 1024 << " KB\n"; 
                }
                break;
            }

            case 2: { 
                int pid; 
                std::cout << "Enter PID: "; 
                std::cin >> pid; 
                auto info = moni.getInfo(pid); 
                std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
                std::cout << "PID: " << info.pid << " | Name: " << conv.to_bytes(info.name) << " | Mem: " << info.memoryUsage / 1024 << " KB\n"; 
                break; 
            }

            case 3: { 
                int pid; 
                std::cout << "Enter PID to kill: "; 
                std::cin >> pid; 
                if (moni.killProcess(pid)) { 
                    std::cout << "Process " << pid << " terminated.\n"; 
                } else { 
                    std::cout << "Failed to terminate process " << pid << ".\n"; 
                } 
                break; 
            }

            case 4: { 
                std::string filename; 
                std::cout << "Enter filename to save snapshot: "; 
                std::cin >> filename; moni.saveSnapshot(filename); 
                std::cout << "Snapshot saved to " << filename << "\n"; 
                break; 
            }

            case 5: { 
                std::string filename; 
                std::cout << "Enter filename to load snapshot: "; 
                std::cin >> filename; 
                moni.loadSnapshot(filename); 
                std::cout << "Snapshot loaded from " << filename << "\n"; 
                break; 
            }
=======
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
=======
>>>>>>> 5f11c3df7aaddf7763465fe61907b5ef3fa782f6
>>>>>>> Stashed changes
        }

        if (state.choice == 0)  {
            state.clearScreen(); 
            break;
        }
    }
}