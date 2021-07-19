//
// Created by netcan on 2021/07/05.
//

#ifndef CONFIG_LOADER_DESERIALIZABLE_H
#define CONFIG_LOADER_DESERIALIZABLE_H
#include <config-loader/Result.h>
#include <config-loader/utils/ConfigPath.h>
#include <config-loader/deserialize/DeserializeTraits.h>
#include <config-loader/concept/Parser.h>
#include <config-loader/parsers/TinyXML2Parser.h>
#include <config-loader/parsers/JsonCppParser.h>
#include <config-loader/parsers/YamlCppParser.h>

CONFIG_LOADER_NS_BEGIN

struct UnsupportedParser;

namespace detail {
template<typename T, concepts::Parser PARSER, typename DEFAULT_PATH>
struct DeserializableWithLoader {
    template<typename GET_CONTENT, // for test
            std::enable_if_t<std::is_invocable_v<GET_CONTENT>>* = nullptr>
    static Result load(T& obj, GET_CONTENT&& loader) {
        std::string content(loader());
        if (content.empty()) { return Result::ERR_EMPTY_CONTENT; }

        PARSER parser;
        CFL_EXPECT_SUCC(parser.parse(content.data()));

        auto firstElem = parser.toRootElemType();
        if (! firstElem.isValid()) { return Result::ERR_MISSING_FIELD; }
        return CompoundDeserializeTraits<T>::deserialize(obj, firstElem);
    }

    static Result load(T& obj, std::string_view path) {
        return load(obj, [&path] {
            return getFileContent(path.data());
        });
    }
};

template<typename T, typename DEFAULT_PATH>
struct DeserializableWithLoader<T, UnsupportedParser, DEFAULT_PATH>  {
    template<typename LOADER>
    static Result load(T&, LOADER&&) {
        return Result::ERR_UNSUPPORTED_PARSER;
    }
};
}

template<typename T, concepts::Parser PARSER, typename DEFAULT_PATH = decltype(""_path), bool = DEFAULT_PATH::isEmpty>
struct Deserializable: private detail::DeserializableWithLoader<T, PARSER, DEFAULT_PATH> {
    // import load with getContent func obj
    using detail::DeserializableWithLoader<T, PARSER, DEFAULT_PATH>::load;

    // load from default path if not empty
    static Result load(T& obj) {
        return load(obj, DEFAULT_PATH::value);
    }
};

// if default path is empty, only provide load with getContent
template<typename T, concepts::Parser PARSER, typename DEFAULT_PATH>
struct Deserializable<T, PARSER, DEFAULT_PATH, true>
        : detail::DeserializableWithLoader<T, PARSER, DEFAULT_PATH> {};


///////////////////////////////////////////////////////////////////////////////
// xml helper
template<typename T, typename CONFIG_CONTENT = decltype(""_path)>
constexpr auto XMLLoader(CONFIG_CONTENT = {}) {
    return Deserializable<T, TinyXML2Parser, CONFIG_CONTENT>{};
}

template<typename T>
Result loadXML2Obj(T& obj, std::string_view path) {
    return Deserializable<T, TinyXML2Parser>::load(obj, path);
}

// json helper
template<typename T, typename CONFIG_CONTENT = decltype(""_path)>
constexpr auto JsonLoader(CONFIG_CONTENT = {}) {
    return Deserializable<T, JsonCppParser, CONFIG_CONTENT>{};
}

template<typename T>
Result loadJSON2Obj(T& obj, std::string_view path) {
    return Deserializable<T, JsonCppParser>::load(obj, path);
}

// yaml helper
template<typename T, typename CONFIG_CONTENT = decltype(""_path)>
constexpr auto YamlLoader(CONFIG_CONTENT = {}) {
    return Deserializable<T, YamlCppParser, CONFIG_CONTENT>{};
}

template<typename T>
Result loadYAML2Obj(T& obj, std::string_view path) {
    return Deserializable<T, YamlCppParser>::load(obj, path);
}

CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_DESERIALIZABLE_H
