//
// Created by netcan on 2021/07/05.
//

#include <type_traits>
#include <catch2/catch.hpp>
#include <config-loader/utils/ConfigPath.h>

using namespace Catch;
using namespace CONFIG_LOADER_NS;

SCENARIO("test path string") {
    GIVEN("user-defined string literal") {
        {
            auto path = ""_path;
            static_assert(path.isEmpty);
        }
        {
            using PATH = decltype("hello world.xml"_path);
            static_assert(sizeof(PATH) == 1);
            static_assert(! PATH::isEmpty);
            REQUIRE_THAT(PATH::value, Equals("hello world.xml"));
            static_assert(PATH::value[15] == '\0');
            static_assert(std::extent_v<decltype(PATH::value)> == 16);
        }
    }
}