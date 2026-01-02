#pragma once
#include <string>
#include <zip.h>
#include <archive.h>
#include <archive_entry.h>

class Smash {
public:
    bool compZipFile(const std::string& inputFile, const std::string& outputZip);
    bool compTarFile(const std::string& inputFile, const std::string& outputTar);
    bool extrZip(const std::string& zipFile, const std::string& outputDir);
    bool extrTar(const std::string& tarFile, const std::string& outputDir);
};
