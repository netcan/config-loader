//
// Created by netcan on 2021/07/04.
//

#ifdef HAS_TINYXML2
#include <catch2/catch.hpp>
#include <tinyxml2.h>
#include <iostream>
#include "DeserializeConfig.h"
using namespace Catch;
using namespace tinyxml2;

static void checkPoint(XMLElement* point, double x, double y) {
    double value;
    REQUIRE(point != nullptr);
    REQUIRE(point->FirstChildElement("x")->QueryDoubleText(&value) == XML_SUCCESS);
    REQUIRE(value == x);
    REQUIRE(point->FirstChildElement("y")->QueryDoubleText(&value) == XML_SUCCESS);
    REQUIRE(value == y);
};

SCENARIO("Load a xml config") {
    using namespace xml_config;
    WHEN("load point config") {
        XMLDocument doc;
        REQUIRE(doc.LoadFile(POINT_CONFIG_PATH) == XML_SUCCESS);
        auto root = doc.FirstChildElement();
        REQUIRE_THAT(root->Name(), Equals("point"));

        checkPoint(root, 1.2, 3.4);
    }

    WHEN("load rect config") {
        XMLDocument doc;
        REQUIRE(doc.LoadFile(RECT_CONFIG_PATH) == XML_SUCCESS);
        auto root = doc.FirstChildElement();
        REQUIRE_THAT(root->Name(), Equals("rect"));

        checkPoint(root->FirstChildElement("p1"), 1.2, 3.4);
        checkPoint(root->FirstChildElement("p2"), 5.6, 7.8);
    }

    WHEN("load some of points") {
        XMLDocument doc;
        REQUIRE(doc.LoadFile(SOME_OF_POINTS_CONFIG_PATH) == XML_SUCCESS);
        auto root = doc.FirstChildElement();
        REQUIRE_THAT(root->Name(), Equals("some_of_points"));
        REQUIRE_THAT(root->FirstChildElement()->GetText(), Equals("Some of points"));

        auto points = root->FirstChildElement("points");
        REQUIRE(points != nullptr);

        double pointsV[] = {
                1.2, 3.4,
                5.6, 7.8,
                2.2, 3.3
        };
        size_t pointIdx = 0;

        for (auto point = points->FirstChildElement()
                ; point
                ; point = point->NextSiblingElement()) {
            REQUIRE_THAT(point->Name(), Equals("value"));
            checkPoint(point, pointsV[pointIdx], pointsV[pointIdx + 1]);
            pointIdx += 2;
        }

    }
}
#endif
