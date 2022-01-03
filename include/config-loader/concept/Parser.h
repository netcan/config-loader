//
// Created by netcan on 2021/07/19.
//

#ifndef CONFIG_LOADER_PARSER_H
#define CONFIG_LOADER_PARSER_H
#include <config-loader/ConfigLoaderNS.h>
#include <config-loader/Result.h>
#include <string_view>
#include <concepts>

CONFIG_LOADER_NS_BEGIN
namespace concepts {
template <typename ELEM_TYPE>
concept ParserElem = requires(const ELEM_TYPE elem) {
    { elem.isValid()      } -> std::convertible_to<bool>;
    { elem.getValueText() } -> std::same_as<std::optional<std::string>>;
    { elem.getKeyName()   } -> std::same_as<const char*>;
    requires requires (Result (&f)(ELEM_TYPE&&)) {
        elem.forEachElement(f);
    };
};

template <typename P>
concept Parser = requires(P parser, std::string_view content) {
    typename P::ElemType;
    requires ParserElem<typename P::ElemType>;
    { parser.parse(content)   } -> std::same_as<Result>;
    { parser.toRootElemType() } -> std::same_as<typename P::ElemType>;
};

};

CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_PARSER_H
