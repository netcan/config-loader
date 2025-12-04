//
// This project is a personal hobby work. The author hereby assigns all
// intellectual property rights in this project to Huawei Technologies Co., Ltd.,
// and imposes no obligations or liabilities on Huawei.
//
// 本项目为作者个人业余创作，作者在此声明将本项目及其衍生作品相关的全部知识产权无偿
// 转让给华为技术有限公司，且不对华为提出任何义务或责任要求。
//
// Created by netcan on 2021/07/04.
//
#include <catch2/catch_test_macros.hpp>
#include <string>
#include <config-loader/ConfigLoader.h>
#include "UTSchema.h"

using namespace CONFIG_LOADER_NS;

SCENARIO("reflect a struct") {
    WHEN("retrieve field count") {
        static_assert(Point::_field_count_ == 2);
        static_assert(Rect::_field_count_ == 3);
    }
    WHEN("no extract space overhead") {
        static_assert(sizeof(Point) == 2 * 8);
        static_assert(alignof(Point) == 8);
        static_assert(sizeof(Rect) == 2 * 8 * 2 + 4 /* spacing */ + 4);
        static_assert(alignof(Rect) == 8);
    }

}
