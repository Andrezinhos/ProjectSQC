#include <stdexcept>
#include <fstream>
#include <vector>
#include "sodium.h"
#include "states.hpp"
#include "Vault.hpp"

std::string toBase64(const std::vector<unsigned char>& data) { 
    size_t b64_maxlen = sodium_base64_encoded_len(data.size(), sodium_base64_VARIANT_ORIGINAL); 
    std::vector<char> b64(b64_maxlen);

    sodium_bin2base64(b64.data(), b64_maxlen, 
    data.data(), data.size(), 
    sodium_base64_VARIANT_ORIGINAL);

    return std::string(b64.data()); 
} 
std::vector<unsigned char> fromBase64(const std::string& s) { 
    std::vector<unsigned char> bin(s.size());
    size_t bin_len; 
    if (sodium_base642bin(bin.data(), bin.size(), s.c_str(), s.size(), 
        nullptr, &bin_len, nullptr, sodium_base64_VARIANT_ORIGINAL) != 0) { 
        throw std::runtime_error("Failed to decode base64"); 
    } 
    bin.resize(bin_len); 
    return bin; 
}

std::string VaultFort::addPW(const std::string& password){
    if (sodium_init() < 0){
        throw std::runtime_error("Fail to Init libsodium");
    }

    char hashed[crypto_pwhash_STRBYTES];
    if (crypto_pwhash_str(
        hashed,
        password.c_str(),
        password.size(),
        crypto_pwhash_OPSLIMIT_INTERACTIVE, 
        crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0) {
        throw std::runtime_error("Failed to make hash of password");
    }
    return std::string(hashed);
}

void VaultFort::saveHash(const std::string& hash){
    std::ofstream file("C:/SQC/bin/data/fort/vault.txt", std::ios::app);
    if (!file) throw std::runtime_error("Error to open txt");
    file << hash << std::endl;
}

std::vector<std::string> VaultFort::loadHashes() { 
    std::ifstream file("C:/SQC/bin/data/fort/vault.txt"); 
    if (!file) { 
        throw std::runtime_error("Erro ao abrir arquivo para leitura"); 
    } 
    std::vector<std::string> hashes; 
    std::string line; 
    while (std::getline(file, line)) { 
        if (!line.empty()) { 
            hashes.push_back(line); 
        } 
    } 
    return hashes; 
}

bool VaultFort::verifyPassword(const std::string& password, const std::string& hash){
    return crypto_pwhash_str_verify(hash.c_str(), password.c_str(), password.size()) == 0;
}

void VaultFort::delHash(int index){
    auto hashes = loadHashes();
    if(index  < 0 || index >= (int)hashes.size()) throw std::runtime_error("Invalid Index");

    hashes.erase(hashes.begin() + index);

    std::ofstream file("C:/SQC/bin/data/fort/vault.txt", std::ios::trunc);
    if (!file)throw std::runtime_error("Error to open file to rewrite");

    for (const auto& h : hashes){
        file << h << "\n";
    }
}

//=======Open Passwords========
Pass VaultFort::LockPW(const std::string& password, const std::string& keyStr){
    if (sodium_init() < 0){
        throw std::runtime_error("Fail to Init libsodium");
    }

    unsigned char key[crypto_secretbox_KEYBYTES];
    crypto_generichash(key, sizeof key, 
        reinterpret_cast<const unsigned char*>(keyStr.data()), keyStr.size(), nullptr, 0);
    
    unsigned char nonce[crypto_secretbox_NONCEBYTES];
    randombytes_buf(nonce, sizeof nonce);
    std::vector<unsigned char> cipher(password.size() + crypto_secretbox_MACBYTES);
    if (crypto_secretbox_easy(cipher.data(), 
        reinterpret_cast<const unsigned char*>(password.data()), password.size(), nonce, key) != 0){
            state.clearScreen();
            throw std::runtime_error("Failed to Cryptograph");
    }
    
    std::string nonceStr(reinterpret_cast<char*>(nonce), sizeof nonce);
    std::string cipherStr(reinterpret_cast<char*>(cipher.data()), cipher.size());

    Pass p;
    p.secure = toBase64(std::vector<unsigned char>(nonce, nonce+crypto_secretbox_NONCEBYTES)) + ":" + toBase64(cipher);
    return p;
}

std::string VaultFort::openPW(const Pass& pass, const std::string& keyStr){
    if (sodium_init() < 0){
        throw std::runtime_error("Fail to Init libsodium");
    }

    unsigned char key[crypto_secretbox_KEYBYTES];
    crypto_generichash(key, sizeof key, 
        reinterpret_cast<const unsigned char*>(keyStr.data()), keyStr.size(), nullptr, 0);
    
    auto sep = pass.secure.find(':');
    if (sep == std::string::npos) throw std::runtime_error("formato inválido");

    auto nonceBin = fromBase64(pass.secure.substr(0, sep));
    auto cipherBin = fromBase64(pass.secure.substr(sep + 1));

    const unsigned char* nonce = reinterpret_cast<const unsigned char*>(nonceBin.data());
    const unsigned char* cipher = reinterpret_cast<const unsigned char*>(cipherBin.data());

    size_t cipherLen = cipherBin.size();
    std::vector<unsigned char> plain(cipherLen - crypto_secretbox_MACBYTES);

    if (crypto_secretbox_open_easy(plain.data(), 
        cipher, cipherLen, nonce, key) != 0){
            state.clearScreen();
            throw std::runtime_error("Not Correct Master Key");
    }

    return std::string(reinterpret_cast<char*>(plain.data()), plain.size());
}

void VaultFort::saveLock(const Pass& pass){
    std::ofstream file("C:/SQC/bin/data/fort/openVault.txt", std::ios::app);
    if (!file) throw std::runtime_error("Error to open txt");
    file << pass.secure << std::endl;
}

std::vector<Pass> VaultFort::loadLock() {
    std::ifstream file("C:/SQC/bin/data/fort/openVault.txt", std::ios::app);
    if (!file) {
        state.clearScreen();
        throw std::runtime_error("Error to read txt");
    }
    std::vector<Pass> items;
    std::string line;
    while (std::getline(file, line)){
        if (!line.empty()){
            Pass p;
            p.secure = line;
            items.push_back(p);
        }
    }
    return items;
}

void VaultFort::delLock(int index){
    auto items = loadLock();
    if(index  < 0 || index >= (int)items.size()) throw std::runtime_error("Invalid Index");

    items.erase(items.begin() + index);

    std::ofstream file("C:/SQC/bin/data/fort/openVault.txt", std::ios::trunc);
    if (!file) throw std::runtime_error("Error to open file to rewrite");

    for (const auto& p : items){
        file << p.secure << "\n";
    }
}
