#pragma once
#include <string>
#include <vector>
#include "json.hpp"

using json = nlohmann::json;

struct Process {
    int pid;
    std::wstring name;
    double cpuUsage;
    size_t memoryUsage;
};

inline void to_json(json& j, const Process& p){
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
    j = json{ 
        {"pid", p.pid}, 
        {"name", conv.to_bytes(p.name)}, 
        {"cpuUsage", p.cpuUsage}, 
        {"memoryUsage", p.memoryUsage} 
    };
}

inline void from_json(const json& j, Process& p){
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv; 
    std::string utf8name;
    j.at("pid").get_to(p.pid);
    j.at("name").get_to(utf8name);
    p.name = conv.from_bytes(utf8name);
    j.at("cpuUsage").get_to(p.cpuUsage);
    j.at("memoryUsage").get_to(p.memoryUsage);
}

class Monitor{
public:

    std::vector<Process> listProcess() const;

    Process getInfo(int pid) const;
    bool killProcess(int pid);
    void saveSnapshot(const std::string& filename) const;
    void loadSnapshot(const std::string& filename);

private:
    std::vector<Process> fetchProcess() const;
};