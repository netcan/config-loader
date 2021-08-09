//
// Created by netcan on 2021/08/09.
//

#ifndef CONFIG_LOADER_TYPESERIALIZER_H
#define CONFIG_LOADER_TYPESERIALIZER_H
#include <config-loader/ConfigLoaderNS.h>
#include <cstdint>
#include <vector>
#include <variant>
#include <array>

CONFIG_LOADER_NS_BEGIN

template<typename ...>
struct dump;

namespace detail {
template<typename T>
constexpr auto strLength = std::monostate{}; // just for compile error, not select it

template<size_t N>
constexpr size_t strLength<const char[N]> = N;

template<size_t N>
constexpr size_t strLength<std::array<char, N>> = N;

template<size_t N>
struct ConcatFold {
    template<typename STR>
    friend decltype(auto) constexpr operator<<(ConcatFold&& self, STR&& str) {
        for (size_t i = 0; i < strLength<std::remove_reference_t<STR>> - 1; ++i) {
            self.concatedStr[self.idx++] = str[i];
        }
        return std::forward<ConcatFold>(self);
    }

    std::array<char, N> concatedStr{};
    size_t idx = 0;
};

template<typename... STRs>
constexpr auto concat(STRs&&... strs) {
    constexpr size_t len = ((strLength<std::remove_reference_t<STRs>> - 1) + ... + 1);
    return (ConcatFold<len>{} << ... << strs).concatedStr; // left fold
}
}

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
     static constexpr auto name = detail::concat("std::vector<", TypeSerializer<T>::name, ">");
};

// helper
template<typename T, typename = void>
constexpr const char* TypeSerializer_v = TypeSerializer<T>::name;

template<typename T>
constexpr const char* TypeSerializer_v<T, std::void_t<decltype(TypeSerializer<T>::name.data())>>
        = TypeSerializer<T>::name.data();

CONFIG_LOADER_NS_END
#endif // CONFIG_LOADER_TYPESERIALIZER_H
