//
// Created by netcan on 2021/07/06.
//

#ifndef CONFIG_LOADER_TINYXML2DESERIALIZETRAITS_H
#define CONFIG_LOADER_TINYXML2DESERIALIZETRAITS_H
#include <config-loader/deserialize/DeserializeTraitsDecl.h>
#include <config-loader/core/ReflectedTraits.h>
#include <config-loader/core/ForEachField.h>
#include <config-loader/Result.h>
#include <list>
#include <deque>
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
        if (content.empty()) {
            return Result::ERR_EMPTY_CONTENT;
        }
        tinyxml2::XMLDocument doc;
        if (doc.Parse(content.data()) != tinyxml2::XML_SUCCESS) {
            return Result::ERR_LOAD_CONTENT;
        }
        return detail::TinyXML2DeserializeTraits<T>::deserialize(obj, doc.FirstChildElement());
    }
};

namespace detail {
template<typename T>
struct TinyXML2DeserializeTraits<T
        , std::enable_if_t<IsReflected_v<T>>> {
    static Result deserialize(T& obj, tinyxml2::XMLElement* node) {
        CONFIG_LOADER_NS::forEachField(obj, [node](const char* fieldName, auto& value) {
            return TinyXML2DeserializeTraits<std::remove_reference_t<decltype(value)>>
                    ::deserialize(value, node->FirstChildElement(fieldName));
        });
        return Result::SUCCESS;
    }
};

template<typename T>
struct TinyXML2DeserializeTraits<T
        , std::enable_if_t<CommonDeserializeTraits<T>::isSupport>> {
    static Result deserialize(T& obj, tinyxml2::XMLElement* node) {
        return CommonDeserializeTraits<T>::deserialize(obj, node->GetText());
    }
};

template<typename T> // for container like list/vector/deque but not string
struct TinyXML2SeqContainerDeserialize {
    static Result deserialize(T& obj, tinyxml2::XMLElement* node) {
        for (auto item = node->FirstChildElement()
                ; item
                ; item = item->NextSiblingElement()) {
            using value_type = typename T::value_type;
            value_type value;
            TinyXML2DeserializeTraits<value_type>::deserialize(value, item);
            obj.push_back(std::move(value));
        }
        return Result::SUCCESS;
    }
};

template<typename T>
struct TinyXML2DeserializeTraits<std::vector<T>>
        : TinyXML2SeqContainerDeserialize<std::vector<T>> { };

template<typename T>
struct TinyXML2DeserializeTraits<std::list<T>>
        : TinyXML2SeqContainerDeserialize<std::list<T>> { };

template<typename T>
struct TinyXML2DeserializeTraits<std::deque<T>>
        : TinyXML2SeqContainerDeserialize<std::deque<T>> { };

}

CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_TINYXML2DESERIALIZETRAITS_H
