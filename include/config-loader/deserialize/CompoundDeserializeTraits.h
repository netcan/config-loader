//
// Created by netcan on 2021/07/06.
//

#ifndef CONFIG_LOADER_COMPOUNDDESERIALIZETRAITS_H
#define CONFIG_LOADER_COMPOUNDDESERIALIZETRAITS_H
#include <config-loader/deserialize/DeserializeTraitsDecl.h>
#include <config-loader/core/ReflectedTraits.h>
#include <config-loader/core/ForEachField.h>
#include <config-loader/concept/Parser.h>
#include <config-loader/concept/Basic.h>
#include <config-loader/utils/Log.h>
#include <config-loader/Result.h>
#include <list>
#include <map>
#include <vector>
#include <memory>
#include <optional>
#include <variant>
#include <unordered_map>
#include <string_view>

CONFIG_LOADER_NS_BEGIN

template<concepts::Reflected T>
struct CompoundDeserializeTraits<T> {
    static Result deserialize(T& obj, concepts::ParserElem auto node) {
        if (! node.isValid()) { return Result::ERR_MISSING_FIELD; }
        return forEachField(obj, [&node](auto&& fieldInfo) {
            decltype(auto) fieldName = fieldInfo.name();
            decltype(auto) value = fieldInfo.value();
            auto res = CompoundDeserializeTraits<std::remove_reference_t<decltype(value)>>
                            ::deserialize(value, node.toChildElem(fieldName));
            if (res != Result::SUCCESS) { LOGE("error handle field: %s", fieldName); }
            return res;
        });
    }
};

template<concepts::Primitive T>
struct CompoundDeserializeTraits<T> {
    static Result deserialize(T& obj, concepts::ParserElem auto node) {
        if (! node.isValid()) { return Result::ERR_MISSING_FIELD; }
        return PrimitiveDeserializeTraits<T>::deserialize(obj, node.getValueText());
    }
};

////////////////////////////////////////////////////////////////////////////////
template<typename SEQ> // for container like list/vector but not string, code reuse
struct SeqContainerDeserialize {
    static Result deserialize(SEQ& container, concepts::ParserElem auto node) {
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

////////////////////////////////////////////////////////////////////////////////
template<typename KV> // for kv container like map/unordered_map, code reuse
struct KVContainerDeserialize {
    static Result deserialize(KV& container, concepts::ParserElem auto node) {
        if (! node.isValid()) { return Result::SUCCESS; }
        using Key = typename KV::key_type;
        using Value = typename KV::mapped_type;

        return node.forEachElement([&container](auto&& item) {
            Key key;
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
    static Result deserialize(std::optional<T>& obj, concepts::ParserElem auto node) {
        if (! node.isValid()) { return Result::SUCCESS; }
        T value;
        CFL_EXPECT_SUCC(CompoundDeserializeTraits<T>::deserialize(value, node));
        obj = std::move(value);
        return Result::SUCCESS;
    }
};

////////////////////////////////////////////////////////////////////////////////
template<typename ...Ts> // for sum type(variant)
struct CompoundDeserializeTraits<std::variant<Ts...>> {
    static Result deserialize(std::variant<Ts...>& obj, concepts::ParserElem auto node) {
        if (! node.isValid()) { return Result::ERR_MISSING_FIELD; }
        auto buildVariant = [&obj, &node]<typename T>(T&& value) {
            auto  res  = CompoundDeserializeTraits<T>::deserialize(value, node);
            if (res == Result::SUCCESS) { obj.template emplace<T>(std::forward<T>(value)); }
            return res;
        };
        bool success {false};
        (void) ( ( success = (buildVariant(Ts{}) == Result::SUCCESS)) || ... );
        return success ? Result::SUCCESS : Result::ERR_TYPE;
    }
};

///////////////////////////////////////////////////////////////////////////////
template<typename SP> // for smart pointer like shared_ptr/unique_ptr, code reuse
struct SmartPointDeserialize {
    static Result deserialize(SP& sp, concepts::ParserElem auto node) {
        if (! node.isValid()) { return Result::SUCCESS; }
        using SPElemType = typename SP::element_type;
        SPElemType value;
        CFL_EXPECT_SUCC(CompoundDeserializeTraits<SPElemType>::deserialize(value, node));
        sp.reset(new SPElemType(std::move(value)));
        return Result::SUCCESS;
    }
};

template<typename T>
struct CompoundDeserializeTraits<std::shared_ptr<T>>
        : SmartPointDeserialize<std::shared_ptr<T>> {};

template<typename T>
struct CompoundDeserializeTraits<std::unique_ptr<T>>
        : SmartPointDeserialize<std::unique_ptr<T>> {};

CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_COMPOUNDDESERIALIZETRAITS_H
