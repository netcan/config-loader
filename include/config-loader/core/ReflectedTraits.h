//
// Created by netcan on 2021/06/28.
//

#ifndef CONFIG_LOADER_REFLECTEDTRAITS_H
#define CONFIG_LOADER_REFLECTEDTRAITS_H

#include <config-loader/ConfigLoaderNS.h>
#include <type_traits>

CONFIG_LOADER_NS_BEGIN

template<typename T, typename = void>
inline constexpr bool IsReflected_v = false;

template<typename T>
inline constexpr bool IsReflected_v
        <T, std::void_t<decltype(&T::_field_count_)>>
        = true;

CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_REFLECTEDTRAITS_H
