//
// This project is a personal hobby work. The author hereby assigns all
// intellectual property rights in this project to Huawei Technologies Co., Ltd.,
// and imposes no obligations or liabilities on Huawei.
//
// 本项目为作者个人业余创作，作者在此声明将本项目及其衍生作品相关的全部知识产权无偿
// 转让给华为技术有限公司，且不对华为提出任何义务或责任要求。
//
// Created by netcan on 2021/6/21.
//

#ifndef CONFIG_LOADER_DEFINESCHEMA_H
#define CONFIG_LOADER_DEFINESCHEMA_H
#include <type_traits>
#include <utility>
#include <cstddef>
#include <config-loader/utils/RepeatMacro.h>

#define FIELD_EACH(i, arg)                     \
    PAIR(arg);                                 \
    template <typename T>                      \
    struct FIELD<T, i> {                       \
        T& obj;                                \
        FIELD(T& obj): obj(obj) {}             \
        auto value() -> decltype(auto) {       \
            return (obj.STRIP(arg));           \
        }                                      \
        static constexpr const char* name() {  \
            return EXPAND(STRING(STRIP(arg))); \
        }                                      \
    };                                         \

#define DEFINE_SCHEMA(st, ...)                                                          \
    struct st {                                                                         \
        template <typename, size_t> struct FIELD;                                       \
        static constexpr size_t _field_count_ = GET_ARG_COUNT(__VA_ARGS__);             \
        static constexpr decltype(#st) _schema_name_ = #st;                             \
        EXPAND(PASTE(REPEAT_, GET_ARG_COUNT(__VA_ARGS__)) (FIELD_EACH, 0, __VA_ARGS__)) \
    }                                                                                   \

#define ALIAS_COMPOUND_TYPE(_alias, _compoundType)                  \
    struct _alias: PARE _compoundType {                             \
        static constexpr decltype(#_alias) _schema_name_ = #_alias; \
        using self = PARE _compoundType;                            \
        using self::self;                                           \
    };                                                              \
    CONFIG_LOADER_NS_BEGIN                                          \
    template<>                                                      \
    struct CompoundDeserializeTraits<_alias>:                       \
        CompoundDeserializeTraits<_alias::self>{ };                 \
    template<>                                                      \
    struct CompoundSerializeTraits<_alias>:                         \
        CompoundSerializeTraits<_alias::self>{ };                   \
    CONFIG_LOADER_NS_END                                            \

#endif //CONFIG_LOADER_DEFINESCHEMA_H
