#include "SmashConfig.hpp"
#include <iostream>
#include <fstream>

bool Smash::compFile(const std::string& inputFile, const std::string& outputZip) {
    int err = 0;
    // Cria ou sobrescreve o arquivo ZIP
    zip_t* archive = zip_open(outputZip.c_str(), ZIP_CREATE | ZIP_TRUNCATE, &err);
    if (!archive) {
        std::cerr << "Error to create ZIP: " << outputZip << "\n";
        return false;
    }

    // Cria uma fonte a partir do arquivo de entrada
    zip_source_t* source = zip_source_file(archive, inputFile.c_str(), 0, 0);
    if (!source) {
        std::cerr << "Error on creating the source " << inputFile << "\n";
        zip_close(archive);
        return false;
    }

    // Adiciona o arquivo ao ZIP
    if (zip_file_add(archive, inputFile.c_str(), source, ZIP_FL_OVERWRITE) < 0) {
        std::cerr << "Error to add " << inputFile << " to ZIP\n";
        zip_source_free(source);
        zip_close(archive);
        return false;
    }

    zip_close(archive);
    return true;
}

bool Smash::extrZip(const std::string& zipFile, const std::string& outputDir) {
    int err = 0;
    zip_t* archive = zip_open(zipFile.c_str(), 0, &err);
    if (!archive) {
        std::cerr << "Error to open ZIP: " << zipFile << "\n";
        return false;
    }

    zip_int64_t num_entries = zip_get_num_entries(archive, 0);
    for (zip_int64_t i = 0; i < num_entries; i++) {
        const char* name = zip_get_name(archive, i, 0);
        if (!name) continue;

        zip_file_t* file = zip_fopen_index(archive, i, 0);
        if (!file) continue;

        std::string outPath = outputDir + "/" + name;
        std::ofstream out(outPath, std::ios::binary);
        if (!out.is_open()) {
            std::cerr << "Error to create exit file: " << outPath << "\n";
            zip_fclose(file);
            continue;
        }

        char buf[4096];
        zip_int64_t bytes;
        while ((bytes = zip_fread(file, buf, sizeof(buf))) > 0) {
            out.write(buf, bytes);
        }

        out.close();
        zip_fclose(file);
    }

    zip_close(archive);
    return true;
}
