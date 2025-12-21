#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "ExcessData.hpp"
#include "states.hpp"

std::string ExcessData::toUpper(const std::string& s) const{
    std::string result = s;
    for (auto& c : result){
        c = std::toupper(static_cast<unsigned char>(c));
    }
    return result;
}

void ExcessData::addDataID(const std::string& id){
    std::string upperID = toUpper(id);
    if (lists.find(upperID) != lists.end()){
        std::cout << "ID Already Exists" << upperID << "\n";
        return;
    }
    lists[upperID] = {};
    state.clearScreen();
    std::cout << "added the ID: " << upperID << "\n";
}

void ExcessData::addDataToID(const std::string& id, const std::string& type, const std::string& content){
    std::string dataID = toUpper(id);
    auto it = lists.find(dataID);
    it->second.push_back({dataID, type, content});

    state.clearScreen();
    std::cout << "added to the ID: " << dataID << "\n";
}

bool ExcessData::hasID(const std::string& id) const {
    return lists.find(toUpper(id)) != lists.end();
}

void ExcessData::listData(){
    state.clearScreen();
    std::cout << "\n==ID List==\n";
    
    if (lists.empty()){
        std::cout << "No Data Added\n";
    }
    else {
        int index = 0;
        for (const auto& pair : lists) {
            std::cout << index+1 << ". " << pair.first << "\n";

            for (const auto& d : pair.second){
                std::cout << "   |type: " << d.type << "\n" << "   |content: " << d.content << "\n";
            }
        } 
    }
}

json ExcessData::toJson() const {
    json j = json::array();

    for (const auto& pair : lists) {
        json IDEnter;
        IDEnter["ID"] = pair.first;

        json items = json::array();
        for (const auto& d : pair.second){
            items.push_back({
            {"type", d.type},
            {"content", d.content},
            });
        }
        
        IDEnter["items"] = items;
        j.push_back(IDEnter);
    }
    return j;
}

void ExcessData::SaveDataFile(const std::string& filename) const {
    std::ofstream out(filename, std::ios::trunc);
    if (out.is_open()){
        out << toJson().dump(4);
    }
}

void ExcessData::DelDataFile(size_t userIndex) {
    const std::string saveIDPath = "C:/SQC/bin/data/dataID.json";
    if (userIndex == 0 || userIndex > lists.size()){
        std::cout << "Not found Data Type\n";
        return; 
    }

    size_t internalIndex = userIndex - 1;

    auto it = lists.begin();
    std::advance(it, internalIndex);

    std::cout << "Removing: " << it->first << " Data\n";
    lists.erase(it);

    SaveDataFile(saveIDPath);
}

void ExcessData::DelInsideID(const std::string& id, size_t userIndex){
    std::string dataID = toUpper(id);
    const std::string saveIDPath = "C:/SQC/bin/data/dataID.json";

    auto it = lists.find(dataID);
    if (it == lists.end()){
        std::cout << "ID not found: " << id << "\n";
        return;
    }

    auto& vec = it->second;
    if (userIndex == 0 || userIndex > vec.size()){
        std::cout << "Not found data inside ID" << "\n";
        return;
    }

    size_t internalIndex = userIndex - 1;

    std::cout << "Removing: " << vec[internalIndex].type << " | " 
    << vec[internalIndex].content << "from ID: " << id << "\n";

    vec.erase(vec.begin() + internalIndex);
    
    SaveDataFile(saveIDPath);
}

void ExcessData::LoadDataFile(const std::string& filename){
    std::ifstream in(filename);
    if (!in.is_open()) return;

    json j;
    in >> j;

    lists.clear();
    for (const auto& entry : j) {
        std::string id = entry.value("ID", "");
        std::vector<Data> dataList;

        for (const auto& d : entry["items"]){
            Data data;
            data.type = d.value("type", "");
            data.content = d.value("content", "");
            dataList.push_back(data);
        }
        
        if (!id.empty()){
            lists[id] = dataList;
        }
    }
}

void ExcessData::showID(const std::string& id) const{
    std::string enterID = toUpper(id);
    auto it = lists.find(enterID);
    if (it == lists.end()){
        std::cout << "ID Not Found" << "\n";
        return;
    }

    std::cout << "\nID: " << it->first << "\n";
    for (const auto& d : it->second){
        std::cout << " |type: " << d.type << " |content: " << d.content << "\n";
    }
}
