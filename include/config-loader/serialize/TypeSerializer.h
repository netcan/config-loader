//
// Created by netcan on 2021/08/09.
//

#ifndef CONFIG_LOADER_TYPESERIALIZER_H
#define CONFIG_LOADER_TYPESERIALIZER_H
#include <config-loader/ConfigLoaderNS.h>
#include <config-loader/utils/ConstexprStringUtils.h>
#include <cstdint>
#include <vector>
#include <variant>
#include <array>

CONFIG_LOADER_NS_BEGIN

template<typename T> struct TypeSerializer;

template<> struct TypeSerializer<int8_t>
{ static constexpr auto&& name = "int8_t"; };
template<> struct TypeSerializer<uint8_t>
{ static constexpr auto&& name = "uint8_t"; };

template<> struct TypeSerializer<int16_t>
{ static constexpr auto&& name = "int16_t"; };
template<> struct TypeSerializer<uint16_t>
{ static constexpr auto&& name = "uint16_t"; };

template<> struct TypeSerializer<int32_t>
{ static constexpr auto&& name = "int32_t"; };
template<> struct TypeSerializer<uint32_t>
{ static constexpr auto&& name = "uint32_t"; };

template<> struct TypeSerializer<int64_t>
{ static constexpr auto&& name = "int64_t"; };
template<> struct TypeSerializer<uint64_t>
{ static constexpr auto&& name = "uint64_t"; };

template<> struct TypeSerializer<float>
{ static constexpr auto&& name = "float"; };
template<> struct TypeSerializer<double>
{ static constexpr auto&& name = "double"; };

template<typename T> struct TypeSerializer<std::vector<T>> {
     static constexpr auto name = concat("std::vector<", TypeSerializer<T>::name, ">");
};

// helper
template<typename T, typename = void>
constexpr const char* TypeSerializer_v = TypeSerializer<T>::name;

template<typename T>
constexpr const char* TypeSerializer_v<T, std::void_t<decltype(TypeSerializer<T>::name.data())>>
        = TypeSerializer<T>::name.data();

CONFIG_LOADER_NS_END
#endif // CONFIG_LOADER_TYPESERIALIZER_H
