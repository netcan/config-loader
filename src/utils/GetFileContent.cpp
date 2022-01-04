//
// Created by netcan on 2021/07/07.
//
#include <fstream>
#include <cstring>
#include <filesystem>
#include <config-loader/ConfigLoaderNS.h>

CONFIG_LOADER_NS_BEGIN

std::string getFileContent(const char* path) {
    if (path == nullptr || strlen(path) == 0) {
        return {};
    }
    std::ifstream f(path);
    auto fileSize = std::filesystem::file_size(path);
    std::string result(fileSize, '\0');
    f.read(result.data(), fileSize);
    return result;
}

CONFIG_LOADER_NS_END
