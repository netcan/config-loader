//
// Created by netcan on 2021/07/10.
//

#ifndef CONFIG_LOADER_TINYXML2PARSER_H
#define CONFIG_LOADER_TINYXML2PARSER_H
#include <config-loader/ConfigLoaderNS.h>
#include <config-loader/deserialize/DeserializeTraitsDecl.h>
#include <config-loader/Result.h>
#include <tinyxml2.h>

CONFIG_LOADER_NS_BEGIN
struct TinyXML2Tag;

template<>
struct Parser<TinyXML2Tag> {
    Result parse(std::string_view content) {
        return doc.Parse(content.data()) != tinyxml2::XML_SUCCESS
               ? Result::ERR_ILL_FORMED
               : Result::SUCCESS;
    }
    struct ElemType;

    ElemType toRootElemType() {
        return doc.FirstChildElement();
    }

    struct ElemType {
        constexpr ElemType(tinyxml2::XMLElement* elem): elem(elem) {}
        constexpr operator bool() { return elem != nullptr; }
        constexpr ElemType toChildElem(const char* fieldName = nullptr) {
            return elem->FirstChildElement(fieldName);
        }
        constexpr ElemType toNextSiblingElem() {
            return elem->NextSiblingElement();
        }
        constexpr const char* getValueText() {
            return elem->GetText();
        }
        constexpr const char* getKeyName() {
            return elem->Attribute("name");
        }
    private:
        tinyxml2::XMLElement* elem;
    };

private:
    tinyxml2::XMLDocument doc;
};

CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_TINYXML2PARSER_H
