//
// This project is a personal hobby work. The author hereby assigns all
// intellectual property rights in this project to Huawei Technologies Co., Ltd.,
// and imposes no obligations or liabilities on Huawei.
//
// 本项目为作者个人业余创作，作者在此声明将本项目及其衍生作品相关的全部知识产权无偿
// 转让给华为技术有限公司，且不对华为提出任何义务或责任要求。
//
// Created by netcan on 2021/07/07.
//

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>
#include <config-loader/ConfigLoader.h>
#include "UTSchema.h"
#include "DeserializeConfig.h"

using namespace Catch;
using namespace Catch::Matchers;
using namespace CONFIG_LOADER_NS;
using namespace xml_config;

SCENARIO("loadXML2Obj test") {
    GIVEN("load by path") {
        THEN("load both by default config") {
            {
                Point point;
                REQUIRE(loadXML2Obj(point, POINT_CONFIG_PATH) == Result::SUCCESS);
                REQUIRE(point.x == 1.2);
                REQUIRE(point.y == 3.4);
            }
            {
                Rect rect;
                REQUIRE(loadXML2Obj(rect, RECT_CONFIG_PATH) == Result::SUCCESS);
                REQUIRE(rect.p1.x == 1.2);
                REQUIRE(rect.p1.y == 3.4);
                REQUIRE(rect.p2.x == 5.6);
                REQUIRE(rect.p2.y == 7.8);
                REQUIRE(rect.color == 0x12345678);
            }

            {
                SomeOfPoints someOfPoints;
                REQUIRE(loadXML2Obj(someOfPoints, SOME_OF_POINTS_CONFIG_PATH) == Result::SUCCESS);

                REQUIRE_THAT(someOfPoints.name,
                             Equals("Some of points"));
                REQUIRE(someOfPoints.points.size() == 3);
            }
        }

        THEN("load by lambda") {
            Rect rect;
            auto res = loadXML2Obj(rect, [] {
                return R"(
                    <?xml version="1.0" encoding="UTF-8"?>
                    <rect>
                        <p1>
                            <x>5.6</x>
                            <y>7.8</y>
                        </p1>
                        <p2>
                            <x>1.2</x>
                            <y>3.4</y>
                        </p2>
                        <color>0x12345678</color>
                    </rect>
                )";
            });
            REQUIRE(res == Result::SUCCESS);
            REQUIRE(rect.p2.x == 1.2);
            REQUIRE(rect.p2.y == 3.4);
            REQUIRE(rect.p1.x == 5.6);
            REQUIRE(rect.p1.y == 7.8);
            REQUIRE(rect.color == 0x12345678);
        }
    }
}
