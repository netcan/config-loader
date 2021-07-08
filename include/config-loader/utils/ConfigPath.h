//
// Created by netcan on 2021/07/05.
//

#ifndef CONFIG_LOADER_CONFIGPATH_H
#define CONFIG_LOADER_CONFIGPATH_H
#include <config-loader/ConfigLoaderNS.h>
#include <string_view>
#include <string>

CONFIG_LOADER_NS_BEGIN

std::string getFileContent(const char* path);

template<char... cs>
struct Path {
    static constexpr char value[] = {cs..., '\0'};
    static std::string getContent() {
        return getFileContent(value);
    }
};

#ifdef __clang__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wgnu-string-literal-operator-template"
#endif

template <typename T, T... CHs>
constexpr Path<CHs...> operator ""_path()
{ return {}; }

#ifdef __clang__
#pragma GCC diagnostic pop
#endif

CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_CONFIGPATH_H
