//
// Created by netcan on 2021/07/07.
//

#ifndef CONFIG_LOADER_PRIMITIVEDESERIALIZETRAITS_H
#define CONFIG_LOADER_PRIMITIVEDESERIALIZETRAITS_H
#include <config-loader/ConfigLoaderNS.h>
#include <config-loader/concept/Basic.h>
#include <config-loader/deserialize/DeserializeTraitsDecl.h>
#include <string>
#include <optional>
#include <sstream>
#include <string_view>

CONFIG_LOADER_NS_BEGIN
namespace detail {
constexpr bool isHex(std::string_view num) {
    return (num.substr(0, 2) == "0x" ||
            num.substr(0, 2) == "0X");
}
}
template<concepts::Arithmetic Number>
struct PrimitiveDeserializeTraits<Number>
        : detail::IsSupport<true> {
    static Result deserialize(Number &num, std::optional<std::string> valueText) {
        if (! valueText.has_value()) { return Result::ERR_EXTRACTING_FIELD; }
        // do not treat int8_t/uint8_t as char type
        if constexpr(std::is_same_v<Number, int8_t> || std::is_same_v<Number, uint8_t>) {
            num = std::stol(*valueText, nullptr, detail::isHex(*valueText) ? 16 : 10);
            return Result::SUCCESS;
        } else {
            std::stringstream ss;
            ss << *valueText;
            if (detail::isHex(*valueText)) { ss << std::hex; }
            ss >> num;
            return ss.fail() ? Result::ERR_EXTRACTING_FIELD : Result::SUCCESS;
        }
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

CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_PRIMITIVEDESERIALIZETRAITS_H
