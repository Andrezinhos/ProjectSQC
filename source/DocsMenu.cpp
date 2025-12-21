#include <iostream>
#include <string>
#include "states.hpp"
#include "menu.hpp"
#include "Docs.hpp"
#include "mainMenu.hpp"

void Menu::Doc(States& state){
    Docs docs;
    while (true)
    {
        std::cout << "\n--- SQC DOCS ---\n" << "\n";
        std::cout << "Select a Item:" << "\n";
        std::cout << "1 - TASKER" << "\n";
        std::cout << "2 - EXCESS" << "\n";
        std::cout << "3 - CRAWLER" << "\n";
        std::cout << "4 - ATLAS" << "\n";
        std::cout << "5 - VAULT" << "\n";
        std::cout << "6 - MICRO EDITOR" << "\n";
        std::cout << "7 - ABOUT" << "\n";
        std::cout << "0 - return to menu" << "\n";  
        std::cin >> state.choice;
        
        switch(state.choice){
            case 1:
                docs.TaskerDocs();
                std::cout << "\nType e to return\n";
                if(docs.toExit()) 
                break;
            case 2:
                docs.ExcessDocs();
                std::cout << "\nType e to return\n";
                if(docs.toExit()) 
                break;
            case 3:
                docs.CrawlerDocs();
                std::cout << "\nType e to return\n";
                if(docs.toExit()) 
                break;
            case 4:
                docs.AtlasDocs();
                std::cout << "\nType e to return\n";
                if(docs.toExit()) 
                break;
            case 5:
                docs.VaultDocs();
                std::cout << "\nType e to return\n";
                if(docs.toExit()) 
                break;
            case 6:
                docs.EditorDocs();
                std::cout << "\nType e to return\n";
                if(docs.toExit()) 
                break;
            case 6:
                docs.AboutDocs();
                std::cout << "\nType e to return\n";
                if(docs.toExit()) 
                break;
            
        }

        if (state.choice == 0){
            break;
        }
    }
}
