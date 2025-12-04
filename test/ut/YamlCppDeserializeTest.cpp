//
// This project is a personal hobby work. The author hereby assigns all
// intellectual property rights in this project to Huawei Technologies Co., Ltd.,
// and imposes no obligations or liabilities on Huawei.
//
// 本项目为作者个人业余创作，作者在此声明将本项目及其衍生作品相关的全部知识产权无偿
// 转让给华为技术有限公司，且不对华为提出任何义务或责任要求。
//
// Created by netcan on 2021/07/16.
//

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>
#include "UTSchema.h"
#include "DeserializeConfig.h"
#include <config-loader/ConfigLoader.h>

using namespace Catch;
using namespace Catch::Matchers;
using namespace CONFIG_LOADER_NS;
using namespace yaml_config;

SCENARIO("deserialize yaml to struct") {
    GIVEN("a flatten point config") {
        Point point;
        REQUIRE(loadYAML2Obj(point, POINT_CONFIG_PATH) == Result::SUCCESS);
        REQUIRE(point.x == 1.2);
        REQUIRE(point.y == 3.4);
    }

    GIVEN("a nest rect config") {
        Rect rect;
        REQUIRE(loadYAML2Obj(rect, RECT_CONFIG_PATH) == Result::SUCCESS);
        REQUIRE(rect.p1.x == 1.2);
        REQUIRE(rect.p1.y == 3.4);
        REQUIRE(rect.p2.x == 5.6);
        REQUIRE(rect.p2.y == 7.8);
        REQUIRE(rect.color == 0x12345678);
    }

    GIVEN("a nest rect config that missing p1/p2") {
        Rect rect;
        auto res = loadYAML2Obj(rect, [] {
            return R"("color": 12345678)";
        });
        REQUIRE(res == Result::ERR_MISSING_FIELD);
    }

    GIVEN("a complex rect config") {
        SomeOfPoints someOfPoints;
        REQUIRE(loadYAML2Obj(someOfPoints, SOME_OF_POINTS_CONFIG_PATH) == Result::SUCCESS);
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
SCENARIO("deserialize yaml to compound STL container") {
    GIVEN("a valid STL obj") {
        STLObj data;
        REQUIRE(loadYAML2Obj(data, STLOBJ_CONFIG_PATH) == Result::SUCCESS);
        REQUIRE(data.m1[0] == 2);
        REQUIRE(data.m1[1] == 4);
        REQUIRE(data.m1[2] == 6);
        REQUIRE(data.m1.size() == 3);

        REQUIRE(data.m2["hello world"].x == 1.2);
        REQUIRE(data.m2["hello world"].y == 3.4);
        REQUIRE(data.m2.size() == 1);

        REQUIRE(data.m3.has_value());
        REQUIRE(data.m3->empty());

        REQUIRE(data.m4.has_value());
        REQUIRE(data.m4->x == 5.6);
        REQUIRE(data.m4->y == 7.8);

        REQUIRE(! data.m5.has_value());
        REQUIRE(! data.m6.has_value());
    }
}

SCENARIO("deserialize yaml to sum type(std::variant)") {
    TestVariant obj;

    GIVEN("a string") {
        auto res = loadYAML2Obj(obj, [] {
            return R"( sumType: hello world! )";
        });
        REQUIRE(res == Result::SUCCESS);
        REQUIRE(obj.sumType.index() == 2);
        REQUIRE(! obj.sumType.valueless_by_exception());
        REQUIRE_THAT(std::get<2>(obj.sumType),
                     Equals("hello world!"));
    }

    GIVEN("a int") {
        auto res = loadYAML2Obj(obj, [] {
            return R"( sumType: 987654 )";
        });
        REQUIRE(res == Result::SUCCESS);
        REQUIRE(obj.sumType.index() == 1);
        REQUIRE(! obj.sumType.valueless_by_exception());
        REQUIRE(std::get<1>(obj.sumType) == 987654);
    }

    GIVEN("a point") {
        auto res = loadYAML2Obj(obj, [] {
            return R"(
                sumType:
                  x: 1.2
                  y: 3.4
            )";
        });
        REQUIRE(res == Result::SUCCESS);
        REQUIRE(obj.sumType.index() == 0);
        REQUIRE(! obj.sumType.valueless_by_exception());
        auto&& [x, y] = std::get<0>(obj.sumType);
        REQUIRE(x == 1.2);
        REQUIRE(y == 3.4);
    }

    GIVEN("a invalid object") {
        auto res = loadYAML2Obj(obj, [] {
            return R"(
                sumType:
                  x: 1.2
            )";
        });
        REQUIRE(res == Result::ERR_TYPE);
    }

    GIVEN("a invalid type") {
        auto res = loadYAML2Obj(obj, [] {
            return R"( sumType: [1,2,3] )";
        });
        REQUIRE(res == Result::ERR_TYPE);
    }
    GIVEN("a null type type") {
        auto res = loadYAML2Obj(obj, [] {
            return R"( dummy: true )";
        });
        REQUIRE(res == Result::ERR_MISSING_FIELD);
    }

    GIVEN("a empty object") {
        auto res = loadYAML2Obj(obj, [] {
            return R"( sumType: [] )";
        });
        REQUIRE(res == Result::ERR_TYPE);
    }
}

SCENARIO("deserialize yaml to tree type") {
    TestTree obj;
    GIVEN("a tree") {
        REQUIRE(loadYAML2Obj(obj, TREE_CONFIG_PATH) == Result::SUCCESS);
        REQUIRE_THAT(obj.name, Equals("hello"));
        REQUIRE(obj.children.size() == 3);
        REQUIRE_THAT(obj.children[0]->name, Equals("world"));
        REQUIRE_THAT(obj.children[1]->name, Equals("first"));
        REQUIRE_THAT(obj.children[2]->name, Equals("second"));
        REQUIRE(obj.children[2]->children.size() == 1);
        REQUIRE_THAT(obj.children[2]->children[0]->name, Equals("leaf"));
    }
}
