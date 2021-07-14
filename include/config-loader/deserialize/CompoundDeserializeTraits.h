//
// Created by netcan on 2021/07/06.
//

#ifndef CONFIG_LOADER_COMPOUNDDESERIALIZETRAITS_H
#define CONFIG_LOADER_COMPOUNDDESERIALIZETRAITS_H
#include <config-loader/deserialize/DeserializeTraitsDecl.h>
#include <config-loader/core/ReflectedTraits.h>
#include <config-loader/core/ForEachField.h>
#include <config-loader/utils/Log.h>
#include <config-loader/Result.h>
#include <list>
#include <deque>
#include <map>
#include <vector>
#include <optional>
#include <variant>
#include <unordered_map>
#include <string_view>

CONFIG_LOADER_NS_BEGIN

namespace detail {
template<typename T>
struct CompoundDeserializeTraits<T
        , std::enable_if_t<IsReflected_v<T>>> {
    template<typename ELEM_TYPE>
    static Result deserialize(T& obj, ELEM_TYPE node) {
        if (! node.isValid()) { return Result::ERR_MISSING_FIELD; }
        return CONFIG_LOADER_NS::forEachField(obj, [&node](auto&& fieldInfo) {
            decltype(auto) fieldName = fieldInfo.name();
            decltype(auto) value = fieldInfo.value();
            auto res = CompoundDeserializeTraits<std::remove_reference_t<decltype(value)>>
                            ::deserialize(value, node.toChildElem(fieldName));
            if (res != Result::SUCCESS) { LOGE("error handle field: %s", fieldName); }
            return res;
        });
    }
};

template<typename T>
struct CompoundDeserializeTraits<T
        , std::enable_if_t<PrimitiveDeserializeTraits<T>::isSupport>> {
    template<typename ELEM_TYPE>
    static Result deserialize(T& obj, ELEM_TYPE node) {
        if (! node.isValid()) { return Result::ERR_MISSING_FIELD; }
        return PrimitiveDeserializeTraits<T>::deserialize(obj, node.getValueText());
    }
};

////////////////////////////////////////////////////////////////////////////////
template<typename SEQ> // for container like list/vector/deque but not string, code reuse
struct SeqContainerDeserialize {
    template<typename ELEM_TYPE>
    static Result deserialize(SEQ& container, ELEM_TYPE node) {
        if (! node.isValid()) { return Result::SUCCESS; }
        using value_type = typename SEQ::value_type;
        return node.forEachElement([&container](auto&& item) {
            value_type value;
            CFL_EXPECT_SUCC(CompoundDeserializeTraits<value_type>::deserialize(value, item));
            container.push_back(std::move(value));
            return Result::SUCCESS;
        });
    }
};

template<typename T> // code reuse
struct CompoundDeserializeTraits<std::vector<T>>
        : SeqContainerDeserialize<std::vector<T>> { };

template<typename T> // code reuse
struct CompoundDeserializeTraits<std::list<T>>
        : SeqContainerDeserialize<std::list<T>> { };

template<typename T> // code reuse
struct CompoundDeserializeTraits<std::deque<T>>
        : SeqContainerDeserialize<std::deque<T>> { };

////////////////////////////////////////////////////////////////////////////////
template<typename KV> // for kv container like map/unordered_map, code reuse
struct KVContainerDeserialize {
    template<typename ELEM_TYPE>
    static Result deserialize(KV& container, ELEM_TYPE node) {
        if (! node.isValid()) { return Result::SUCCESS; }
        using Key = typename KV::key_type;
        using Value = typename KV::mapped_type;

        return node.forEachElement([&container](auto&& item) {
            Key key; // Key is simply from XML Key Name
            auto keyName = item.getKeyName();
            if (keyName == nullptr) { return Result::ERR_EXTRACTING_FIELD; }
            CFL_EXPECT_SUCC(PrimitiveDeserializeTraits<Key>::deserialize(key, keyName));

            Value value; // Value may be complex data struct
            CFL_EXPECT_SUCC(CompoundDeserializeTraits<Value>::deserialize(value, item));

            if (auto [_, inserted] = container.emplace(std::move(key), std::move(value)); !inserted) {
                LOGI("inserted field %s fail, may contain duplicate key", keyName);
            }
            return Result::SUCCESS;
        });
    }
};

template<typename K, typename V>
struct CompoundDeserializeTraits<std::map<K, V>>
        : KVContainerDeserialize<std::map<K, V>> {};

template<typename K, typename V>
struct CompoundDeserializeTraits<std::unordered_map<K, V>>
        : KVContainerDeserialize<std::unordered_map<K, V>> {};

////////////////////////////////////////////////////////////////////////////////
template<typename T> // for optional type
struct CompoundDeserializeTraits<std::optional<T>> {
    template<typename ELEM_TYPE>
    static Result deserialize(std::optional<T>& obj, ELEM_TYPE node) {
        if (! node.isValid()) {
            obj.reset();
            return Result::SUCCESS;
        }
        T value;
        CFL_EXPECT_SUCC(CompoundDeserializeTraits<T>::deserialize(value, node));
        obj = std::move(value);
        return Result::SUCCESS;
    }
};

////////////////////////////////////////////////////////////////////////////////
template<typename ...Ts> // for sum type(variant)
struct CompoundDeserializeTraits<std::variant<Ts...>> {
    template<typename ELEM_TYPE>
    static Result deserialize(std::variant<Ts...>& obj, ELEM_TYPE node) {
        auto buildVariant = [&obj, &node](auto&& value) {
            using type = std::remove_reference_t<decltype(value)>;
            auto  res  = CompoundDeserializeTraits<type>::deserialize(value, node);
            if (res == Result::SUCCESS) { obj.template emplace<type>(std::move(value)); }
            return res;
        };
        bool success {false};
        (void) ( ( success = (buildVariant(Ts{}) == Result::SUCCESS)) || ...);
        return success ? Result::SUCCESS : Result::ERR_TYPE;
    }
};

}

CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_COMPOUNDDESERIALIZETRAITS_H
