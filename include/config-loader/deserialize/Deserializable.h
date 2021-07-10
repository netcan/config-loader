//
// Created by netcan on 2021/07/05.
//

#ifndef CONFIG_LOADER_DESERIALIZABLE_H
#define CONFIG_LOADER_DESERIALIZABLE_H
#include <config-loader/Result.h>
#include <config-loader/utils/ConfigPath.h>
#include <config-loader/deserialize/DeserializeTraits.h>
#include <config-loader/parsers/TinyXML2Parser.h>
#include <config-loader/parsers/JsonCppParser.h>

CONFIG_LOADER_NS_BEGIN

template<typename T, typename PARSER, typename DEFAULT_CONFIG = decltype(""_path)>
struct Deserializable {
    template<typename GET_CONTENT>
    Result load(T& obj, GET_CONTENT&& getContent) {
        return DeserializeTraits<PARSER>::load(obj, getContent());
    }

    Result load(T& obj) { // load from default config
        return DeserializeTraits<PARSER>::load(obj, DEFAULT_CONFIG::getContent());
    }
};

///////////////////////////////////////////////////////////////////////////////
// xml helper
template<typename T, typename CONFIG_CONTENT = decltype(""_path)>
constexpr auto XMLLoader(CONFIG_CONTENT = {}) {
    return Deserializable<T, Parser<TinyXML2Tag>, CONFIG_CONTENT>{};
}

template<typename T>
Result loadXMLtoObj(T& obj, std::string_view path) {
    return Deserializable<T, Parser<TinyXML2Tag>>::load(obj, [&path] {
        return getFileContent(path.data());
    });
}

// json helper
template<typename T, typename CONFIG_CONTENT = decltype(""_path)>
constexpr auto JsonLoader(CONFIG_CONTENT = {}) {
    return Deserializable<T, Parser<JsonCppTag>, CONFIG_CONTENT>{};
}

template<typename T>
Result loadJsontoObj(T& obj, std::string_view path) {
    return Deserializable<T, Parser<JsonCppTag>>::load(obj, [&path] {
        return getFileContent(path.data());
    });
}

CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_DESERIALIZABLE_H
