//
// Created by netcan on 2021/07/17.
//

#ifndef CONFIG_LOADER_UNSUPPORTEDPARSER_H
#define CONFIG_LOADER_UNSUPPORTEDPARSER_H
#include <config-loader/ConfigLoaderNS.h>
#include <config-loader/concept/Parser.h>
#include <config-loader/Result.h>

CONFIG_LOADER_NS_BEGIN

struct UnsupportedParser { };
namespace concepts {
template<>
constexpr bool enable_parser<UnsupportedParser> = true;
}

static_assert(concepts::Parser<UnsupportedParser>);
CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_UNSUPPORTEDPARSER_H
