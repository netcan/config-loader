//
// Created by netcan on 2021/08/06.
//
#include <catch2/catch.hpp>
#include <config-loader/ConfigLoader.h>
#include "UTSchema.h"
#include "DeserializeConfig.h"
#include <iostream>

using namespace Catch;
using namespace CONFIG_LOADER_NS;
using namespace xml_config;

SCENARIO("dumping data structure") {
    GIVEN("a point") {
        Point point;
        REQUIRE(loadXML2Obj(point, POINT_CONFIG_PATH) == Result::SUCCESS);
        dumpObj2OStream(std::cout, point);
        std::cout << std::endl;
    }
    GIVEN("a Rect") {
        Rect rect;
        REQUIRE(loadXML2Obj(rect, RECT_CONFIG_PATH) == Result::SUCCESS);
        dumpObj2OStream(std::cout, rect);
        std::cout << std::endl;
    }

}