//
// Created by netcan on 2021/07/10.
//

#ifndef CONFIG_LOADER_JSONCPPPARSER_H
#define CONFIG_LOADER_JSONCPPPARSER_H

#include <config-loader/ConfigLoaderNS.h>
#include <config-loader/Result.h>
#include <config-loader/utils/Assertion.h>
#include <config-loader/parsers/UnsupportedParser.h>
#include <memory>
#include <optional>
#include <string>

#if HAS_JSONCPP
#include <json/json.h>
#endif

CONFIG_LOADER_NS_BEGIN

#if HAS_JSONCPP
struct JsonCppParser {
    Result parse(std::string_view content) {
        Json::CharReaderBuilder builder;
        std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
        return reader->parse(content.data(), content.data() + content.size(),
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
            if (! elem.isObject()) {
                return ElemType{Json::Value::nullSingleton()};
            }
            return ElemType{elem[fieldName]};
        }
        std::optional<std::string> getValueText() const {
            if (elem.isObject() || elem.isArray()) return std::nullopt;
            return elem.asString();
        }
        const char* getKeyName() const {
            return keyName;
        }

        template<typename F>
        Result forEachElement(F&& f) const {
            switch (elem.type()) {
                // null type isn't iterable, handle it as empty container
                case Json::ValueType::nullValue:
                    return Result::SUCCESS;
                case Json::ValueType::arrayValue:
                    for (auto&& e: elem) {
                        CFL_EXPECT_SUCC(f(ElemType{e}));
                    }
                    return Result::SUCCESS;
                case Json::ValueType::objectValue: {
                    auto keys = elem.getMemberNames();
                    for (auto &&key: keys) {
                        CFL_EXPECT_SUCC(f(ElemType{elem[key], key.c_str()}));
                    }
                    return Result::SUCCESS;
                }
                default: // otherwise, is error type
                    return Result::ERR_TYPE;
            }
        }

    private:
        const char * keyName {};
        const Json::Value elem;
    };

private:
    Json::Value root;
};
#else
using JsonCppParser = UnsupportedParser;
#endif

CONFIG_LOADER_NS_END
#endif //CONFIG_LOADER_JSONCPPPARSER_H
