//
// Created by netcan on 2021/07/06.
//

#ifndef CONFIG_LOADER_DESERIALIZETRAITSDECL_H
#define CONFIG_LOADER_DESERIALIZETRAITSDECL_H
#include <config-loader/ConfigLoaderNS.h>
#include <config-loader/utils/Log.h>

CONFIG_LOADER_NS_BEGIN

namespace detail {
template<bool support>
struct IsSupport {
    static constexpr bool isSupport = support;
};
}

template<typename FORMAT>
struct Parser;

template<typename PARSER>
struct DeserializeTraits;

template<typename T, typename = void>
struct TrivialDeserializeTraits: detail::IsSupport<false> {
    static Result deserialize(T&, std::string_view) {
        LOGE("unimplemented");
        return Result::ERE_EXTRACTING_FIELD;
    }
};

CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_DESERIALIZETRAITSDECL_H
