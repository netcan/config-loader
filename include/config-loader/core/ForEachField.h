//
// This project is a personal hobby work. The author hereby assigns all
// intellectual property rights in this project to Huawei Technologies Co., Ltd.,
// and imposes no obligations or liabilities on Huawei.
//
// 本项目为作者个人业余创作，作者在此声明将本项目及其衍生作品相关的全部知识产权无偿
// 转让给华为技术有限公司，且不对华为提出任何义务或责任要求。
//
// Created by netcan on 2021/06/28.
//

#ifndef CONFIG_LOADER_FOREACHFIELD_H
#define CONFIG_LOADER_FOREACHFIELD_H
#include <config-loader/Result.h>
#include <cstddef>
#include <type_traits>
#include <utility>

CONFIG_LOADER_NS_BEGIN

namespace detail {
// for check if `f' has Result value or not(void)
struct DummyFieldInfo {
    int& value();
    const char* name();
};

template<typename T, typename F, size_t... Is>
constexpr auto forEachField(T &&obj, F &&f, std::index_sequence<Is...>) {
    using TDECAY = std::decay_t<T>;

    if constexpr (std::is_same_v<decltype(f(std::declval<DummyFieldInfo>())), Result>) {
        Result res{Result::SUCCESS};
        (void) ( ( (res = f(typename TDECAY::template FIELD<T, Is>
                                    (std::forward<T>(obj)))) == Result::SUCCESS) && ... );
        return res;
    } else {
        (f(typename TDECAY::template FIELD<T, Is>(std::forward<T>(obj))), ...);
    }
}
}

template<typename T, typename F>
constexpr auto forEachField(T&& obj, F&& f) {
    return detail::forEachField(std::forward<T>(obj),
                                std::forward<F>(f),
                                std::make_index_sequence<std::decay_t<T>::_field_count_>{});
}

CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_FOREACHFIELD_H
