//
// Created by netcan on 2021/07/05.
//

#ifdef HAS_TINYXML2
#include <type_traits>
#include <catch2/catch.hpp>
#include <tinyxml2.h>
#include <config-loader/utils/ConfigPath.h>

using namespace Catch;
using namespace tinyxml2;
using namespace CONFIG_LOADER_NS;

SCENARIO("test path string") {
    GIVEN("empty path") {
        auto path = ""_path;
        THEN("read its content") {
            auto content = path.getContent();
            REQUIRE(content.empty());
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
#endif