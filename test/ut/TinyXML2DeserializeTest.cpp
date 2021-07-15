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
SCENARIO("deserialize xml to compound STL container") {
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

DEFINE_STRUCT(TestBool,
              (bool) m1);

SCENARIO("deserialize xml to bool type") {
    auto deserializer = XMLLoader<TestBool>();
    TestBool obj;
    GIVEN("a valid bool") {
        auto res = deserializer.load(obj, [] {
            return "<TestBool><m1>true</m1></TestBool>";
        });
        REQUIRE(res == Result::SUCCESS);
        REQUIRE(obj.m1);
    }
    GIVEN("a valid bool") {
        auto res = deserializer.load(obj, [] {
            return "<TestBool><m1>True</m1></TestBool>";
        });
        REQUIRE(res == Result::SUCCESS);
        REQUIRE(obj.m1);
    }
    GIVEN("a valid bool") {
        auto res = deserializer.load(obj, [] {
            return "<TestBool><m1>1</m1></TestBool>";
        });
        REQUIRE(res == Result::SUCCESS);
        REQUIRE(obj.m1);
    }
    GIVEN("a valid bool") {
        auto res = deserializer.load(obj, [] {
            return "<TestBool><m1>false</m1></TestBool>";
        });
        REQUIRE(res == Result::SUCCESS);
        REQUIRE(! obj.m1);
    }
    GIVEN("a invalid bool") {
        auto res = deserializer.load(obj, [] {
            return "<TestBool><m1>unknown</m1></TestBool>";
        });
        REQUIRE(res == Result::ERR_EXTRACTING_FIELD);
    }
}

DEFINE_STRUCT(TestInt,
              (int) number);

SCENARIO("deserialize xml to a number") {
    auto deserializer = XMLLoader<TestInt>();
    TestInt obj;
    GIVEN("a HEX number") {
        auto res = deserializer.load(obj, [] {
            return "<TestInt><number>0X12</number></TestInt>";
        });
        REQUIRE(res == Result::SUCCESS);
        REQUIRE(obj.number == 0x12);
    }
    GIVEN("a hex number") {
        auto res = deserializer.load(obj, [] {
            return "<TestInt><number>0x12</number></TestInt>";
        });
        REQUIRE(res == Result::SUCCESS);
        REQUIRE(obj.number == 0x12);
    }

    GIVEN("a hex number") {
        auto res = deserializer.load(obj, [] {
            return "<TestInt><number>0x</number></TestInt>";
        });
        REQUIRE(res == Result::ERR_EXTRACTING_FIELD);
    }

}

DEFINE_STRUCT(TestVariant,
              (std::variant<Point, int, std::string>) sumType);

SCENARIO("deserialize xml to sum type(std::variant)") {
    auto deserializer = XMLLoader<TestVariant>();
    TestVariant obj;
    GIVEN("a string") {
        auto res = deserializer.load(obj, [] {
            return R"(
                <TestVariant>
                    <sumType>hello world!</sumType>
                </TestVariant>
            )";
        });
        REQUIRE(res == Result::SUCCESS);
        REQUIRE(obj.sumType.index() == 2);
        REQUIRE(! obj.sumType.valueless_by_exception());
        REQUIRE_THAT(std::get<2>(obj.sumType),
                     Equals("hello world!"));
    }

    GIVEN("a int") {
        auto res = deserializer.load(obj, [] {
            return R"(
                 <TestVariant>
                     <sumType>987654</sumType>
                 </TestVariant>
                )";
        });
        REQUIRE(res == Result::SUCCESS);
        REQUIRE(obj.sumType.index() == 1);
        REQUIRE(! obj.sumType.valueless_by_exception());
        REQUIRE(std::get<1>(obj.sumType) == 987654);
    }

    GIVEN("a point") {
        auto res = deserializer.load(obj, [] {
            return R"(
                 <TestVariant>
                     <sumType>
                        <x>1.2</x><y>3.4</y>
                    </sumType>
                 </TestVariant>
            )";
        });
        REQUIRE(res == Result::SUCCESS);
        REQUIRE(obj.sumType.index() == 0);
        REQUIRE(! obj.sumType.valueless_by_exception());
        auto&& [x, y] = std::get<0>(obj.sumType);
        REQUIRE(x == 1.2);
        REQUIRE(y == 3.4);
    }

    GIVEN("a missing field") {
        auto res = deserializer.load(obj, [] {
            return R"(
                 <TestVariant>
                 </TestVariant>
            )";
        });
        REQUIRE(res == Result::ERR_MISSING_FIELD);
    }

    GIVEN("a invalid object") {
        auto res = deserializer.load(obj, [] {
            return R"(
                 <TestVariant>
                     <sumType>
                        <x>1.2</x>
                    </sumType>
                 </TestVariant>
            )";
        });
        REQUIRE(res == Result::ERR_TYPE);
    }

    GIVEN("a empty object") {
        auto res = deserializer.load(obj, [] {
            return R"(
                 <TestVariant>
                     <sumType>
                    </sumType>
                 </TestVariant>
            )";
        });
        REQUIRE(res == Result::ERR_TYPE);
    }
}

DEFINE_STRUCT(TestTree,
              (std::string) name,
              (std::vector<std::unique_ptr<TestTree>>) children);

SCENARIO("deserialize xml to tree type") {
    auto deserializer = XMLLoader<TestTree>();
    TestTree obj;
    GIVEN("a tree") {
        auto res = deserializer.load(obj, [] {
            return R"(
                <TestTree>
                    <name>hello</name>
                    <children>
                        <Node> <name>world</name> </Node>
                        <Node> <name>first</name> </Node>
                        <Node>
                            <name>second</name>
                            <children>
                                <Node> <name>leaf</name> </Node>
                            </children>
                        </Node>
                    </children>
                </TestTree>
            )";
        });
        REQUIRE(res == Result::SUCCESS);
        REQUIRE_THAT(obj.name, Equals("hello"));
        REQUIRE(obj.children.size() == 3);
        REQUIRE_THAT(obj.children[0]->name, Equals("world"));
        REQUIRE_THAT(obj.children[1]->name, Equals("first"));
        REQUIRE_THAT(obj.children[2]->name, Equals("second"));
        REQUIRE(obj.children[2]->children.size() == 1);
        REQUIRE_THAT(obj.children[2]->children[0]->name, Equals("leaf"));

    }

}
