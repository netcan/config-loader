//
// Created by netcan on 2021/07/06.
//

#include <catch2/catch.hpp>
#include <tinyxml2.h>
#include "ReflectedStruct.h"
#include "DeserializeXMLConfig.h"
#include <config-loader/ConfigLoader.h>

using namespace Catch;
using namespace tinyxml2;
using namespace CONFIG_LOADER_NS;

SCENARIO("deserialize xml to struct") {
    using namespace xml_config;
    GIVEN("a flatten point config") {
        Point point;
        auto deserializer = XMLLoader<Point>();
        auto res = deserializer.load(point, [] {
            return POINT_CONFIG;
        });
        REQUIRE(res == Result::SUCCESS);
        REQUIRE(point.x == 1.2);
        REQUIRE(point.y == 3.4);
    }

    GIVEN("a nest rect config") {
        Rect rect;
        auto deserializer = XMLLoader<Rect>();
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

    GIVEN("a nest rect config that missing p1/p2") {
        Rect rect;
        auto deserializer = XMLLoader<Rect>();
        auto res = deserializer.load(rect, [] {
            return R"(
                <?xml version="1.0" encoding="UTF-8"?>
                <rect>
                    <color>0x12345678</color>
                </rect>
            )";
        });
        REQUIRE(res == Result::ERR_MISSING_FIELD);
    }

    GIVEN("a complex rect config") {
        SomeOfPoints someOfPoints;
        auto deserializer = XMLLoader<SomeOfPoints>();
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
SCENARIO("deserialize xml to extra STL container") {
    GIVEN("a valid STL obj") {
        auto deserializer = XMLLoader<STLObj>();
        STLObj data;
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
        REQUIRE(data.m6.empty());

    }

}

DEFINE_STRUCT(TestObj,
              (bool) m1);

SCENARIO("deserialize primitive type") {
    auto deserializer = XMLLoader<TestObj>();
    TestObj obj;
    GIVEN("a valid bool") {
        auto res = deserializer.load(obj, [] {
            return "<TestObj><m1>true</m1></TestObj>";
        });
        REQUIRE(res == Result::SUCCESS);
        REQUIRE(obj.m1);
    }
    GIVEN("a valid bool") {
        auto res = deserializer.load(obj, [] {
            return "<TestObj><m1>True</m1></TestObj>";
        });
        REQUIRE(res == Result::SUCCESS);
        REQUIRE(obj.m1);
    }
    GIVEN("a valid bool") {
        auto res = deserializer.load(obj, [] {
            return "<TestObj><m1>1</m1></TestObj>";
        });
        REQUIRE(res == Result::SUCCESS);
        REQUIRE(obj.m1);
    }
    GIVEN("a valid bool") {
        auto res = deserializer.load(obj, [] {
            return "<TestObj><m1>false</m1></TestObj>";
        });
        REQUIRE(res == Result::SUCCESS);
        REQUIRE(! obj.m1);
    }
    GIVEN("a invalid bool") {
        auto res = deserializer.load(obj, [] {
            return "<TestObj><m1>unknown</m1></TestObj>";
        });
        REQUIRE(res == Result::ERR_EXTRACTING_FIELD);
    }
}
