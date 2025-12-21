#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include "CrawlerConfig.hpp"
#include "states.hpp"

namespace fs = std::filesystem;

std::vector<std::string> CrawlerFile::searchFilesPartial(const std::string& root, const std::string& pattern) const{
    std::vector<std::string> results;
    std::error_code ec;

    for (fs::recursive_directory_iterator it(root, fs::directory_options::skip_permission_denied, ec), end; it != end; it.increment(ec)) {
        if (ec) { ec.clear(); continue; }

        if (it->is_regular_file()){
            std::string name = it->path().filename().string();
            if (name.find(pattern) != std::string::npos){
                results.push_back(it->path().string());
            }
        }  
    }
    return results;
}


std::vector<std::string> CrawlerFile::searchFiles(const std::string& root, const std::string& filename) const{
    std::vector<std::string> results;
    fs::path rootPath(root);
    
    std::error_code ec_root;
    if (!fs::exists(rootPath, ec_root) || !fs::is_directory(rootPath, ec_root)){
        std::cerr << "Root search failed for: " << root << "\n";
        if (ec_root){
            std::cerr << "Root Error" << ec_root.message() << "Code: " << ec_root.value() << ")\n";
        }
        return results;
    }

    try {
        for (const auto& entry : fs::recursive_directory_iterator(
                 rootPath,
                 fs::directory_options::skip_permission_denied)) {
            try {
                if (entry.is_regular_file() && entry.path().filename() == filename) {
                    results.push_back(entry.path().string());
                }
            } catch (const std::exception& e) {
                std::cerr << "Error accessing entry: " << e.what() << "\n";
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error iterating root: " << e.what() << "\n";
    }

    return results;
}

void CrawlerFile::listResults(const std::vector<std::string>& results) const{
    if (results.empty()){
        std::cout << "Not find the file\n";
        return;
    }    	
    for(const auto& path : results){
        std::cout << " - " << path << "\n";
    }
}

