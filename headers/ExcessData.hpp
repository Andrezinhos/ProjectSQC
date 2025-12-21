#pragma once
#include <vector>
#include <string>
#include <limits>
#include "json.hpp"
using json = nlohmann::json;

struct Data{
    std::string id;
    std::string type;
    std::string content;
};

class ExcessData{
private:
    std::map<std::string, std::vector<Data>> lists;

    std::string toUpper(const std::string& s) const;
public:
    void addDataID(const std::string& id);
    void addDataToID(const std::string& id, const std::string& type, const std::string& content);
    bool hasID(const std::string& id) const;
    void listData(); 
    json toJson() const;
    void SaveDataFile(const std::string& filename) const;
    void DelDataFile(size_t index);
    void DelInsideID(const std::string& id, size_t userIndex);
    void LoadDataFile(const std::string& filename);
    void showID(const std::string& id) const;
};