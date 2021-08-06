//
// Created by netcan on 2021/08/06.
//

#ifndef CONFIG_LOADER_SERIALIZETRAITSDECL_H
#define CONFIG_LOADER_SERIALIZETRAITSDECL_H
#include <config-loader/ConfigLoaderNS.h>
CONFIG_LOADER_NS_BEGIN
template<typename T, typename = void>
struct PrimitiveSerializeTraits: detail::IsSupport<false> {};

template<typename T, typename = void>
struct CompoundSerializeTraits;
CONFIG_LOADER_NS_END
#endif //CONFIG_LOADER_SERIALIZETRAITSDECL_H
