//
// Created by netcan on 2021/08/10.
//

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>
#include <config-loader/utils/ConstexprStringUtils.h>
using namespace Catch;
using namespace Catch::Matchers;
using namespace CONFIG_LOADER_NS;

SCENARIO("test concat") {
    GIVEN("concat empty string") {
        constexpr auto res = concat();
        static_assert(res.size() == 1);
    }

    GIVEN("concat a string") {
        constexpr auto res = concat("hello");
        static_assert(res.size() == 6);
        REQUIRE_THAT(res.data(), Equals("hello"));
    }

    GIVEN("concat two string") {
        constexpr auto res = concat("hello", " world");
        static_assert(res.size() == 12);
        REQUIRE_THAT(res.data(), Equals("hello world"));
    }

    GIVEN("concat three string") {
        constexpr auto res = concat("one", "two", "three");
        static_assert(res.size() == 12);
        REQUIRE_THAT(res.data(), Equals("onetwothree"));
    }

    GIVEN("mixin concat char[N]/array<char, N>") {
        constexpr auto res = concat("one", concat("two"), "three");
        static_assert(res.size() == 12);
        REQUIRE_THAT(res.data(), Equals("onetwothree"));
    }
}

SCENARIO("test join") {
    GIVEN("empty join") {
        constexpr auto res = join()(", ");
        static_assert(res.size() == 1);
    }

    GIVEN("join a string") {
        constexpr auto res = join("one")(", ");
        static_assert(res.size() == 4);
        REQUIRE_THAT(res.data(), Equals("one"));
    }
    GIVEN("join two string") {
        constexpr auto res = join("one", "two")(", ");
        static_assert(res.size() == 9);
        REQUIRE_THAT(res.data(), Equals("one, two"));
    }
    GIVEN("join three string") {
        constexpr auto res = join("one", "two", "three")(", ");
        static_assert(res.size() == 16);
        REQUIRE_THAT(res.data(), Equals("one, two, three"));
    }

    GIVEN("mixin join char[N]/array<char, N>") {
        constexpr auto res = join("one", join("two", "three")(","))(", ");
        static_assert(res.size() == 15);
        REQUIRE_THAT(res.data(), Equals("one, two,three"));
    }
}
