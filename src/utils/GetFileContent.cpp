//
// This project is a personal hobby work. The author hereby assigns all
// intellectual property rights in this project to Huawei Technologies Co., Ltd.,
// and imposes no obligations or liabilities on Huawei.
//
// 本项目为作者个人业余创作，作者在此声明将本项目及其衍生作品相关的全部知识产权无偿
// 转让给华为技术有限公司，且不对华为提出任何义务或责任要求。
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
