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
template<typename T, typename PARSER, typename DEFAULT_PATH>
struct DeserializableWithGetContent {
    template<typename GET_CONTENT>
    static Result load(T& obj, GET_CONTENT&& getContent) {
        std::string content(getContent());
        if (content.empty()) { return Result::ERR_EMPTY_CONTENT; }

        PARSER parser;
        CFL_EXPECT_SUCC(parser.parse(content.data()));

        auto firstElem = parser.toRootElemType();
        if (! firstElem.isValid()) { return Result::ERR_MISSING_FIELD; }
        return detail::CompoundDeserializeTraits<T>::deserialize(obj, firstElem);
    }
};

}

template<typename T, typename PARSER, typename DEFAULT_PATH = decltype(""_path), bool = DEFAULT_PATH::isEmpty>
struct Deserializable: private detail::DeserializableWithGetContent<T, PARSER, DEFAULT_PATH> {
    // import load with getContent func obj
    using detail::DeserializableWithGetContent<T, PARSER, DEFAULT_PATH>::load;

    // load from default path if not empty
    static Result load(T& obj) {
        return load(obj, [] { return DEFAULT_PATH::getContent(); });
    }
};

// if default path is empty, only provide load with getContent
template<typename T, typename PARSER, typename DEFAULT_PATH>
struct Deserializable<T, PARSER, DEFAULT_PATH, true>
        : detail::DeserializableWithGetContent<T, PARSER, DEFAULT_PATH> {};


///////////////////////////////////////////////////////////////////////////////
// xml helper
template<typename T, typename CONFIG_CONTENT = decltype(""_path)>
constexpr auto XMLLoader(CONFIG_CONTENT = {}) {
    return Deserializable<T, TinyXML2Parser, CONFIG_CONTENT>{};
}

template<typename T>
Result loadXMLtoObj(T& obj, std::string_view path) {
    return Deserializable<T, TinyXML2Parser>::load(obj, [&path] {
        return getFileContent(path.data());
    });
}

// json helper
template<typename T, typename CONFIG_CONTENT = decltype(""_path)>
constexpr auto JsonLoader(CONFIG_CONTENT = {}) {
    return Deserializable<T, JsonCppParser, CONFIG_CONTENT>{};
}

template<typename T>
Result loadJsontoObj(T& obj, std::string_view path) {
    return Deserializable<T, JsonCppParser>::load(obj, [&path] {
        return getFileContent(path.data());
    });
}

CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_DESERIALIZABLE_H
