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
        PASTE(REPEAT_, GET_ARG_COUNT(__VA_ARGS__)) (FIELD_EACH, 0, __VA_ARGS__) \
    }                                                                           \

#endif //CONFIG_LOADER_DEFINESCHEMA_H
