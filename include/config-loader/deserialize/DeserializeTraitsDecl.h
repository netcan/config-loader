//
// Created by netcan on 2021/07/06.
//

#ifndef CONFIG_LOADER_DESERIALIZETRAITSDECL_H
#define CONFIG_LOADER_DESERIALIZETRAITSDECL_H
#include <config-loader/ConfigLoaderNS.h>

CONFIG_LOADER_NS_BEGIN

namespace detail {
template<bool support>
struct IsSupport {
    static constexpr bool isSupport = support;
};
}

template<typename FORMAT>
struct DeserializeTraits;

template<typename FORMAT, typename = void>
struct CommonDeserializeTraits: detail::IsSupport<false> { };

CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_DESERIALIZETRAITSDECL_H
