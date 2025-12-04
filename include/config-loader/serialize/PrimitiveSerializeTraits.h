//
// This project is a personal hobby work. The author hereby assigns all
// intellectual property rights in this project to Huawei Technologies Co., Ltd.,
// and imposes no obligations or liabilities on Huawei.
//
// 本项目为作者个人业余创作，作者在此声明将本项目及其衍生作品相关的全部知识产权无偿
// 转让给华为技术有限公司，且不对华为提出任何义务或责任要求。
//
// Created by netcan on 2021/08/06.
//

#ifndef CONFIG_LOADER_PRIMITIVESERIALIZETRAITS_H
#define CONFIG_LOADER_PRIMITIVESERIALIZETRAITS_H
#include <config-loader/ConfigLoaderNS.h>
#include <config-loader/serialize/SerializeTraitsDecl.h>
#include <config-loader/utils/CommonTraits.h>
#include <string>
#include <type_traits>
CONFIG_LOADER_NS_BEGIN

template<typename Number>
struct PrimitiveSerializeTraits<Number, std::enable_if_t<std::is_arithmetic_v<Number>>>
        : detail::IsSupport<true> {
    static void dump(std::ostream& out, Number number) {
        // do not treat int8_t/uint8_t as char type
        if constexpr(std::is_same_v<Number, int8_t> || std::is_same_v<Number, uint8_t>) {
            out << +number;
        } else {
            out << number;
        }
    }
};

template<>
struct PrimitiveSerializeTraits<std::string>
        : detail::IsSupport<true> {
    static void dump(std::ostream& out, const std::string& str) {
        out << "\"" << str << "\"";
    }
};

CONFIG_LOADER_NS_END
#endif //CONFIG_LOADER_PRIMITIVESERIALIZETRAITS_H
