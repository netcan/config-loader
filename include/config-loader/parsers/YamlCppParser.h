//
// Created by netcan on 2021/07/16.
//

#ifndef CONFIG_LOADER_YAMLCPPPARSER_H
#define CONFIG_LOADER_YAMLCPPPARSER_H
#include <config-loader/ConfigLoaderNS.h>
#include <config-loader/utils/Assertion.h>
#include <config-loader/parsers/UnsupportedParser.h>
#include <config-loader/Result.h>
#include <optional>
#include <string_view>

#if HAS_YAMLCPP
#include <yaml-cpp/yaml.h>
#endif

CONFIG_LOADER_NS_BEGIN

#if HAS_YAMLCPP
struct YamlCppParser {
    Result parse(std::string_view content) {
        root = YAML::Load(content.data());
        return root.IsNull()
               ? Result::ERR_ILL_FORMED
               : Result::SUCCESS;
    }
    struct ElemType;

    ElemType toRootElemType() {
        return ElemType{root};
    }

    struct ElemType {
        explicit ElemType(const YAML::Node &node, const char *keyName = {})
                : keyName(keyName), node(node) {}

        bool isValid() const { return node.IsDefined(); }
        ElemType toChildElem(const char* fieldName) const {
            if (! node.IsMap()) {
                return ElemType{YAML::Node()};
            }
            return ElemType{node[fieldName]};
        }

        std::optional<std::string> getValueText() const {
            if (node.IsMap() || node.IsSequence()) return std::nullopt;
            return node.as<std::string>();
        }

        const char* getKeyName() const {
            return keyName;
        }

        template<typename F>
        Result forEachElement(F&& f) const {
            switch (node.Type()) {
                // null type isn't iterable, handle it as empty container
                case YAML::NodeType::Null:
                    return Result::SUCCESS;
                case YAML::NodeType::Sequence:
                    for(auto&& e: node) {
                        CFL_EXPECT_SUCC(f(ElemType{e}));
                    }
                    return Result::SUCCESS;
                case YAML::NodeType::Map:
                    for(auto&& e: node) {
                        auto keyName = e.first.as<std::string>();
                        CFL_EXPECT_SUCC(f(ElemType{e.second, keyName.c_str()}));
                    }
                    return Result::SUCCESS;
                default: // otherwise, is error type
                    return Result::ERR_TYPE;
            }
        }

    private:
        const char* keyName {};
        const YAML::Node node;
    };

private:
    YAML::Node root;
};
#else
using YamlCppParser = UnsupportedParser;
#endif

CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_YAMLCPPPARSER_H
