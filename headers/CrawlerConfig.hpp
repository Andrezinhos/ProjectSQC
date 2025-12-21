#pragma once
#include <vector>
#include <filesystem>

class CrawlerFile{
public:
    std::vector<std::string> searchFiles(const std::string& root, const std::string& filename) const;
    
    std::vector<std::string> searchFilesPartial(const std::string& root, const std::string& pattern) const;

    void listResults(const std::vector<std::string>& results) const;
};