//
// Created by netcan on 2021/07/04.
//
#include <catch2/catch.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <config-loader/ConfigLoader.h>
#include "ReflectedStruct.h"

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