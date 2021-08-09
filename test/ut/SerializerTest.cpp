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

    GIVEN("test variant") {
        {
            TestVariant obj{ Point { 1, 2 } };
            dumpObj2OStream(std::cout, obj);
        }

    }

    GIVEN("tree obj") {
        TestTree tree;
        REQUIRE(loadXML2Obj(tree, TREE_CONFIG_PATH) == Result::SUCCESS);
        dumpObj2OStream(std::cout, tree);
    }
}

ALIAS_COMPOUND_TYPE(Tree, (std::map<int, std::shared_ptr<Tree>>));

SCENARIO("dumping alias structure") {
    std::cout << std::endl
              << "////////////////////////////////////////////////////////////////////////////////////////"
              << std::endl;

    Tree tree {
            { {0}, std::make_shared<Tree>() },
            { {1}, std::make_shared<Tree>(
                    Tree {{ {2}, std::make_shared<Tree>() }})
            },
            { {3}, std::make_shared<Tree>() },
    };
    dumpObj2OStream(std::cout, tree);

}
