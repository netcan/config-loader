//
// Created by netcan on 2021/07/07.
//

#include <catch2/catch.hpp>
#include <config-loader/ConfigLoader.h>
#include "ReflectedStruct.h"

using namespace Catch;
using namespace CONFIG_LOADER_NS;

SCENARIO("test deserializable config file") {
    constexpr auto someOfPointsPath = "configs/SomeOfPoints.xml"_path;
    WHEN("deserializable a complex data from xml file") {
        Deserializable<SomeOfPoints
                , TinyXML2Tag
                , decltype(someOfPointsPath)> deserializer;

        SomeOfPoints someOfPoints;
        REQUIRE(deserializer.load(someOfPoints) == Result::SUCCESS);
        REQUIRE_THAT(someOfPoints.name,
                     Equals("Some of points"));
        REQUIRE(someOfPoints.points.size() == 3);
    }

    WHEN("deserializable a complex data from xml file") {
        Deserializable deserializer(SomeOfPoints{}, TinyXML2Tag{}, someOfPointsPath);

        SomeOfPoints someOfPoints;
        REQUIRE(deserializer.load(someOfPoints) == Result::SUCCESS);
        REQUIRE_THAT(someOfPoints.name,
                     Equals("Some of points"));
        REQUIRE(someOfPoints.points.size() == 3);
    }

}