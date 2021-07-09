//
// Created by netcan on 2021/07/06.
//

#include <catch2/catch.hpp>
#include <map>
#include <tinyxml2.h>
#include <iostream>
#include "ReflectedStruct.h"
#include "DeserializeXMLConfig.h"
#include <config-loader/ConfigLoader.h>
using namespace Catch;
using namespace tinyxml2;
using namespace CONFIG_LOADER_NS;

SCENARIO("deserialize xml to struct") {
    WHEN("deserialize a flatten point config") {
        Point point;
        Deserializable<Point, TinyXML2Tag> deserializer;
        auto res = deserializer.load(point, [] {
            return POINT_CONFIG;
        });
        REQUIRE(res == Result::SUCCESS);
        REQUIRE(point.x == 1.2);
        REQUIRE(point.y == 3.4);
    }

    WHEN("deserialize a nest rect config") {
        Rect rect;
        Deserializable<Rect, TinyXML2Tag> deserializer;
        auto res = deserializer.load(rect, [] {
            return RECT_CONFIG;
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
        Deserializable<SomeOfPoints, TinyXML2Tag> deserializer;
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
DEFINE_STRUCT(STLObj,
              (std::map<int, int>) m1,
              (std::unordered_map<std::string, Point>) m2,
              (std::map<int, int>) m3,
              (std::optional<Point>) m4,
              (std::optional<int>) m5);

SCENARIO("deserialize xml to extra STL container") {
    GIVEN("a STL obj") {
        STLObj data;
        auto deserializer = XMLLoader<STLObj>();
        auto res = deserializer.load(data, [] {
            return R"(
                <STLOBj>
                    <m1>
                        <key name="0">2</key>
                        <key name="1">4</key>
                        <key name="2">6</key>
                        <key name="2">8</key>
                    </m1>
                    <m2>
                        <key name="hello world">
                            <x>1.2</x>
                            <y>3.4</y>
                        </key>
                    </m2>
                    <m3></m3>
                    <m4>
                        <x>5.6</x>
                        <y>7.8</y>
                    </m4>
                </STLOBj>
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
    }

}
