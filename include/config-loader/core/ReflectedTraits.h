//
// Created by netcan on 2021/06/28.
//

#ifndef CONFIG_LOADER_REFLECTEDTRAITS_H
#define CONFIG_LOADER_REFLECTEDTRAITS_H

CONFIG_LOADER_NS_BEGIN

template<typename T, typename = void>
constexpr bool IsReflected_v = false;

template<typename T>
constexpr bool IsReflected_v
        <T, std::void_t<decltype(&T::_field_count_)>>
        = true;

template<typename T>
constexpr auto getSchemaName() -> decltype(T::_schema_name_) {
    return T::_schema_name_;
}

CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_REFLECTEDTRAITS_H
