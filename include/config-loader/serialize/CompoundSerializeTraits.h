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
            CompoundSerializeTraits<std::decay_t<decltype(value)>>
                ::dump(out, value, depth + 1);
            out << ",";
        });
        out << "\n" << detail::indent(depth) << "}";
    }
};

template<typename T>
struct CompoundSerializeTraits<T,
        std::enable_if_t<PrimitiveSerializeTraits<T>::isSupport>> {
    static void dump(std::ostream& out, const T& obj, size_t = 0) {
        out << "{";
        PrimitiveSerializeTraits<T>::dump(out, obj);
        out << "}";
    }
};

////////////////////////////////////////////////////////////////////////////////
template<typename SEQ> // for container like list/vector/deque but not string, code reuse
struct SeqContainerSerialize {
    static void dump(std::ostream& out, const SEQ& container, size_t depth = 0) {
        out << "{";
        for (auto&& v: container) {
            CompoundSerializeTraits<std::decay_t<decltype(v)>>::dump(out, v, depth + 1);
            out << ", ";
        }
        out << "\n" << detail::indent(depth) << "}";
    }
};

template<typename T> // code reuse
struct CompoundSerializeTraits<std::vector<T>>
        : SeqContainerSerialize<std::vector<T>> { };

template<typename T> // code reuse
struct CompoundSerializeTraits<std::list<T>>
        : SeqContainerSerialize<std::list<T>> { };

template<typename T> // code reuse
struct CompoundSerializeTraits<std::deque<T>>
        : SeqContainerSerialize<std::deque<T>> { };

////////////////////////////////////////////////////////////////////////////////
template<typename KV> // for kv container like map/unordered_map, code reuse
struct KVContainerSerialize {
    static void dump(std::ostream& out, const KV& container, size_t depth = 0) {
        out << "{";
        for (auto&& [k, v]: container) {
            out << "{";
            CompoundSerializeTraits<std::decay_t<decltype(k)>>::dump(out, k, depth + 1);
            out << ", ";
            CompoundSerializeTraits<std::decay_t<decltype(v)>>::dump(out, v, depth + 1);
            out << "},";
        }
        out << "\n" << detail::indent(depth) << "}";
    }
};

template<typename K, typename V>
struct CompoundSerializeTraits<std::map<K, V>>
        : KVContainerSerialize<std::map<K, V>> {};

template<typename K, typename V>
struct CompoundSerializeTraits<std::unordered_map<K, V>>
        : KVContainerSerialize<std::unordered_map<K, V>> {};

////////////////////////////////////////////////////////////////////////////////
template<typename T> // for optional type
struct CompoundSerializeTraits<std::optional<T>> {
    static void dump(std::ostream& out, const std::optional<T>& obj, size_t depth = 0) {
        out << "{";
        if (obj.has_value()) {
            CompoundSerializeTraits<std::decay_t<decltype(*obj)>>::dump(out, *obj, depth + 1);
        } else {
            out << "std::nullopt";
        }
        out << "}";
    }
};

///////////////////////////////////////////////////////////////////////////////
template<typename T> // for shared_ptr
struct CompoundSerializeTraits<std::shared_ptr<T>> {
    static void dump(std::ostream& out, const std::shared_ptr<T>& obj, size_t depth = 0) {
        if (obj == nullptr) {
            out << "nullptr";
        } else {
            using TDecay = std::decay_t<decltype(*obj)>;
            out << "std::make_shared<" << getSchemaName<TDecay>()
                    << ">(" << getSchemaName<TDecay>();
            CompoundSerializeTraits<TDecay>::dump(out, *obj, depth + 1);
            out << ")";
        }
    }
};

////////////////////////////////////////////////////////////////////////////////
template<typename ...Ts> // for sum type(variant)
struct CompoundSerializeTraits<std::variant<Ts...>> {
    static void dump(std::ostream& out, const std::variant<Ts...>& obj, size_t depth = 0) {
        out << "{" << " std::in_place_index<" << obj.index() << ">, ";
        std::visit([&](auto&& v) {
            CompoundSerializeTraits<std::decay_t<decltype(v)>>::dump(out, v, depth + 1);
        }, obj);
        out << "}";
    }
};

CONFIG_LOADER_NS_END
#endif //CONFIG_LOADER_COMPOUNDSERIALIZETRAITS_H
