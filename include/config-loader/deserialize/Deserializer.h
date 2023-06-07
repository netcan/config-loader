//
// Created by netcan on 2021/07/07.
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

std::string getFileContent(const char* path);

namespace detail {
template<concepts::Parser P>
struct Load2Obj {
    template<typename T, std::invocable GET_CONTENT>
    Result operator()(T& obj, GET_CONTENT&& loader) const {
        std::string content(loader());
        if (content.empty()) { return Result::ERR_EMPTY_CONTENT; }

        P parser;
        CFL_EXPECT_SUCC(parser.parse(content.data()));

        auto rootElem = parser.toRootElemType();
        if (! rootElem.isValid()) { return Result::ERR_MISSING_FIELD; }
        return CompoundDeserializeTraits<T>::deserialize(obj, rootElem);
    }

    template<typename T>
    Result operator()(T& obj, std::string_view path) const {
        return (*this)(obj, [&path] {
            return getFileContent(path.data());
        });
    }
};

template<>
struct Load2Obj<UnsupportedParser> {
    template<typename T, typename LOADER>
    Result operator()(T&, LOADER&&) const {
        return Result::ERR_UNSUPPORTED_PARSER;
    }
};

template<concepts::Parser P>
inline constexpr Load2Obj<P> load2Obj;
}

///////////////////////////////////////////////////////////////////////////////
// xml helper
template<typename T, typename Content>
Result loadXML2Obj(T& obj, Content content) {
    return detail::load2Obj<TinyXML2Parser>(obj, content);
}

// json helper
template<typename T, typename Content>
Result loadJSON2Obj(T& obj, Content content) {
    return detail::load2Obj<JsonCppParser>(obj, content);
}

// yaml helper
template<typename T, typename Content>
Result loadYAML2Obj(T& obj, Content content) {
    return detail::load2Obj<YamlCppParser>(obj, content);
}

CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_DESERIALIZER_H
