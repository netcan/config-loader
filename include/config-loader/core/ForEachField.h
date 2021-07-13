//
// Created by netcan on 2021/06/28.
//

#ifndef CONFIG_LOADER_FOREACHFIELD_H
#define CONFIG_LOADER_FOREACHFIELD_H
#include <config-loader/Result.h>

CONFIG_LOADER_NS_BEGIN

namespace detail {
    template<typename T, typename F, size_t... Is>
    constexpr Result forEachField(T &&obj, F &&f, std::index_sequence<Is...>) {
        using TDECAY = std::decay_t<T>;

        Result res = Result::SUCCESS;
        (void)( ( (res = f(typename TDECAY::template FIELD<T, Is>(std::forward<T>(obj)))) == Result::SUCCESS) && ...);
        return res;
    }
}

template<typename T, typename F>
constexpr Result forEachField(T&& obj, F&& f) {
    return detail::forEachField(std::forward<T>(obj),
                                std::forward<F>(f),
                                std::make_index_sequence<std::decay_t<T>::_field_count_>{});
}

CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_FOREACHFIELD_H
