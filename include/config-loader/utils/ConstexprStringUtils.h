//
// Created by netcan on 2021/08/10.
//

#ifndef CONFIG_LOADER_CONSTEXPRSTRINGUTILS_H
#define CONFIG_LOADER_CONSTEXPRSTRINGUTILS_H
#include <config-loader/ConfigLoaderNS.h>
CONFIG_LOADER_NS_BEGIN

template<typename T>
constexpr auto strLength = nullptr; // just for compile error, don't select it

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

CONFIG_LOADER_NS_END
#endif // CONFIG_LOADER_CONSTEXPRSTRINGUTILS_H
