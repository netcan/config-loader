//
// This project is a personal hobby work. The author hereby assigns all
// intellectual property rights in this project to Huawei Technologies Co., Ltd.,
// and imposes no obligations or liabilities on Huawei.
//
// 本项目为作者个人业余创作，作者在此声明将本项目及其衍生作品相关的全部知识产权无偿
// 转让给华为技术有限公司，且不对华为提出任何义务或责任要求。
//
// Created by netcan on 2021/07/08.
//

#include <catch2/catch_test_macros.hpp>
#include <config-loader/ConfigLoader.h>
#include "UTSchema.h"

using namespace CONFIG_LOADER_NS;

SCENARIO("Error checking") {
    WHEN("a empty config") {
        Point point;
        auto res = loadXML2Obj(point, [] {
            return "";
        });
        REQUIRE(res == Result::ERR_EMPTY_CONTENT);
    }

    WHEN("a ill-format config") {
        Point point;
        auto res = loadXML2Obj(point, [] {
            return "<eeeeeeeeeeeeee";
        });
        REQUIRE(res == Result::ERR_ILL_FORMED);
    }

    WHEN("a lacking field config") {
        {
            Point point;
            auto res = loadXML2Obj(point, [] {
                return R"(
                    <?xml version="1.0" encoding="UTF-8"?>
                    <point>
                        <x>1.2</x>
                    </point>
                )";
            });
            REQUIRE(res == Result::ERR_MISSING_FIELD);
        }

        {
            SomeOfPoints someOfPoints;
            auto res = loadXML2Obj(someOfPoints, [] {
                return R"(
                    <?xml version="1.0" encoding="UTF-8"?>
                    <some_of_points>
                        <name>Some of points</name>
                        <points>
                            <value>
                                <y>3.3</y>
                            </value>
                        </points>
                    </some_of_points>
                )";
            });
            REQUIRE(res == Result::ERR_MISSING_FIELD);
        }
    }

    WHEN("a err extracting field config") {
        Point point;
        auto res = loadXML2Obj(point, [] {
            return R"(
                    <?xml version="1.0" encoding="UTF-8"?>
                    <point>
                        <x>abc</x>
                    </point>
                )";
        });
        REQUIRE(res == Result::ERR_EXTRACTING_FIELD);
    }
}
