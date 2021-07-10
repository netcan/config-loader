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

CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_DESERIALIZETRAITSDECL_H
