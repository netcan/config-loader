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
    std::cout << std::endl
              << "////////////////////////////////////////////////////////////////////////////////////////"
              << std::endl;

    GIVEN("a point") {
        Point point;
        REQUIRE(loadXML2Obj(point, POINT_CONFIG_PATH) == Result::SUCCESS);
        dumpObj2OStream(std::cout, point);
    }
    GIVEN("a Rect") {
        Rect rect;
        REQUIRE(loadXML2Obj(rect, RECT_CONFIG_PATH) == Result::SUCCESS);
        dumpObj2OStream(std::cout, rect);
    }

    GIVEN("some of points") {
        SomeOfPoints someOfPoints;
        REQUIRE(loadXML2Obj(someOfPoints, SOME_OF_POINTS_CONFIG_PATH) == Result::SUCCESS);
        dumpObj2OStream(std::cout, someOfPoints);
    }

    GIVEN("stl obj") {
        STLObj stlObj;
        REQUIRE(loadXML2Obj(stlObj, STLOBJ_CONFIG_PATH) == Result::SUCCESS);
        dumpObj2OStream(std::cout, stlObj);
    }

    GIVEN("tree obj") {
        TestTree tree;
        REQUIRE(loadXML2Obj(tree, TREE_CONFIG_PATH) == Result::SUCCESS);
        dumpObj2OStream(std::cout, tree);

    }

}
