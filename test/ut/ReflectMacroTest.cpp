//
// Created by netcan on 2021/07/04.
//
#include <catch2/catch.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <config-loader/ConfigLoader.h>
#include "ReflectedStruct.h"

using namespace CONFIG_LOADER_NS;

template<typename T>
static void serializeObj(std::ostream& out, T&& obj,
                         const char* fieldName = "", int depth = 0) {
    auto indent = [&] {
        for (int i = 0; i < depth; ++i)
        { out << "    "; }
    };

    if constexpr(IsReflected_v<std::decay_t<T>>) {
        indent();
        out << fieldName << (*fieldName ? ": {" : "{") << std::endl;
        forEachField(std::forward<T>(obj),
                     [&](auto&& fieldName, auto&& value)
                     { serializeObj(out, value, fieldName, depth + 1); });
        indent();
        out << "}" << std::endl;
    } else {
        indent();
        out << fieldName << ": " << obj << std::endl;
    }
}

template<typename T>
static void deserializeObj(std::istream& in, T&& obj,
                           const char* fieldName = "") {
    if constexpr(IsReflected_v<std::decay_t<T>>) {
        std::string token;
        in >> token; // eat '{'
        if (*fieldName) {
            in >> token; // WARNING: needs check fieldName valid
        }

        forEachField(std::forward<T>(obj),
                     [&](auto&& fieldName, auto&& value)
                     { deserializeObj(in, value, fieldName); });

        in >> token; // eat '}'
    } else {
        if (*fieldName) {
            std::string token;
            in >> token; // WARNING: needs check fieldName valid
        }
        in >> obj; // dump value
    }
}

SCENARIO("reflect a struct") {
    WHEN("retrieve field count") {
        static_assert(Point::_field_count_ == 2);
        static_assert(Rect::_field_count_ == 3);
    }

    WHEN("serialize and deserialize obj") {
        std::stringstream result; // serialize result
        {
            Rect rect {
                    {1.2, 3.4},
                    {5.6, 7.8},
                    0x12345678,
            };
            serializeObj(result, rect);
        }
        std::cout << "serialize rect result:" << std::endl
                  << result.str() << std::endl;
        {
            Rect rect;
            deserializeObj(result, rect);
            REQUIRE(rect.p1.x == 1.2);
            REQUIRE(rect.p1.y == 3.4);
            REQUIRE(rect.p2.x == 5.6);
            REQUIRE(rect.p2.y == 7.8);
            REQUIRE(rect.color == 0x12345678);
        }

    }

}