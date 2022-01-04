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

template<typename P>
inline constexpr bool enable_parser = false;

template <typename P>
concept Parser = enable_parser<P> || requires(P p, std::string_view content) {
    requires std::default_initializable<P>;
    typename P::ElemType;
    requires ParserElem<typename P::ElemType>;
    { p.parse(content)   } -> std::same_as<Result>;
    { p.toRootElemType() } -> std::same_as<typename P::ElemType>;
};

};

CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_PARSER_H
