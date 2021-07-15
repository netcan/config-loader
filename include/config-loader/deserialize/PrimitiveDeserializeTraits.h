//
// Created by netcan on 2021/07/07.
//

#ifndef CONFIG_LOADER_PRIMITIVEDESERIALIZETRAITS_H
#define CONFIG_LOADER_PRIMITIVEDESERIALIZETRAITS_H
#include <config-loader/ConfigLoaderNS.h>
#include <config-loader/deserialize/DeserializeTraitsDecl.h>
#include <string>
#include <optional>
#include <sstream>
#include <string_view>

CONFIG_LOADER_NS_BEGIN
namespace detail {
template<typename Integer>
struct PrimitiveDeserializeTraits<Integer, std::enable_if_t<std::is_arithmetic_v<Integer>>>
        : detail::IsSupport<true> {
    static Result deserialize(Integer &num, std::optional<std::string> valueText) {
        if (! valueText.has_value()) { return Result::ERR_EXTRACTING_FIELD; }
        std::stringstream ss;
        ss << *valueText;
        if (valueText->substr(0, 2) == "0x" ||
            valueText->substr(0, 2) == "0X") { ss << std::hex; }
        ss >> num;
        return ss.fail() ? Result::ERR_EXTRACTING_FIELD : Result::SUCCESS;
    }
};

template<>
struct PrimitiveDeserializeTraits<bool>
        : detail::IsSupport<true> {
    static Result deserialize(bool &value, std::optional<std::string> valueText) {
        if (! valueText.has_value()) { return Result::ERR_EXTRACTING_FIELD; }
        std::stringstream ss;
        ss << *valueText;
        ss >> value;
        if (!ss.fail()) { return Result::SUCCESS; }
        if (valueText == "true" || valueText == "True") {
            value = true;
            return Result::SUCCESS;
        }
        if (valueText == "false" || valueText == "False") {
            value = false;
            return Result::SUCCESS;
        }

        return Result::ERR_EXTRACTING_FIELD;
    }
};

template<>
struct PrimitiveDeserializeTraits<std::string>
        : detail::IsSupport<true> {
    static Result deserialize(std::string &str, std::optional<std::string> valueText) {
        if (! valueText.has_value()) { return Result::ERR_EXTRACTING_FIELD; }
        str = std::move(*valueText);
        return Result::SUCCESS;
    }
};
}

CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_PRIMITIVEDESERIALIZETRAITS_H
