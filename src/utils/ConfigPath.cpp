//
// Created by netcan on 2021/07/07.
//
#include <config-loader/utils/ConfigPath.h>
#include <fstream>
#include <filesystem>

CONFIG_LOADER_NS_BEGIN

std::string getFileContent(const char* path) {
    std::ifstream f(path);
    auto fileSize = std::filesystem::file_size(path);
    std::string result(fileSize, '\0');
    f.read(result.data(), fileSize);
    return result;
}

CONFIG_LOADER_NS_END
