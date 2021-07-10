//
// Created by netcan on 2021/07/06.
//

#ifndef CONFIG_LOADER_DESERIALIZETRAITSDECL_H
#define CONFIG_LOADER_DESERIALIZETRAITSDECL_H
#include <config-loader/ConfigLoaderNS.h>
#include <config-loader/utils/Assertion.h>
#include <config-loader/utils/Log.h>

CONFIG_LOADER_NS_BEGIN

namespace detail {
template<bool support>
struct IsSupport {
    static constexpr bool isSupport = support;
};

template<typename T, typename = void>
struct PrimitiveDeserializeTraits: IsSupport<false> {};

template<typename T, typename = void>
struct CompoundDeserializeTraits;
}

template<typename PARSER>
struct DeserializeTraits {
    template<typename T>
    static Result load(T& obj, std::string_view content) {
        if (content.empty()) { return Result::ERR_EMPTY_CONTENT; }

        PARSER parser;
        CFL_EXPECT_SUCC(parser.parse(content.data()));

        auto firstElem = parser.toRootElemType();
        if (! firstElem.isValid()) { return Result::ERR_MISSING_FIELD; }
        return detail::CompoundDeserializeTraits<T>::deserialize(obj, firstElem);
    }
};

CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_DESERIALIZETRAITSDECL_H
