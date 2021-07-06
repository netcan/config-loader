//
// Created by netcan on 2021/07/06.
//

#ifndef CONFIG_LOADER_TINYXML2DESERIALIZETRAITS_H
#define CONFIG_LOADER_TINYXML2DESERIALIZETRAITS_H
#include <config-loader/deserialize/DeserializeTraitsDecl.h>
#include <config-loader/core/ReflectedTraits.h>
#include <config-loader/core/ForEachField.h>
#include <config-loader/Result.h>
#include <sstream>
#include <string_view>
#include <tinyxml2.h>

CONFIG_LOADER_NS_BEGIN
struct TinyXML2Tag {};

template<>
struct DeserializeTraits<TinyXML2Tag> {
    template<typename T>
    static Result load(T& obj, std::string_view content) {
        tinyxml2::XMLDocument doc;
        if (doc.Parse(content.data()) != tinyxml2::XML_SUCCESS) {
            return Result::ERR_LOAD_CONTENT;
        }
        return deserialize(obj, doc.FirstChildElement());
    }
private:
    template<typename T>
    static Result deserialize(T& obj, tinyxml2::XMLElement* node) {
        if constexpr(IsReflected_v<std::decay_t<T>>) {
            forEachField(obj, [node](const char* fieldName, auto& value) {
                return deserialize(value, node->FirstChildElement(fieldName));
            });
            return Result::SUCCESS;
        } else { // isn't reflected
            std::stringstream ss;
            std::string_view valueText = node->GetText();
            ss << node->GetText();
            if (valueText.substr(0, 2) == "0x") { ss << std::hex; }
            ss >> obj;
            if (valueText.substr(0, 2) == "0x") { ss << std::oct; }
        }
        return Result::SUCCESS;
    }
};

CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_TINYXML2DESERIALIZETRAITS_H
