//
// Created by netcan on 2021/07/10.
//

#include <catch2/catch.hpp>
#include <config-loader/ConfigLoader.h>
#include "ReflectedStruct.h"
#include "DeserializeConfig.h"

using namespace CONFIG_LOADER_NS;
using namespace Catch;

SCENARIO("mixin deserializer") {
    Deserializer deserializer {
            JsonLoader<Point>(json_config::POINT_CONFIG_PATH),
            XMLLoader<Rect>(xml_config::RECT_CONFIG_PATH),
            YamlLoader<SomeOfPoints>()
    };

    WHEN("deserialize a flatten point config") {
        Point point;
        REQUIRE(deserializer.load(point) == Result::SUCCESS);
        REQUIRE(point.x == 1.2);
        REQUIRE(point.y == 3.4);
    }

    WHEN("deserialize a nest rect config") {
        Rect rect;
        REQUIRE(deserializer.load(rect) == Result::SUCCESS);
        REQUIRE(rect.p1.x == 1.2);
        REQUIRE(rect.p1.y == 3.4);
        REQUIRE(rect.p2.x == 5.6);
        REQUIRE(rect.p2.y == 7.8);
        REQUIRE(rect.color == 0x12345678);
    }

    WHEN("deserialize a complex rect config") {
        SomeOfPoints someOfPoints;
        auto res = deserializer.load(someOfPoints, yaml_config::SOME_OF_POINTS_CONFIG_PATH);
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
