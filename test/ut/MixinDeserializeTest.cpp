//
// Created by netcan on 2021/07/10.
//

#include <catch2/catch.hpp>
#include <config-loader/ConfigLoader.h>
#include "ReflectedStruct.h"

using namespace CONFIG_LOADER_NS;
using namespace Catch;

SCENARIO("mixin deserializer") {
    Deserializer deserializer(
            JsonLoader<Point>(),
            XMLLoader<Rect>(),
            JsonLoader<SomeOfPoints>()
    );

    WHEN("deserialize a flatten point config") {
        Point point;
        auto res = deserializer.load(point, [] {
            return R"({ "x": 1.2, "y": 3.4 })";
        });
        REQUIRE(res == Result::SUCCESS);
        REQUIRE(point.x == 1.2);
        REQUIRE(point.y == 3.4);
    }

    WHEN("deserialize a nest rect config") {
        Rect rect;
        auto res = deserializer.load(rect, [] {
            return R"(
                <?xml version="1.0" encoding="UTF-8"?>
                <rect>
                    <p1><x>1.2</x><y>3.4</y></p1>
                    <p2><x>5.6</x><y>7.8</y></p2>
                    <color>0x12345678</color>
                </rect>
            )";
        });
        REQUIRE(res == Result::SUCCESS);
        REQUIRE(rect.p1.x == 1.2);
        REQUIRE(rect.p1.y == 3.4);
        REQUIRE(rect.p2.x == 5.6);
        REQUIRE(rect.p2.y == 7.8);
        REQUIRE(rect.color == 0x12345678);
    }

    WHEN("deserialize a complex rect config") {
        SomeOfPoints someOfPoints;
        auto res = deserializer.load(someOfPoints, [] {
            return R"(
                {
                  "name": "Some of points",
                  "points":[
                    { "x": 1.2, "y": 3.4 },
                    { "x": 5.6, "y": 7.8 },
                    { "x": 2.2, "y": 3.3 }
                  ]
                }
            )";
        });
        REQUIRE(res == Result::SUCCESS);
        REQUIRE_THAT(someOfPoints.name,
                     Equals("Some of points"));
        REQUIRE(someOfPoints.points.size() == 3);
        double pointsV[] = {
                1.2, 3.4,
                5.6, 7.8,
                2.2, 3.3
        };
        for (size_t i = 0; i < someOfPoints.points.size(); ++i) {
            REQUIRE(someOfPoints.points[i].x == pointsV[i * 2]);
            REQUIRE(someOfPoints.points[i].y == pointsV[i * 2 + 1]);
        }
    }
}
