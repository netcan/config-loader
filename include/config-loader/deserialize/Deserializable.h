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
namespace detail {
template<typename T, typename PARSER,
        typename DEFAULT_PATH, bool = DEFAULT_PATH::isEmpty>
struct DeserializableWithDefaultPath {
    constexpr Result load(T& obj) { // load from default config
        return DeserializeTraits<PARSER>::load(obj, DEFAULT_PATH::getContent());
    }
};

template<typename T, typename PARSER, typename DEFAULT_PATH>
struct DeserializableWithDefaultPath<T, PARSER, DEFAULT_PATH, true> {
    // if default path is empty, delete it
    constexpr Result load(T& obj) = delete;
};
}

template<typename T, typename PARSER, typename DEFAULT_PATH = decltype(""_path)>
struct Deserializable: private detail::DeserializableWithDefaultPath<T, PARSER, DEFAULT_PATH> {
    // import `default load' from default path if provide
    using detail::DeserializableWithDefaultPath<T, PARSER, DEFAULT_PATH>::load;

    template<typename GET_CONTENT>
    constexpr Result load(T& obj, GET_CONTENT&& getContent) {
        return DeserializeTraits<PARSER>::load(obj, getContent());
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
