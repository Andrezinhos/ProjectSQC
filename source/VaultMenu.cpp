#include <iostream>
#include <cstdlib>
#include <string>
#include <filesystem>
#include <vector>
#include "states.hpp"
#include "menu.hpp"
#include "mainMenu.hpp"
#include "Vault.hpp"

void Menu::Vault(States& state){
    static VaultFort vault;
    while (true)
    {
        std::cout << "\n--- SQC VAULT ---\n" << "\n";
        std::cout << "Select a Item:" << "\n";
        std::cout << "1 - Add Password" << "\n";
        std::cout << "2 - Check Passwords" << "\n";
        std::cout << "3 - List Passwords" << "\n";
        std::cout << "4 - Add secure Passwords" << "\n";
        std::cout << "5 - Check secure Passwords" << "\n";
        std::cout << "6 - Delete Passwords" << "\n";
        std::cout << "7 - Delete secure Passwords" << "\n";
        std::cout << "0 - return to menu" << "\n"; 
        std::cin >> state.choice;

        std::string pass;
        std::string master;
        int index;

        switch(state.choice){
            case 1: {
                std::cout << "Type the password: ";
                std::cin >> pass;
                
                std::cout << "Type the Master key: ";
                std::cin >> master;

                Pass p = vault.LockPW(pass, master);
                vault.saveLock(p);
                state.clearScreen();
                std::cout << "Sucess to add new password\n";
                break;
            }
            case 2:{
                auto items = vault.loadLock();
                std::cout << "Type the Index: ";
                int idx;
                std::cin >> idx;

                std::cout << "Type the Master key: ";
                std::cin >> master;

                try {
                    std::string og = vault.openPW(items[idx-1], master);
                    state.clearScreen();
                    std::cout << "OG password: " << og << "\n";
                } catch (const std::exception& e){
                    std::cerr << e.what() << "\n";
                }
                break;
            }
            case 3:{
                try {
                    std::vector<std::string> hashes = vault.loadHashes();
                    int index = 1;
                    state.clearScreen();
                    for (const auto& h : hashes){
                        std::cout << index++ << " - " << h << "\n";
                    }
                } catch (const std::exception& e) {
                    std::cerr << e.what() << "\n"; 
                }
                break;
            }
            case 4:{
                std::cout << "Type the password: ";
                std::cin >> pass;

                std::string hash = vault.addPW(pass);
                vault.saveHash(hash);
                state.clearScreen();
                std::cout << "Sucess to add new password\n";
                break;
            }
            case 5 :{
                std::string input;
                std::cout << "Type the password: ";
                std::cin >> input;

                auto hashes = vault.loadHashes();
                bool ok = false;
                for (const auto& h : hashes){
                    if (vault.verifyPassword(input, h)){
                        ok = true;
                        break;
                    }
                }
                if(ok) {
                    state.clearScreen();
                    std::cout << "Valid password: " + input;
                }
                else {
                    state.clearScreen();
                    std::cout << "Invalid password: " + input;
                }
                break;
            }
            case 6: {
                std::cout << "Type the Index of the password: ";
                std::cin >> index;
                vault.delLock(index-1);
                state.clearScreen();
                std::cout << "Sucess to delete password";
                break;
            }
            case 7: {
                std::cout << "Type the Index of the password: ";
                std::cin >> index;
                vault.delHash(index-1);
                state.clearScreen();
                std::cout << "Sucess to delete password";
                break;
            }
        }
        
        if (state.choice == 0)  {
            state.clearScreen(); 
            break;
        }
    }
}

