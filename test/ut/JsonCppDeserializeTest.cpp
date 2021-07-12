//
// Created by netcan on 2021/07/10.
//

#include <catch2/catch.hpp>
#include <tinyxml2.h>
#include "ReflectedStruct.h"
#include "DeserializeJsonConfig.h"
#include <config-loader/ConfigLoader.h>

using namespace Catch;
using namespace CONFIG_LOADER_NS;

SCENARIO("deserialize json to struct") {
    using namespace json_config;
    GIVEN("a flatten point config") {
        Point point;
        auto deserializer = JsonLoader<Point>();
        auto res = deserializer.load(point, [] {
            return POINT_CONFIG;
        });
        REQUIRE(res == Result::SUCCESS);
        REQUIRE(point.x == 1.2);
        REQUIRE(point.y == 3.4);
    }

    GIVEN("a nest rect config") {
        Rect rect;
        auto deserializer = JsonLoader<Rect>();
        auto res = deserializer.load(rect, [] {
            return RECT_CONFIG;
        });
        REQUIRE(res == Result::SUCCESS);
        REQUIRE(rect.p1.x == 1.2);
        REQUIRE(rect.p1.y == 3.4);
        REQUIRE(rect.p2.x == 5.6);
        REQUIRE(rect.p2.y == 7.8);
        REQUIRE(rect.color == 12345678);
    }

    GIVEN("a nest rect config that missing p1/p2") {
        Rect rect;
        auto deserializer = JsonLoader<Rect>();
        auto res = deserializer.load(rect, [] {
            return R"({ "color": 12345678 })";
        });
        REQUIRE(res == Result::ERR_MISSING_FIELD);
    }

    GIVEN("a complex rect config") {
        SomeOfPoints someOfPoints;
        auto deserializer = JsonLoader<SomeOfPoints>();
        auto res = deserializer.load(someOfPoints, [] {
            return SOME_OF_POINTS_CONFIG;
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

///////////////////////////////////////////////////////////////////////////////
SCENARIO("deserialize json to extra STL container") {
    GIVEN("a valid STL obj") {
        auto deserializer = JsonLoader<STLObj>();
        STLObj data;
        auto res = deserializer.load(data, [] {
            return R"(
                {
                  "m1": { "0": 2, "1": 4, "2": 6, },
                  "m2": {
                    "hello world": { "x": 1.2, "y": 3.4 }
                  },
                  "m3": {},
                  "m4": { "x": 5.6, "y": 7.8 }
                }
             )";
        });
        REQUIRE(res == Result::SUCCESS);
        REQUIRE(data.m1[0] == 2);
        REQUIRE(data.m1[1] == 4);
        REQUIRE(data.m1[2] == 6);
        REQUIRE(data.m1.size() == 3);

        REQUIRE(data.m2["hello world"].x == 1.2);
        REQUIRE(data.m2["hello world"].y == 3.4);
        REQUIRE(data.m2.size() == 1);

        REQUIRE(data.m3.empty());

        REQUIRE(data.m4.has_value());
        REQUIRE(data.m4->x == 5.6);
        REQUIRE(data.m4->y == 7.8);

        REQUIRE(! data.m5.has_value());
        REQUIRE(data.m6.empty());
    }

}
