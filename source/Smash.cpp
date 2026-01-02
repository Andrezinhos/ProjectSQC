#include "SmashConfig.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

bool Smash::compZipFile(const std::string& inputFile, const std::string& outputZip) {
    struct archive* a = archive_write_new();
    archive_write_set_format_zip(a); // formato ZIP
    archive_write_open_filename(a, outputZip.c_str());

    struct archive_entry* entry = archive_entry_new();
    archive_entry_set_pathname(entry, inputFile.c_str());

    std::ifstream in(inputFile, std::ios::binary | std::ios::ate);
    auto size = in.tellg();
    in.seekg(0);

    archive_entry_set_size(entry, size);
    archive_entry_set_filetype(entry, AE_IFREG);
    archive_entry_set_perm(entry, 0644);

    archive_write_header(a, entry);

    char buf[8192];
    while (in.read(buf, sizeof(buf)) || in.gcount() > 0) {
        archive_write_data(a, buf, in.gcount());
    }

    archive_entry_free(entry);
    archive_write_close(a);
    archive_write_free(a);
    return true;
}


bool Smash::extrZip(const std::string& zipFile, const std::string& outputDir) {
    struct archive* a = archive_read_new();
    archive_read_support_format_zip(a); // suporte a ZIP
    archive_read_support_filter_all(a);

    if (archive_read_open_filename(a, zipFile.c_str(), 10240) != ARCHIVE_OK) {
        return false;
    }

    struct archive_entry* entry;
    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        std::string outPath = outputDir + "/" + archive_entry_pathname(entry);
        fs::create_directories(fs::path(outPath).parent_path());
        std::ofstream out(outPath, std::ios::binary);

        const void* buff;
        size_t size;
        la_int64_t offset;
        while (archive_read_data_block(a, &buff, &size, &offset) == ARCHIVE_OK) {
            out.write((const char*)buff, size);
        }
        out.close();
    }

    archive_read_close(a);
    archive_read_free(a);
    return true;
}

bool Smash::compTarFile(const std::string& inputFile, const std::string& outputTar) {
    struct archive* a = archive_write_new();
    archive_write_set_format_pax_restricted(a);
    if (archive_write_open_filename(a, outputTar.c_str()) != ARCHIVE_OK) {
        std::cerr << "Erro ao criar TAR: " << outputTar << "\n";
        return false;
    }

    struct archive_entry* entry = archive_entry_new();
    archive_entry_set_pathname(entry, inputFile.c_str());

    std::ifstream in(inputFile, std::ios::binary | std::ios::ate);
    auto size = in.tellg();
    in.seekg(0);

    archive_entry_set_size(entry, size);
    archive_entry_set_filetype(entry, AE_IFREG);
    archive_entry_set_perm(entry, 0644);

    archive_write_header(a, entry);

    char buf[8192];
    while (in.read(buf, sizeof(buf)) || in.gcount() > 0) {
        archive_write_data(a, buf, in.gcount());
    }

    archive_entry_free(entry);
    archive_write_close(a);
    archive_write_free(a);
    return true;
}

bool Smash::extrTar(const std::string& tarFile, const std::string& outputDir) {
    struct archive* a = archive_read_new();
    archive_read_support_format_tar(a);
    archive_read_support_filter_all(a);

    if (archive_read_open_filename(a, tarFile.c_str(), 10240) != ARCHIVE_OK) {
        std::cerr << "Erro ao abrir TAR: " << tarFile << "\n";
        return false;
    }

    struct archive_entry* entry;
    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        std::string outPath = outputDir + "/" + archive_entry_pathname(entry);
        fs::create_directories(fs::path(outPath).parent_path());
        std::ofstream out(outPath, std::ios::binary);

        const void* buff;
        size_t size;
        la_int64_t offset;
        while (archive_read_data_block(a, &buff, &size, &offset) == ARCHIVE_OK) {
            out.write((const char*)buff, size);
        }
        out.close();
    }

    archive_read_close(a);
    archive_read_free(a);
    return true;
}

