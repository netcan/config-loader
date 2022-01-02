//
// Created by netcan on 2021/07/05.
//

#ifndef CONFIG_LOADER_DESERIALIZER_H
#define CONFIG_LOADER_DESERIALIZER_H
#include <config-loader/Result.h>
#include <config-loader/deserialize/DeserializeTraits.h>
#include <config-loader/parsers/TinyXML2Parser.h>
#include <config-loader/parsers/JsonCppParser.h>
#include <config-loader/parsers/YamlCppParser.h>
#include <concepts>

CONFIG_LOADER_NS_BEGIN

struct UnsupportedParser;

std::string getFileContent(const char* path);

namespace detail {
template<typename T, typename PARSER>
struct Deserializer {
    template<std::invocable GET_CONTENT>
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

template<typename T>
struct Deserializer<T, UnsupportedParser>  {
    template<typename LOADER>
    static Result load(T&, LOADER&&) {
        return Result::ERR_UNSUPPORTED_PARSER;
    }
};
}

///////////////////////////////////////////////////////////////////////////////
// xml helper
template<typename T, typename Content>
Result loadXML2Obj(T& obj, Content content) {
    return detail::Deserializer<T, TinyXML2Parser>::load(obj, content);
}

// json helper
template<typename T, typename Content>
Result loadJSON2Obj(T& obj, Content content) {
    return detail::Deserializer<T, JsonCppParser>::load(obj, content);
}

// yaml helper
template<typename T, typename Content>
Result loadYAML2Obj(T& obj, Content content) {
    return detail::Deserializer<T, YamlCppParser>::load(obj, content);
}

CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_DESERIALIZER_H
