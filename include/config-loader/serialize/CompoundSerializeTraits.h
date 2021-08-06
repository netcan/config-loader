//
// Created by netcan on 2021/08/06.
//

#ifndef CONFIG_LOADER_COMPOUNDSERIALIZETRAITS_H
#define CONFIG_LOADER_COMPOUNDSERIALIZETRAITS_H
#include <config-loader/ConfigLoaderNS.h>
#include <config-loader/serialize/SerializeTraitsDecl.h>
#include <config-loader/utils/CommonTraits.h>
#include <config-loader/core/ReflectedTraits.h>
CONFIG_LOADER_NS_BEGIN
namespace detail {
inline std::string indent(size_t depth) {
    constexpr size_t indentWidth = 2;
    return std::string(indentWidth * depth, ' ');
}
}

template<typename T>
struct CompoundSerializeTraits<T,
        std::enable_if_t<IsReflected_v<T>>> {
    static void dump(std::ostream& out, const T& obj, size_t depth = 0) {
        out << "{";
        forEachField(obj, [&out, depth](auto&& fieldInfo) {
            decltype(auto) fieldName = fieldInfo.name();
            decltype(auto) value = fieldInfo.value();
            out << "\n" << detail::indent(depth + 1) << "." << fieldName;
            CompoundSerializeTraits<std::remove_reference_t<decltype(value)>>
                ::dump(out, value, depth + 1);
            out << ",";
        });
        out << "\n" << detail::indent(depth) << "}";
    }
};

template<typename T>
struct CompoundSerializeTraits<T,
        std::enable_if_t<PrimitiveSerializeTraits<T>::isSupport>> {
    static void dump(std::ostream& out, const T& obj, size_t depth = 0) {
        out << "{";
        PrimitiveSerializeTraits<T>::dump(out, obj);
        out << "}";
    }
};
CONFIG_LOADER_NS_END
#endif //CONFIG_LOADER_COMPOUNDSERIALIZETRAITS_H
