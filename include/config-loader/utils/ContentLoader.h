//
// Created by netcan on 2021/07/18.
//

#ifndef CONFIG_LOADER_CONTENTLOADER_H
#define CONFIG_LOADER_CONTENTLOADER_H
#include <string_view>
#include <functional>
#include <config-loader/ConfigLoaderNS.h>
#include <config-loader/utils/ConfigPath.h>

CONFIG_LOADER_NS_BEGIN

struct ContentLoader {
    template<typename GET_CONTENT,
            std::enable_if_t<std::is_invocable_v<GET_CONTENT>>* = nullptr>
    ContentLoader(GET_CONTENT&& getContent): getContent(getContent) {}

    template<typename STRING,
            std::enable_if_t<std::is_convertible_v<STRING, std::string_view>>* = nullptr>
    ContentLoader(STRING&& path): path(path) {}

    std::string operator()() const {
        if (path.empty()) {
            return getContent();
        } else {
            return getFileContent(path.data());
        }
    }
private:
    const std::string_view path;
    const std::function<std::string()> getContent;
};

CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_CONTENTLOADER_H
