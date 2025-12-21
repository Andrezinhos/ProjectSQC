#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "TaskerList.hpp"
#include "states.hpp"

void TaskerList::addTask(const std::string& title, const std::string& description, bool done){
    Task t{title, description, false};
    tasks.push_back(t);
    state.clearScreen();
    std::cout << "added task: " << title << "\n";
}

void TaskerList::listTasks(){
    state.clearScreen();
    std::cout << "\n==Task List==\n";
    if (tasks.empty()){
        std::cout << "No Tasks Added\n";
    }
    else {
        for (size_t i = 0; i < tasks.size(); ++i) {
            std::cout << i+1 << ". " << tasks[i].title << " |desc: " << tasks[i].description << "\n";
        } 
    }
}

json TaskerList::toJson() const {
    json j = json::array();
    for (const auto& t : tasks) {
        j.push_back({
            {"title", t.title},
            {"description", t.description},
            {"done", t.done},
        });
    }
    return j;
}

void TaskerList::SaveFile(const std::string& filename) const {
    std::ofstream out(filename, std::ios::trunc);
    if (out.is_open()){
        out << toJson().dump(4);
    }
}

void TaskerList::DelFile(size_t userIndex) {
    const std::string savePath = "C:/SQC/bin/data/tasks.json";
    
    if (userIndex == 0 || userIndex > tasks.size()){
        std::cout << "Not found Task Number\n";
        return; 
    }

    size_t internalIndex = userIndex - 1;

    std::cout << "Removing: " << tasks[internalIndex].title << " Task\n";
    tasks.erase(tasks.begin() + internalIndex);

    SaveFile(savePath);
}

void TaskerList::LoadFile(const std::string& filename){
    std::ifstream in(filename);
    if (!in.is_open()) return;

    json j;
    in >> j;

    tasks.clear();
    for (const auto& item : j) {
        Task t;
        t.title = item.value("title", "");
        t.description = item.value("description", "");
        t.done = item.value("done", false);
        tasks.push_back(t);
    }
}
