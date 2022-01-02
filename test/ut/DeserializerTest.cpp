//
// Created by netcan on 2021/07/07.
//

#include <catch2/catch.hpp>
#include <config-loader/ConfigLoader.h>
#include "UTSchema.h"
#include "DeserializeConfig.h"

using namespace Catch;
using namespace CONFIG_LOADER_NS;
using namespace xml_config;

SCENARIO("loadXML2Obj test") {
    GIVEN("load by path") {
        THEN("load both by default config") {
            {
                Point point;
                REQUIRE(loadXML2Obj(point, POINT_CONFIG_PATH) == Result::SUCCESS);
                REQUIRE(point.x == 1.2);
                REQUIRE(point.y == 3.4);
            }
            {
                Rect rect;
                REQUIRE(loadXML2Obj(rect, RECT_CONFIG_PATH) == Result::SUCCESS);
                REQUIRE(rect.p1.x == 1.2);
                REQUIRE(rect.p1.y == 3.4);
                REQUIRE(rect.p2.x == 5.6);
                REQUIRE(rect.p2.y == 7.8);
                REQUIRE(rect.color == 0x12345678);
            }

            {
                SomeOfPoints someOfPoints;
                REQUIRE(loadXML2Obj(someOfPoints, SOME_OF_POINTS_CONFIG_PATH) == Result::SUCCESS);

                REQUIRE_THAT(someOfPoints.name,
                             Equals("Some of points"));
                REQUIRE(someOfPoints.points.size() == 3);
            }
        }

        THEN("load by lambda") {
            Rect rect;
            auto res = loadXML2Obj(rect, [] {
                return R"(
                    <?xml version="1.0" encoding="UTF-8"?>
                    <rect>
                        <p1>
                            <x>5.6</x>
                            <y>7.8</y>
                        </p1>
                        <p2>
                            <x>1.2</x>
                            <y>3.4</y>
                        </p2>
                        <color>0x12345678</color>
                    </rect>
                )";
            });
            REQUIRE(res == Result::SUCCESS);
            REQUIRE(rect.p2.x == 1.2);
            REQUIRE(rect.p2.y == 3.4);
            REQUIRE(rect.p1.x == 5.6);
            REQUIRE(rect.p1.y == 7.8);
            REQUIRE(rect.color == 0x12345678);
        }
    }
}

