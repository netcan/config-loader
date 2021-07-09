//
// Created by netcan on 2021/07/05.
//

#ifndef CONFIG_LOADER_DESERIALIZABLE_H
#define CONFIG_LOADER_DESERIALIZABLE_H
#include <config-loader/Result.h>
#include <config-loader/utils/ConfigPath.h>
#include <config-loader/deserialize/DeserializeTraits.h>

CONFIG_LOADER_NS_BEGIN

template<typename T, typename FORMAT, typename DEFAULT_CONFIG = decltype(""_path)>
struct Deserializable {
    template<typename GET_CONTENT>
    Result load(T& obj, GET_CONTENT&& getContent) {
        return DeserializeTraits<FORMAT>::load(obj, getContent());
    }

    Result load(T& obj) { // load from default config
        return DeserializeTraits<FORMAT>::load(obj, DEFAULT_CONFIG::getContent());
    }
};

///////////////////////////////////////////////////////////////////////////////
// helper
template<typename T, typename CONFIG_CONTENT = decltype(""_path)>
constexpr auto XMLLoader(CONFIG_CONTENT = {}) {
    return Deserializable<T, TinyXML2Tag, CONFIG_CONTENT>{};
}

template<typename T>
Result loadXMLtoObj(T& obj, std::string_view path) {
    return Deserializable<T, TinyXML2Tag>::load(obj, [&path] {
        return getFileContent(path.data());
    });
}

CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_DESERIALIZABLE_H
