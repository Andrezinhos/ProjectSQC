#include <vector>
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <string>
#include <fstream>
#include "AtlasConfig.hpp"
#include "states.hpp"

void AtlasList::addLink(const std::string& link, const std::string& name){
    URL u{link, name};
    links.push_back(u);
    state.clearScreen();
    std::cout << "added link: " << name << "\n";
}

void AtlasList::listLinks(){
    state.clearScreen();
    std::cout << "\n==Links List==\n";
    if (links.empty()){
        std::cout << "No Links Added\n";
    }
    else {
        for (size_t i = 0; i < links.size(); ++i) {
            std::cout << i+1 << ". " << "|name: " << links[i].name << " ||link: " << links[i].link << "\n";
        } 
    }
}

json AtlasList::toJson() const {
    json j = json::array();
    for (const auto& l : links) {
        j.push_back({
            {"link", l.link},
            {"name", l.name},
        });
    }
    return j;
}

void AtlasList::openLink(const std::string& link) {
#ifdef _WIN32
    HINSTANCE result = ShellExecuteA(0, "open", link.c_str(), 0, 0, SW_SHOWNORMAL);
    if ((INT_PTR)result <= 32){
        std::cerr << "fail to open the link" << link << "\n";
    }
#elif __APPLE__
    std::string command = "open \"" + link + "\"";
    system(command.c_str());
#else
    std::string command = "xdg-open \"" + link + "\"";
    system(command.c_str());
#endif
}

void AtlasList::SaveLink(const std::string& filename) const {
    std::ofstream out(filename, std::ios::trunc);
    if (out.is_open()){
        out << toJson().dump(4);
    }
}

void AtlasList::DelLink(size_t userIndex) {
    const std::string saveLinkPath = "C:/SQC/bin/data/links.json";
    
    if (userIndex == 0 || userIndex > links.size()){
        std::cout << "Not found Link Number\n";
        return; 
    }

    size_t internalIndex = userIndex - 1;
    std::cout << "Removing: " << links[internalIndex].link << " Link\n";
    links.erase(links.begin() + internalIndex);

    SaveLink(saveLinkPath);
}

void AtlasList::LoadLink(const std::string& filename){
    std::ifstream in(filename);
    if (!in.is_open()) return;

    json j;
    in >> j;

    links.clear();
    for (const auto& item : j) {
        URL u;
        u.link = item.value("link", "");
        u.name = item.value("name", "");
        links.push_back(u);
    }
}
