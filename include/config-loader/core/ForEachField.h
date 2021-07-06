//
// Created by netcan on 2021/06/28.
//

#ifndef CONFIG_LOADER_FOREACHFIELD_H
#define CONFIG_LOADER_FOREACHFIELD_H

CONFIG_LOADER_NS_BEGIN

namespace detail {
    template<typename T, typename F, size_t... Is>
    constexpr void forEachField(T &&obj, F &&f, std::index_sequence<Is...>) {
        using TDECAY = std::decay_t<T>;
        (f(typename TDECAY::template FIELD<T, Is>(std::forward<T>(obj)).name(),
           typename TDECAY::template FIELD<T, Is>(std::forward<T>(obj)).value()), ...);
    }
}

template<typename T, typename F>
constexpr void forEachField(T&& obj, F&& f) {
    detail::forEachField(std::forward<T>(obj),
            std::forward<F>(f),
            std::make_index_sequence<std::decay_t<T>::_field_count_>{});
}

CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_FOREACHFIELD_H
