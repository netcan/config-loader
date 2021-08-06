//
// Created by netcan on 2021/6/21.
//

#ifndef CONFIG_LOADER_DEFINESCHEMA_H
#define CONFIG_LOADER_DEFINESCHEMA_H
#include <type_traits>
#include <utility>
#include <cstddef>
#include <config-loader/utils/RepeatMacro.h>

#define FIELD_EACH(i, arg)                    \
    PAIR(arg);                                \
    template <typename T>                     \
    struct FIELD<T, i> {                      \
        T& obj;                               \
        FIELD(T& obj): obj(obj) {}            \
        auto value() -> decltype(auto) {      \
            return (obj.STRIP(arg));          \
        }                                     \
        static constexpr const char* name() { \
            return STRING(STRIP(arg));        \
        }                                     \
    };                                        \

#define DEFINE_SCHEMA(st, ...)                                                  \
    struct st {                                                                 \
        template <typename, size_t> struct FIELD;                               \
        static constexpr size_t _field_count_ = GET_ARG_COUNT(__VA_ARGS__);     \
        static constexpr const char* _schema_name_ = #st;                       \
        PASTE(REPEAT_, GET_ARG_COUNT(__VA_ARGS__)) (FIELD_EACH, 0, __VA_ARGS__) \
    }                                                                           \

#define ALIAS_COMPOUND_TYPE(_alias, _compoundType)           \
    struct _alias: PARE _compoundType {                      \
        static constexpr const char* _schema_name_ = #_alias; \
        using self = PARE _compoundType;                     \
        using self::self;                                    \
    };                                                       \
    CONFIG_LOADER_NS_BEGIN                                   \
    template<>                                               \
    struct CompoundDeserializeTraits<_alias>:                \
        CompoundDeserializeTraits<_alias::self>{ };          \
    template<>                                               \
    struct CompoundSerializeTraits<_alias>:                  \
        CompoundSerializeTraits<_alias::self>{ };            \
    CONFIG_LOADER_NS_END                                     \

#endif //CONFIG_LOADER_DEFINESCHEMA_H
