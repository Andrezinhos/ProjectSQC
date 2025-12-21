#pragma once
#include <vector>
#include <iostream>
#include <limits>
#include "json.hpp"
using json = nlohmann::json;

struct Task{
    std::string title;
    std::string description;
    bool done = false;
};

class TaskerList{
private:
    std::vector<Task> tasks;
public:
    void addTask(const std::string& title, const std::string& description, bool done = false);
    void listTasks(); 
    json toJson() const;
    void SaveFile(const std::string& filename) const;
    void DelFile(size_t index);
    void LoadFile(const std::string& filename);
};