#include <iostream>
#include <string>
#include <cstdlib>
#include "mainMenu.hpp"
#include "states.hpp"
#include "menu.hpp"

void MainMenu::Mainface(States& state){

    Menu menu;
    system("powershell -Command \"$Host.UI.RawUI.BackgroundColor = 'DarkBlue'; Clear-Host\"");
    std::string title = R"( ____    ___    ____ 
/ ___|  / _ \  / ___|
\(___  | | | | ||   
 ___)\ | |_| | ||___ 
|____/  \__\_\ \____| 
)";
    std::cout << title;
    std::cout << "\n=========================\n";
    std::cout << "SEQUENCE MANAGER KIT\n";
    std::cout << "=========================\n";
    std::cout << "\nwhat's today work\n";
    std::cout << "----------------\n";
    std::cout << "SQC ATLAS - atls" << "\n";
    std::cout << "SQC CRAWLER - crwlr" << "\n";
    std::cout << "SQC EXCESS - exs" << "\n";
    std::cout << "SQC MONITOR - moni" << "\n";
    std::cout << "SQC SMASHER - smsh" << "\n";
    std::cout << "SQC TASKER - tskr" << "\n";
    std::cout << "SQC VAULT - vlt" << "\n";
    std::cout << "----------------" << "\n";
    std::cout << "SQC DOCS - docs" << "\n";
    std::cout << "----------------" << "\n";
    std::cout << "q - quit\n";
    std::cout << "----------------\n";
    std::cout << ">> ";
    std::cin >> state.name;

    if (state.name == "q"){
        system("powershell -Command \"$Host.UI.RawUI.BackgroundColor = 'Black'; Clear-Host\"");
        state.running = false;
        return;
    }

    if (state.name == "tskr"){
        state.clearScreen();
        menu.Tasker(state);
    }   
    
    if (state.name == "exs"){
        state.clearScreen();
        menu.Excess(state);
    }

    if (state.name == "crwlr"){
        state.clearScreen();
        menu.Crawler(state);
    }

    if (state.name == "atls"){
        state.clearScreen();
        menu.Atlas(state);
    }

    if (state.name == "vlt"){
        state.clearScreen();
        menu.Vault(state);
    }

    if (state.name == "moni"){
        state.clearScreen();
        menu.Monito(state);
    }

    if (state.name == "smsh"){
        state.clearScreen();
        menu.Smasher(state);
    }
    
    if (state.name == "docs"){
        state.clearScreen();
        menu.Doc(state);
    }
}
