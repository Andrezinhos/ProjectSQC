#include "Monitor.hpp"
#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <iostream>
#include <fstream>

std::vector<Process> Monitor::listProcess() const {
    std::vector<Process> process;

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE) return process;
    
    PROCESSENTRY32W pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32W);

    if (Process32FirstW(snapshot, &pe32)){
        do {
            Process info;
            info.pid = pe32.th32ProcessID;
            info.name = pe32.szExeFile;
            info.cpuUsage = 0.0;
            info.memoryUsage = 0;

            HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, info.pid);
            if (hProcess){
                PROCESS_MEMORY_COUNTERS pmc;
                if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))){
                    info.memoryUsage = pmc.WorkingSetSize;
                }
                CloseHandle(hProcess);
            }
            process.push_back(info);
        } while (Process32NextW(snapshot, &pe32));
    }

    CloseHandle(snapshot);
    return process;
}

Process Monitor::getInfo(int pid) const{
    Process info{pid, L"", 0.0, 0};

    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, info.pid);
    if (hProcess){
        wchar_t name[MAX_PATH];
        if (GetModuleBaseNameW(hProcess, nullptr, name, MAX_PATH)){
            info.name = std::wstring(name);
        }
        PROCESS_MEMORY_COUNTERS pmc;
        if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))){
            info.memoryUsage = pmc.WorkingSetSize;
        }
        CloseHandle(hProcess);
    }
    return info;
}

bool Monitor::killProcess(int pid) {
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
    if (!hProcess) return false;
    bool success = TerminateProcess(hProcess, 0);
    CloseHandle(hProcess);
    return success;
}

void Monitor::saveSnapshot(const std::string& filename) const {
    auto procs = listProcess();
    json j = procs;
    std::ofstream file(filename);
    file << j.dump(4);
}

void Monitor::loadSnapshot(const std::string& filename){
    std::ifstream file(filename); 
    if (!file.is_open()) return; 
    json j; 
    file >> j; 
    
    std::vector<Process> procs = j.get<std::vector<Process>>();
}