//
// Created by netcan on 2021/07/18.
//

#include <catch2/catch.hpp>
#include <config-loader/utils/ContentLoader.h>

using namespace CONFIG_LOADER_NS;
using namespace Catch;

SCENARIO("test ContentLoader") {
    GIVEN("a const char* path") {
        ContentLoader loader("configs/Point.xml");
        REQUIRE(!loader().empty());
    }
    GIVEN("a Config Path") {
        ContentLoader loader = "configs/Point.xml"_path;
        REQUIRE(!loader().empty());
    }
    GIVEN("a lambda") {
        ContentLoader loader = [] {
            return "hello world!";
        };
        REQUIRE_THAT(loader(), Equals("hello world!"));

    }
}