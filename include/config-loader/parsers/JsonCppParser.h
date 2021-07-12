//
// Created by netcan on 2021/07/10.
//

#ifndef CONFIG_LOADER_JSONCPPPARSER_H
#define CONFIG_LOADER_JSONCPPPARSER_H
#include <config-loader/ConfigLoaderNS.h>
#include <config-loader/deserialize/DeserializeTraitsDecl.h>
#include <config-loader/utils/Assertion.h>
#include <config-loader/Result.h>
#include <memory>
#include <json/json.h>

CONFIG_LOADER_NS_BEGIN

struct JsonCppParser {
    Result parse(std::string_view content) {
        Json::CharReaderBuilder builder;
        std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
        return reader->parse(content.begin(), content.end(),
                             &root , nullptr)
               ? Result::SUCCESS
               : Result::ERR_ILL_FORMED;
    }

    struct ElemType;

    ElemType toRootElemType() {
        return ElemType{root};
    }

    struct ElemType {
        explicit ElemType(const Json::Value& elem, const char* keyName = {})
                : keyName(keyName), elem(elem) {}
        bool isValid() const { return ! elem.isNull(); }
        ElemType toChildElem(const char* fieldName) const {
            return ElemType{elem[fieldName]};
        }
        std::string getValueText() const {
            return elem.asString();
        }
        const char* getKeyName() const {
            return keyName;
        }

        template<typename F>
        Result forEachElement(F&& f) const {
            if (!elem.isArray() && !elem.isObject()) {
                return Result::ERR_TYPE;
            }

            if (elem.isArray()) {
                for (auto e: elem) {
                    CFL_EXPECT_SUCC(f(ElemType{e}));
                }
            } else {
                auto keys = elem.getMemberNames();
                for (auto key: keys) {
                    CFL_EXPECT_SUCC(f(ElemType{elem[key], key.c_str()}));
                }
            }
            return Result::SUCCESS;
        }

    private:
        const char * keyName {};
        const Json::Value elem;
    };

private:
    Json::Value root;
};

CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_JSONCPPPARSER_H
