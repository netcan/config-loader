//
// This project is a personal hobby work. The author hereby assigns all
// intellectual property rights in this project to Huawei Technologies Co., Ltd.,
// and imposes no obligations or liabilities on Huawei.
//
// 本项目为作者个人业余创作，作者在此声明将本项目及其衍生作品相关的全部知识产权无偿
// 转让给华为技术有限公司，且不对华为提出任何义务或责任要求。
//
// Created by netcan on 2021/08/10.
//

#ifndef CONFIG_LOADER_CONSTEXPRSTRINGUTILS_H
#define CONFIG_LOADER_CONSTEXPRSTRINGUTILS_H
#include <config-loader/ConfigLoaderNS.h>
#include <cstddef>
#include <type_traits>
#include <array>
CONFIG_LOADER_NS_BEGIN
template<typename T> constexpr auto strLength =
        strLength<std::remove_cv_t<std::remove_reference_t<T>>>;

template<size_t N>
inline constexpr size_t strLength<char[N]> = N - 1;

template<size_t N>
inline constexpr size_t strLength<std::array<char, N>> = N - 1;

template<typename STR>
constexpr auto copy(STR&& src, char* dest) -> decltype(strLength<STR>) {
    size_t i = 0;
    for (; i < strLength<STR>; ++i) {
        dest[i] = src[i];
    }
    return i;
}

namespace detail {
template<size_t N>
struct ConcatStringFold {
    template<typename STR>
    friend decltype(auto) constexpr operator<<(ConcatStringFold&& self, STR&& str) {
        self.idx += copy(std::forward<STR>(str), self.concatedStr.data() + self.idx);
        return std::forward<ConcatStringFold>(self);
    }
    std::array<char, N + 1> concatedStr{};
    size_t idx = 0;
};
}

template<typename... STRs>
constexpr auto concat(STRs&&... strs) {
    constexpr size_t len = (strLength<STRs> + ... + 0);
    return (detail::ConcatStringFold<len>{} << ... << strs).concatedStr; // left fold
}

namespace detail {
template<typename DELIM_TYPE, size_t N>
struct JoinStringFold {
    constexpr JoinStringFold(DELIM_TYPE delimiter): delimiter(delimiter) {}
    template<typename STR>
    friend decltype(auto) constexpr operator<<(JoinStringFold&& self, STR&& str) {
        self.idx += copy(std::forward<STR>(str), self.joinedStr.data() + self.idx);
        if (self.idx + strLength<DELIM_TYPE> < N) {
            self.idx += copy(std::forward<DELIM_TYPE>(self.delimiter), self.joinedStr.data() + self.idx);
        }
        return std::forward<JoinStringFold>(self);
    }
    std::array<char, N + 1> joinedStr{};
    DELIM_TYPE delimiter;
    size_t idx = 0;
};
};

template<typename... STRs>
constexpr auto join(STRs&& ...strs) {
    return [&](auto&& delimiter) {
        using DELIM_TYPE = decltype(delimiter);
        constexpr size_t strNum = sizeof...(STRs);
        constexpr size_t len = (strLength<STRs> + ... + 0) +
                               (strNum >= 1 ? strNum - 1 : 0) * strLength<DELIM_TYPE>;
        return (detail::JoinStringFold<DELIM_TYPE, len>{std::forward<DELIM_TYPE>(delimiter)}
                << ... << strs).joinedStr;
    };
}

CONFIG_LOADER_NS_END
#endif // CONFIG_LOADER_CONSTEXPRSTRINGUTILS_H
