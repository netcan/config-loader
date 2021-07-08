//
// Created by netcan on 2021/07/09.
//

#include <catch2/catch.hpp>
#include <sstream>

SCENARIO("test stringstream") {
    std::stringstream ss;
    WHEN("extract error") {
        ss << "asfdasjl";
        int value;
        ss >> value;
        REQUIRE(ss.fail());
    }
    WHEN("extract empty error") {
        ss << "";
        int value;
        ss >> value;
        REQUIRE(ss.fail());
    }
    WHEN("extract int") {
        ss << "123";
        int value;
        ss >> value;
        REQUIRE(! ss.fail());
        REQUIRE(value == 123);
    }
}

