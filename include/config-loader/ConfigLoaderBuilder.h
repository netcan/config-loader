//
// Created by netcan on 2021/07/05.
//

#ifndef CONFIG_LOADER_CONFIGLOADERBUILDER_H
#define CONFIG_LOADER_CONFIGLOADERBUILDER_H
#include <config-loader/Result.h>

CONFIG_LOADER_NS_BEGIN

template<typename T, typename PATH_STR>
struct Deserializable {
    Result load(T&);
};

CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_CONFIGLOADERBUILDER_H
