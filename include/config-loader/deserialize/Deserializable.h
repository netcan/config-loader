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
    Deserializable() = default;
    Deserializable(T, FORMAT, CONFIG_CONTENT) {}

    template<typename GET_CONTENT>
    Result load(T& obj, GET_CONTENT&& getContent) {
        return DeserializeTraits<FORMAT>::load(obj, getContent());
    }

    Result load(T& obj) {
        return DeserializeTraits<FORMAT>::load(obj, CONFIG_CONTENT::getContent());
    }
};

// C++17 deduction guide
template<typename T, typename FORMAT, typename CONFIG_CONTENT = decltype(""_path)>
Deserializable(T, FORMAT, CONFIG_CONTENT) -> Deserializable<T, FORMAT, CONFIG_CONTENT>;

CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_DESERIALIZABLE_H
