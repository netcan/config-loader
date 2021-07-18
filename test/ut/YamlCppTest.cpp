//
// Created by netcan on 2021/07/16.
//

#ifdef HAS_YAMLCPP
#include <catch2/catch.hpp>
#include <yaml-cpp/yaml.h>
#include <iostream>
#include "DeserializeConfig.h"
using namespace Catch;

static void checkPoint(const YAML::Node& node, double x, double y) {
    REQUIRE(node["x"].as<double>() == x);
    REQUIRE(node["y"].as<double>() == y);
};

SCENARIO("Load a yaml config") {
    using namespace yaml_config;
    GIVEN("a point config") {
        YAML::Node root = YAML::LoadFile(POINT_CONFIG_PATH.value);
        REQUIRE(! root.IsNull());
        checkPoint(root, 1.2, 3.4);
    }

    GIVEN("a rect config") {
        YAML::Node root = YAML::LoadFile(RECT_CONFIG_PATH.value);
        REQUIRE(! root.IsNull());
        checkPoint(root["p1"], 1.2, 3.4);
        checkPoint(root["p2"], 5.6, 7.8);
        REQUIRE(root["color"].as<int>() == 0x12345678);
    }

    GIVEN("some of points") {
        YAML::Node root = YAML::LoadFile(SOME_OF_POINTS_CONFIG_PATH.value);
        REQUIRE(! root.IsNull());
        REQUIRE_THAT(root["name"].as<std::string>(), Equals("Some of points"));
        double pointsV[] = {
                1.2, 3.4,
                5.6, 7.8,
                2.2, 3.3
        };
        size_t pointIdx = 0;
        for (auto&& point = root["point"].begin()
                ; point != root["point"].end()
                ; ++point) {
            checkPoint(*point, pointsV[pointIdx], pointsV[pointIdx + 1]);
            pointIdx += 2;
        }
    }
}
#endif