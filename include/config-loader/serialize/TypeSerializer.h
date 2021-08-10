//
// Created by netcan on 2021/08/09.
//

#ifndef CONFIG_LOADER_TYPESERIALIZER_H
#define CONFIG_LOADER_TYPESERIALIZER_H
#include <config-loader/ConfigLoaderNS.h>
#include <config-loader/utils/ConstexprStringUtils.h>
#include <config-loader/utils/RepeatMacro.h>
#include <cstdint>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <unordered_map>
#include <variant>
#include <array>

CONFIG_LOADER_NS_BEGIN
template<typename T> struct TypeSerializer;

#define TYPE_SERIALIZER(_type, _typeName)                 \
    struct TypeSerializer<PARE _type>                     \
    { static constexpr decltype(auto) name = _typeName; }

template<> TYPE_SERIALIZER((int8_t), "int8_t");
template<> TYPE_SERIALIZER((uint8_t), "uint8_t");
template<> TYPE_SERIALIZER((int16_t), "int16_t");
template<> TYPE_SERIALIZER((uint16_t), "uint16_t");
template<> TYPE_SERIALIZER((int32_t), "int32_t");
template<> TYPE_SERIALIZER((uint32_t), "uint32_t");
template<> TYPE_SERIALIZER((int64_t), "int64_t");
template<> TYPE_SERIALIZER((uint64_t), "uint64_t");
template<> TYPE_SERIALIZER((float), "float");
template<> TYPE_SERIALIZER((double), "double");
template<> TYPE_SERIALIZER((std::string), "std::string");

template<typename T>
TYPE_SERIALIZER((std::vector<T>),
                    concat("std::vector<", TypeSerializer<T>::name, ">"));
template<typename T>
TYPE_SERIALIZER((std::list<T>),
                concat("std::list<", TypeSerializer<T>::name, ">"));

template<typename K, typename V>
TYPE_SERIALIZER((std::map<K, V>),
                concat("std::map<", TypeSerializer<K>::name,
                       ", ", TypeSerializer<V>::name, ">"));
template<typename K, typename V>
TYPE_SERIALIZER((std::unordered_map<K, V>),
                concat("std::unordered_map<", TypeSerializer<K>::name,
                       ", ", TypeSerializer<V>::name, ">"));

template<typename T>
TYPE_SERIALIZER((std::optional<T>),
                concat("std::optional<", TypeSerializer<T>::name, ">"));

template<typename... Ts>
TYPE_SERIALIZER((std::variant<Ts...>),
                concat("std::variant<", join(TypeSerializer<Ts>::name...)(", "), ">"));

template<typename T>
TYPE_SERIALIZER((std::shared_ptr<T>),
                concat("std::shared_ptr<", TypeSerializer<T>::name, ">"));

template<typename T>
TYPE_SERIALIZER((std::unique_ptr<T>),
                concat("std::unique_ptr<", TypeSerializer<T>::name, ">"));

#undef TYPE_SERIALIZER
// helper
template<typename T, typename = void>
constexpr const char* TypeSerializer_v = TypeSerializer<T>::name;

template<typename T>
constexpr const char* TypeSerializer_v<T, std::void_t<decltype(TypeSerializer<T>::name.data())>> =
        TypeSerializer<T>::name.data();

CONFIG_LOADER_NS_END
#endif // CONFIG_LOADER_TYPESERIALIZER_H
