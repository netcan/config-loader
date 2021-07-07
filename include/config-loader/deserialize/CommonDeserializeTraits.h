//
// Created by netcan on 2021/07/07.
//

#ifndef CONFIG_LOADER_COMMONDESERIALIZETRAITS_H
#define CONFIG_LOADER_COMMONDESERIALIZETRAITS_H
#include <config-loader/ConfigLoaderNS.h>
#include <config-loader/deserialize/DeserializeTraitsDecl.h>
#include <string>
#include <sstream>
#include <string_view>

CONFIG_LOADER_NS_BEGIN

template<typename Integer>
struct CommonDeserializeTraits<Integer
        , std::enable_if_t<std::is_arithmetic_v<Integer>>>
        : detail::IsSupport<true> {
    static Result deserialize(Integer& num, std::string_view valueText) {
        std::stringstream ss;
        ss << valueText;
        if (valueText.substr(0, 2) == "0x") { ss << std::hex; }
        ss >> num;
        if (valueText.substr(0, 2) == "0x") { ss << std::oct; }
        return Result::SUCCESS;
    }
};

template<>
struct CommonDeserializeTraits<std::string>
        : detail::IsSupport<true> {
    static Result deserialize(std::string& str, std::string_view valueText) {
        str = valueText;
        return Result::SUCCESS;
    }
};

CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_COMMONDESERIALIZETRAITS_H
