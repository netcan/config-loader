//
// Created by netcan on 2021/07/05.
//

#include <type_traits>
#include <catch2/catch.hpp>
#include <tinyxml2.h>
#include <config-loader/utils/ConfigPath.h>

using namespace Catch;
using namespace tinyxml2;
using namespace CONFIG_LOADER_NS;

SCENARIO("test path string") {
    WHEN("user-defined string literal") {
        {
            constexpr auto path = "/home/netcan/test.xml"_path;
            REQUIRE_THAT(path.value, Equals("/home/netcan/test.xml"));
            static_assert(sizeof(path) == 1);
        }
        {
            using PATH = decltype("hello world.xml"_path);
            REQUIRE_THAT(PATH::value, Equals("hello world.xml"));
            static_assert(PATH::length == 15);
            static_assert(PATH::value[15] == '\0');
            static_assert(std::extent_v<decltype(PATH::value)> == 16);
        }
    }
    GIVEN("config path") {
        auto path = "configs/SomeOfPoints.xml"_path;
        THEN("read its content") {
            auto content = path.getContent();
            REQUIRE(! content.empty());
            THEN("is a valid xml") {
                XMLDocument doc;
                REQUIRE(doc.Parse(content.c_str()) == XML_SUCCESS);
            }
        }
    }

}