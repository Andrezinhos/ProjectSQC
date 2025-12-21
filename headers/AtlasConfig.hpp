#pragma once
#include <vector>
#include <iostream>
#include <limits>
#include "json.hpp"
using json = nlohmann::json;

struct URL{
    std::string link;
    std::string name;
};

class AtlasList{
private:
    std::vector<URL> links;
public:
    void addLink(const std::string& title, const std::string& description);
    void listLinks(); 
    json toJson() const;
    void SaveLink(const std::string& filename) const;
    void openLink(const std::string& name);
    void DelLink(size_t index);
    void LoadLink(const std::string& filename);

    bool empty() const { return links.empty(); }
    size_t size() const { return links.size(); }
    const URL& getLink(size_t index) const { return links.at(index); }
};