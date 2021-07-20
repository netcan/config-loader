//
// Created by netcan on 2021/07/06.
//

#ifndef CONFIG_LOADER_DESERIALIZETRAITSDECL_H
#define CONFIG_LOADER_DESERIALIZETRAITSDECL_H
#include <config-loader/ConfigLoaderNS.h>
#include <config-loader/utils/Assertion.h>
#include <config-loader/utils/Log.h>
#include <config-loader/utils/CommonTraits.h>

CONFIG_LOADER_NS_BEGIN
template<typename T>
struct PrimitiveDeserializeTraits: detail::IsSupport<false> {};

template<typename T>
struct CompoundDeserializeTraits;

CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_DESERIALIZETRAITSDECL_H
