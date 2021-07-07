//
// Created by netcan on 2021/07/07.
//

#include <catch2/catch.hpp>
#include <config-loader/ConfigLoader.h>
#include "ReflectedStruct.h"

using namespace Catch;
using namespace CONFIG_LOADER_NS;

SCENARIO("test Deserializable") {
    WHEN("deserializable a complex data from xml file") {
        SomeOfPoints someOfPoints;
        Deserializable<SomeOfPoints
                , TinyXML2Tag
                , decltype("configs/SomeOfPoints.xml"_path)> deserializer;
        REQUIRE(deserializer.load(someOfPoints) == Result::SUCCESS);
        REQUIRE_THAT(someOfPoints.name,
                     Equals("Some of points"));
        REQUIRE(someOfPoints.points.size() == 3);
    }

}