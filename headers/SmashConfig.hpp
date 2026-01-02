#pragma once
#include <string>
#include <zip.h>

class Smash {
public:
    // Cria um arquivo ZIP e adiciona um arquivo existente
    bool compFile(const std::string& inputFile, const std::string& outputZip);

    // Extrai um arquivo ZIP para uma pasta
    bool extrZip(const std::string& zipFile, const std::string& outputDir);
};
