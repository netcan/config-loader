//
// Created by netcan on 2021/07/07.
//

#include <catch2/catch.hpp>
#include <config-loader/ConfigLoader.h>
#include "ReflectedStruct.h"

using namespace Catch;
using namespace CONFIG_LOADER_NS;

constexpr auto rectConfigPath = "configs/Rect.xml"_path;
constexpr auto someOfPointsConfigPath = "configs/SomeOfPoints.xml"_path;

SCENARIO("test deserializable config file") {
    WHEN("deserializable build by type") {
        Deserializable<SomeOfPoints
                , TinyXML2Tag
                , decltype(someOfPointsConfigPath)> deserializer;

        SomeOfPoints someOfPoints;
        REQUIRE(deserializer.load(someOfPoints) == Result::SUCCESS);
        REQUIRE_THAT(someOfPoints.name,
                     Equals("Some of points"));
        REQUIRE(someOfPoints.points.size() == 3);
    }

    WHEN("deserializable build by value") {
        Deserializable deserializer(SomeOfPoints{}
            , TinyXML2Tag{}
            , someOfPointsConfigPath);

        SomeOfPoints someOfPoints;
        REQUIRE(deserializer.load(someOfPoints) == Result::SUCCESS);
        REQUIRE_THAT(someOfPoints.name,
                     Equals("Some of points"));
        REQUIRE(someOfPoints.points.size() == 3);
    }

}
SCENARIO("composing deserializable to deserializer") {
    GIVEN("composing by type") {
        using RectDeserializable = Deserializable<Rect
                , TinyXML2Tag
                , decltype(rectConfigPath)>;
        using SomeOfPointsDeserializable = Deserializable<SomeOfPoints
                , TinyXML2Tag
                , decltype(someOfPointsConfigPath)>;
        Deserializer<RectDeserializable
                    , SomeOfPointsDeserializable> deserializer;

        THEN("load both by default config") {
            {
                Rect rect;
                REQUIRE(deserializer.load(rect) == Result::SUCCESS);
                REQUIRE(rect.p1.x == 1.2);
                REQUIRE(rect.p1.y == 3.4);
                REQUIRE(rect.p2.x == 5.6);
                REQUIRE(rect.p2.y == 7.8);
                REQUIRE(rect.color == 0x12345678);
            }

            {
                SomeOfPoints someOfPoints;
                REQUIRE(deserializer.load(someOfPoints) == Result::SUCCESS);

                REQUIRE_THAT(someOfPoints.name,
                             Equals("Some of points"));
                REQUIRE(someOfPoints.points.size() == 3);
            }
        }

        THEN("load by custom config") {
            Rect rect;
            auto res = deserializer.load(rect, [] {
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

    GIVEN("composing by value") {
        Deserializer deserializer(
                AddItem<Point, TinyXML2Tag>("configs/Point.xml"_path),
                AddItem<Rect, TinyXML2Tag>("configs/Rect.xml"_path),
                AddItem<SomeOfPoints, TinyXML2Tag>("configs/SomeOfPoints.xml"_path)
        );
        THEN("deserialize a flatten point") {
            Point point;
            REQUIRE(deserializer.load(point) == Result::SUCCESS);
            REQUIRE(point.x == 1.2);
            REQUIRE(point.y == 3.4);
        }
        THEN("deserialize a complex config") {
            {
                SomeOfPoints someOfPoints;
                REQUIRE(deserializer.load(someOfPoints) == Result::SUCCESS);
                REQUIRE_THAT(someOfPoints.name,
                             Equals("Some of points"));
                REQUIRE(someOfPoints.points.size() == 3);
            }
        }
    }

}

