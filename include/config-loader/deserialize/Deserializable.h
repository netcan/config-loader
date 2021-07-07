//
// Created by netcan on 2021/07/05.
//

#ifndef CONFIG_LOADER_DESERIALIZABLE_H
#define CONFIG_LOADER_DESERIALIZABLE_H
#include <config-loader/Result.h>
#include <config-loader/utils/ConfigPath.h>
#include <config-loader/deserialize/DeserializeTraits.h>

CONFIG_LOADER_NS_BEGIN

template<typename T, typename FORMAT, typename CONFIG_CONTENT = decltype(""_path)>
struct Deserializable: private CONFIG_CONTENT {
    template<typename GET_CONTENT>
    Result load(T& obj, GET_CONTENT&& getContent) {
        return DeserializeTraits<FORMAT>::load(obj, getContent());
    }

    Result load(T& obj) {
        return DeserializeTraits<FORMAT>::load(obj, CONFIG_CONTENT::getContent());
    }
};

CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_DESERIALIZABLE_H
