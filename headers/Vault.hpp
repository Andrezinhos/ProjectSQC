#pragma once
#include <string>
#include <vector>

struct Pass {
    std::string password;
    std::string secure;  
};

class VaultFort{
    public:
    std::string addPW(const std::string& password);
    void saveHash(const std::string& hash);
    std::vector<std::string> loadHashes();
    bool verifyPassword(const std::string& password, const std::string& hash);

    Pass LockPW(const std::string& password, const std::string& key);
    std::string openPW(const Pass& pass, const std::string& key);

    void saveLock(const Pass& pass);
    std::vector<Pass> loadLock();
    void delLock(int index);
    void delHash(int index);
};