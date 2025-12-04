//
// This project is a personal hobby work. The author hereby assigns all
// intellectual property rights in this project to Huawei Technologies Co., Ltd.,
// and imposes no obligations or liabilities on Huawei.
//
// 本项目为作者个人业余创作，作者在此声明将本项目及其衍生作品相关的全部知识产权无偿
// 转让给华为技术有限公司，且不对华为提出任何义务或责任要求。
//
// Created by netcan on 2021/08/09.
//

#ifndef CONFIG_LOADER_TYPESERIALIZER_H
#define CONFIG_LOADER_TYPESERIALIZER_H
#include <config-loader/ConfigLoaderNS.h>
#include <config-loader/utils/ConstexprStringUtils.h>
#include <config-loader/utils/RepeatMacro.h>
#include <cstdint>
#include <optional>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <memory>
#include <unordered_map>
#include <variant>
#include <array>

CONFIG_LOADER_NS_BEGIN
template<typename T, typename = void> struct TypeSerializer;

#define TYPE_SERIALIZER(_type, _typeName)                 \
    struct TypeSerializer<PARE _type>                     \
    { static constexpr decltype(_typeName) name = _typeName; }

template<typename T>
struct TypeSerializer<T, std::void_t<decltype(&T::_schema_name_)>> {
    static constexpr decltype(T::_schema_name_) name = T::_schema_name_;
};

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
template<> TYPE_SERIALIZER((std::string), "string");

template<typename T>
TYPE_SERIALIZER((std::vector<T>),
                    concat("vector<", TypeSerializer<T>::name, ">"));
template<typename T>
TYPE_SERIALIZER((std::list<T>),
                concat("list<", TypeSerializer<T>::name, ">"));

template<typename K, typename V>
TYPE_SERIALIZER((std::map<K, V>),
                concat("map<", TypeSerializer<K>::name,
                       ", ", TypeSerializer<V>::name, ">"));
template<typename K, typename V>
TYPE_SERIALIZER((std::unordered_map<K, V>),
                concat("unordered_map<", TypeSerializer<K>::name,
                       ", ", TypeSerializer<V>::name, ">"));

template<typename T>
TYPE_SERIALIZER((std::optional<T>),
                concat("optional<", TypeSerializer<T>::name, ">"));

template<typename... Ts>
TYPE_SERIALIZER((std::variant<Ts...>),
                concat("variant<", join(TypeSerializer<Ts>::name...)(", "), ">"));

template<typename T>
TYPE_SERIALIZER((std::shared_ptr<T>),
                concat("shared_ptr<", TypeSerializer<T>::name, ">"));

template<typename T>
TYPE_SERIALIZER((std::unique_ptr<T>),
                concat("unique_ptr<", TypeSerializer<T>::name, ">"));

#undef TYPE_SERIALIZER
// helper
template<typename T, typename = void>
inline constexpr const char* TypeSerializer_v = TypeSerializer<T>::name;

template<typename T>
inline constexpr const char* TypeSerializer_v<T, std::void_t<decltype(TypeSerializer<T>::name.data())>> =
        TypeSerializer<T>::name.data();

CONFIG_LOADER_NS_END
#endif // CONFIG_LOADER_TYPESERIALIZER_H
