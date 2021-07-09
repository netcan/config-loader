//
// Created by netcan on 2021/07/06.
//

#ifndef CONFIG_LOADER_TINYXML2DESERIALIZETRAITS_H
#define CONFIG_LOADER_TINYXML2DESERIALIZETRAITS_H
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
#include <tinyxml2.h>

CONFIG_LOADER_NS_BEGIN
struct TinyXML2Tag {};

namespace detail {
template<typename T, typename = void>
struct TinyXML2DeserializeTraits;
}

template<>
struct DeserializeTraits<TinyXML2Tag> {
    template<typename T>
    static Result load(T& obj, std::string_view content) {
        if (content.empty()) { return Result::ERR_EMPTY_CONTENT; }
        tinyxml2::XMLDocument doc;
        if (doc.Parse(content.data()) != tinyxml2::XML_SUCCESS) {
            return Result::ERR_ILL_FORMED;
        }
        auto firstElem = doc.FirstChildElement();
        if (firstElem == nullptr) { return Result::ERR_MISSING_FIELD; }
        return detail::TinyXML2DeserializeTraits<T>::deserialize(obj, *firstElem);
    }
};

namespace detail {
template<typename T>
struct TinyXML2DeserializeTraits<T
        , std::enable_if_t<IsReflected_v<T>>> {
    static Result deserialize(T& obj, tinyxml2::XMLElement& node) {
        return CONFIG_LOADER_NS::forEachField(obj, [&node](const char* fieldName, auto& value) {
            if (auto fieldElem = node.FirstChildElement(fieldName)) {
                return TinyXML2DeserializeTraits<std::remove_reference_t<decltype(value)>>
                        ::deserialize(value, *fieldElem);
            } else {
                LOGE("not such field: %s", fieldName);
                return Result::ERR_MISSING_FIELD;
            }
        });
    }
};

template<typename T>
struct TinyXML2DeserializeTraits<T
        , std::enable_if_t<CommonDeserializeTraits<T>::isSupport>> {
    static Result deserialize(T& obj, tinyxml2::XMLElement& node) {
        return CommonDeserializeTraits<T>::deserialize(obj, node.GetText());
    }
};

template<typename F>
constexpr Result forEachXMLElement(tinyxml2::XMLElement& node, F&& f) {
    for (auto item = node.FirstChildElement()
            ; item != nullptr
            ; item = item->NextSiblingElement()) {
        CFL_EXPECT_SUCC(f(*item));
    }
    return Result::SUCCESS;
}

template<typename SEQ> // for container like list/vector/deque but not string, code reuse
struct TinyXML2SeqContainerDeserialize {
    static Result deserialize(SEQ& container, tinyxml2::XMLElement& node) {
        using value_type = typename SEQ::value_type;
        return forEachXMLElement(node, [&container](auto&& item) {
            value_type value;
            CFL_EXPECT_SUCC(TinyXML2DeserializeTraits<value_type>::deserialize(value, item));
            container.push_back(std::move(value));
            return Result::SUCCESS;
        });
    }
};

template<typename T> // code reuse
struct TinyXML2DeserializeTraits<std::vector<T>>
        : TinyXML2SeqContainerDeserialize<std::vector<T>> { };

template<typename T> // code reuse
struct TinyXML2DeserializeTraits<std::list<T>>
        : TinyXML2SeqContainerDeserialize<std::list<T>> { };

template<typename T> // code reuse
struct TinyXML2DeserializeTraits<std::deque<T>>
        : TinyXML2SeqContainerDeserialize<std::deque<T>> { };

template<typename KV> // for kv container like map/unordered_map, code reuse
struct TinyXML2KVContainerDeserialize {
    static Result deserialize(KV& container, tinyxml2::XMLElement& node) {
        using Key = typename KV::key_type;
        using Value = typename KV::mapped_type;

        return forEachXMLElement(node, [&container](tinyxml2::XMLElement& item) {
            Key key; // Key is simply from XML Key Name
            auto keyName = item.Attribute("name");
            if (keyName == nullptr) { return Result::ERE_EXTRACTING_FIELD; }
            CFL_EXPECT_SUCC(CommonDeserializeTraits<Key>::deserialize(key, keyName));

            Value value; // Value may be complex data struct
            CFL_EXPECT_SUCC(TinyXML2DeserializeTraits<Value>::deserialize(value, item));

            if (auto [_, inserted] = container.emplace(std::move(key), std::move(value)); !inserted) {
                LOGI("inserted field %s fail, may contain duplicate key", keyName);
            }
            return Result::SUCCESS;
        });
    }
};

template<typename K, typename V>
struct TinyXML2DeserializeTraits<std::map<K, V>>
        : TinyXML2KVContainerDeserialize<std::map<K, V>> {};

template<typename K, typename V>
struct TinyXML2DeserializeTraits<std::unordered_map<K, V>>
        : TinyXML2KVContainerDeserialize<std::unordered_map<K, V>> {};

}

CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_TINYXML2DESERIALIZETRAITS_H
