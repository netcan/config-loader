//
// Created by netcan on 2021/07/06.
//

#ifndef CONFIG_LOADER_TINYXML2DESERIALIZETRAITS_H
#define CONFIG_LOADER_TINYXML2DESERIALIZETRAITS_H
#include <config-loader/deserialize/DeserializeTraitsDecl.h>
#include <config-loader/core/ReflectedTraits.h>
#include <config-loader/core/ForEachField.h>
#include <config-loader/Result.h>
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

}

CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_TINYXML2DESERIALIZETRAITS_H
