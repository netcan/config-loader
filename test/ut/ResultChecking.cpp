//
// Created by netcan on 2021/07/08.
//

#include <catch2/catch.hpp>
#include <tinyxml2.h>
#include <config-loader/ConfigLoader.h>
#include "ReflectedStruct.h"

using namespace CONFIG_LOADER_NS;

SCENARIO("Error checking") {
    WHEN("a empty config") {
        Point point;
        auto res = deserializer.load(point, [] {
            return "";
        });
        REQUIRE(res == Result::ERR_EMPTY_CONTENT);
    }

    WHEN("a ill-format config") {
        Point point;
        auto res = deserializer.load(point, [] {
            return "<eeeeeeeeeeeeee";
        });
        REQUIRE(res == Result::ERR_ILL_FORMED);
    }

    WHEN("a lacking field config") {
        {
            Point point;
            auto res = deserializer.load(point, [] {
                return R"(
                    <?xml version="1.0" encoding="UTF-8"?>
                    <point>
                        <x>1.2</x>
                    </point>
                )";
            });
            REQUIRE(res == Result::ERR_MISSING_FIELD);
        }

        {
            SomeOfPoints someOfPoints;
            auto res = deserializer.load(someOfPoints, [] {
                return R"(
                    <?xml version="1.0" encoding="UTF-8"?>
                    <some_of_points>
                        <name>Some of points</name>
                        <points>
                            <value>
                                <y>3.3</y>
                            </value>
                        </points>
                    </some_of_points>
                )";
            });
            REQUIRE(res == Result::ERR_MISSING_FIELD);
        }
    }

    WHEN("a err extracting field config") {
        Point point;
        auto res = deserializer.load(point, [] {
            return R"(
                    <?xml version="1.0" encoding="UTF-8"?>
                    <point>
                        <x>abc</x>
                    </point>
                )";
        });
        REQUIRE(res == Result::ERE_EXTRACTING_FIELD);
    }

}