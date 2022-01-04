//
// Created by netcan on 2021/07/20.
//

#ifndef CONFIG_LOADER_BASIC_H
#define CONFIG_LOADER_BASIC_H
#include <config-loader/deserialize/DeserializeTraitsDecl.h>
#include <concepts>
#include <string_view>

CONFIG_LOADER_NS_BEGIN
namespace concepts {

template<typename T>
concept Reflected = requires(T obj) {
    { obj._field_count_ } -> std::convertible_to<size_t>;
#ifndef __clang__
    requires (obj._field_count_ == 0) ||
             (obj._field_count_ > 0 && requires {
                typename std::decay_t<T>::template FIELD<T, 0>;
             });
#endif
};

template<typename T>
concept Primitive = PrimitiveDeserializeTraits<T>::isSupport;

template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template<typename T>
concept LValRef = std::is_lvalue_reference_v<T>;

template<typename INFO>
concept FieldInfo = requires(INFO field) {
    { field.name() } -> std::convertible_to<std::string_view>;
    { field.value() } -> LValRef;
};
}
CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_BASIC_H
