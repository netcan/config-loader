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
struct TinyXML2Tag {};

template<>
struct Parser<TinyXML2Tag> {
    constexpr Result parse(std::string_view content) {
        return doc.Parse(content.data()) == tinyxml2::XML_SUCCESS
               ? Result::SUCCESS
               : Result::ERR_ILL_FORMED;
    }
    struct ElemType;

    constexpr ElemType toRootElemType() {
        return doc.FirstChildElement();
    }

    struct ElemType {
        constexpr ElemType(tinyxml2::XMLElement* elem): elem(elem) {}
        constexpr operator bool() const { return elem != nullptr; }
        constexpr ElemType toChildElem(const char* fieldName) const {
            return elem->FirstChildElement(fieldName);
        }
        constexpr const char* getValueText() const {
            return elem->GetText();
        }
        constexpr const char* getKeyName() const {
            return elem->Attribute("name");
        }
        template<typename F>
        constexpr Result forEachElement(F&& f) const {
            for (auto item = elem->FirstChildElement()
                    ; item
                    ; item = item->NextSiblingElement()) {
                CFL_EXPECT_SUCC(f(ElemType{item}));
            }
            return Result::SUCCESS;
        }
    private:
        tinyxml2::XMLElement* elem;
    };

private:
    tinyxml2::XMLDocument doc;
};

CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_TINYXML2PARSER_H
