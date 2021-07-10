//
// Created by netcan on 2021/07/06.
//

#ifndef CONFIG_LOADER_NONTRIVIALDESERIALIZETRAITS_H
#define CONFIG_LOADER_NONTRIVIALDESERIALIZETRAITS_H
#include <config-loader/deserialize/DeserializeTraitsDecl.h>
#include <config-loader/core/ReflectedTraits.h>
#include <config-loader/core/ForEachField.h>
#include <config-loader/utils/Log.h>
#include <config-loader/utils/Assertion.h>
#include <config-loader/Result.h>
#include <list>
#include <deque>
#include <map>
#include <vector>
#include <string_view>

CONFIG_LOADER_NS_BEGIN

namespace detail {
template<typename T, typename = void>
struct NonTrivialDeserializeTraits;
}

template<typename PARSER>
struct DeserializeTraits {
    template<typename T>
    static Result load(T& obj, std::string_view content) {
        if (content.empty()) { return Result::ERR_EMPTY_CONTENT; }

        PARSER parser;
        CFL_EXPECT_SUCC(parser.parse(content.data()));

        auto firstElem = parser.toRootElemType();
        if (! firstElem) { return Result::ERR_MISSING_FIELD; }
        return detail::NonTrivialDeserializeTraits<T>::deserialize(obj, firstElem);
    }
};

////////////////////////////////////////////////////////////////////////////////

namespace detail {
template<typename T>
struct NonTrivialDeserializeTraits<T
        , std::enable_if_t<IsReflected_v<T>>> {
    template<typename ELEM_TYPE>
    static Result deserialize(T& obj, ELEM_TYPE node) {
        return CONFIG_LOADER_NS::forEachField(obj, [&node](const char* fieldName, auto& value) {
            auto res = NonTrivialDeserializeTraits<std::remove_reference_t<decltype(value)>>
                            ::deserialize(value, node.toChildElem(fieldName));
            if (res != Result::SUCCESS) { LOGE("error handle field: %s", fieldName); }
            return res;
        });
    }
};

template<typename T>
struct NonTrivialDeserializeTraits<T
        , std::enable_if_t<TrivialDeserializeTraits<T>::isSupport>> {
    template<typename ELEM_TYPE>
    static Result deserialize(T& obj, ELEM_TYPE node) {
        if (! node) { return Result::ERR_MISSING_FIELD; }
        return TrivialDeserializeTraits<T>::deserialize(obj, node.getValueText());
    }
};

template<typename SEQ> // for container like list/vector/deque but not string, code reuse
struct SeqContainerDeserialize {
    template<typename ELEM_TYPE>
    static Result deserialize(SEQ& container, ELEM_TYPE node) {
        if (! node) { return Result::ERR_MISSING_FIELD; }
        using value_type = typename SEQ::value_type;
        return node.forEachElement([&container](auto&& item) {
            value_type value;
            CFL_EXPECT_SUCC(NonTrivialDeserializeTraits<value_type>::deserialize(value, item));
            container.push_back(std::move(value));
            return Result::SUCCESS;
        });
    }
};

template<typename T> // code reuse
struct NonTrivialDeserializeTraits<std::vector<T>>
        : SeqContainerDeserialize<std::vector<T>> { };

template<typename T> // code reuse
struct NonTrivialDeserializeTraits<std::list<T>>
        : SeqContainerDeserialize<std::list<T>> { };

template<typename T> // code reuse
struct NonTrivialDeserializeTraits<std::deque<T>>
        : SeqContainerDeserialize<std::deque<T>> { };

template<typename KV> // for kv container like map/unordered_map, code reuse
struct KVContainerDeserialize {
    template<typename ELEM_TYPE>
    static Result deserialize(KV& container, ELEM_TYPE node) {
        if (! node) { return Result::ERR_MISSING_FIELD; }
        using Key = typename KV::key_type;
        using Value = typename KV::mapped_type;

        return node.forEachElement([&container](auto&& item) {
            Key key; // Key is simply from XML Key Name
            auto keyName = item.getKeyName();
            if (keyName == nullptr) { return Result::ERR_EXTRACTING_FIELD; }
            CFL_EXPECT_SUCC(TrivialDeserializeTraits<Key>::deserialize(key, keyName));

            Value value; // Value may be complex data struct
            CFL_EXPECT_SUCC(NonTrivialDeserializeTraits<Value>::deserialize(value, item));

            if (auto [_, inserted] = container.emplace(std::move(key), std::move(value)); !inserted) {
                LOGI("inserted field %s fail, may contain duplicate key", keyName);
            }
            return Result::SUCCESS;
        });
    }
};

template<typename K, typename V>
struct NonTrivialDeserializeTraits<std::map<K, V>>
        : KVContainerDeserialize<std::map<K, V>> {};

template<typename K, typename V>
struct NonTrivialDeserializeTraits<std::unordered_map<K, V>>
        : KVContainerDeserialize<std::unordered_map<K, V>> {};


template<typename T>
struct NonTrivialDeserializeTraits<std::optional<T>> {
    template<typename ELEM_TYPE>
    static Result deserialize(std::optional<T>& obj, ELEM_TYPE node) {
        if (! node) {
            obj.reset();
            return Result::SUCCESS;
        }
        T value;
        CFL_EXPECT_SUCC(NonTrivialDeserializeTraits<T>::deserialize(value, node));
        obj = std::move(value);
        return Result::SUCCESS;
    }
};

}

CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_NONTRIVIALDESERIALIZETRAITS_H
