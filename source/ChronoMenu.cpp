#include <iostream>
#include <string>
#include "states.hpp"
#include "menu.hpp"
#include "mainMenu.hpp"
#include "ChronoTimer.hpp"

void Menu::Chrono(States& state){
    static ChronoTime time;
    while (true)
    {
        std::cout << "\n--- SQC CHRONO ---\n" << "\n";
        std::cout << "Select a Item:" << "\n";
        std::cout << "1 - set new timer" << "\n";
        std::cout << "2 - open link" << "\n";
        std::cout << "3 - read list" << "\n";
        std::cout << "4 - delete link" << "\n"; 
        std::cout << "0 - return to menu" << "\n"; 
        std::cin >> state.choice;
        
        int seconds;
        
        switch(state.choice){
             case 1:
        		std::cout << "Set the time (seconds): ";
        		std::cin >> seconds;

        		time.setTimer(seconds);
                state.clearScreen();   	
             	break;
        }

        if (state.choice == 0)  {
            state.clearScreen(); 
            break;
        }
    }
}
