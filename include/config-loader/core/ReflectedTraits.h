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
