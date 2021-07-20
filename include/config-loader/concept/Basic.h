//
// Created by netcan on 2021/07/20.
//

#ifndef CONFIG_LOADER_BASIC_H
#define CONFIG_LOADER_BASIC_H
#include <concepts>
#include <config-loader/core/ReflectedTraits.h>
#include <config-loader/deserialize/DeserializeTraitsDecl.h>

CONFIG_LOADER_NS_BEGIN
namespace concepts {
template<typename T>
concept Reflected = IsReflected_v<T>;

template<typename T>
concept Primitive = detail::PrimitiveDeserializeTraits<T>::isSupport;

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
