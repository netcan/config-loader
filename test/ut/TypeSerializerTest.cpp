//
// Created by netcan on 2021/08/09.
//

#include <catch2/catch.hpp>
#include <config-loader/serialize/TypeSerializer.h>
using namespace Catch;
using namespace CONFIG_LOADER_NS;

SCENARIO("test concat") {
    using config_loader::detail::concat;
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

SCENARIO("test TypeDeserializer") {
    GIVEN("vector") {
        REQUIRE_THAT(TypeSerializer_v<std::vector<int>>,
                     Equals("std::vector<int32_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::vector<uint32_t>>,
                     Equals("std::vector<uint32_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::vector<int8_t>>,
                     Equals("std::vector<int8_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::vector<uint8_t>>,
                     Equals("std::vector<uint8_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::vector<short>>,
                     Equals("std::vector<int16_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::vector<unsigned short>>,
                     Equals("std::vector<uint16_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::vector<double>>,
                     Equals("std::vector<double>"));
        REQUIRE_THAT(TypeSerializer_v<std::vector<float>>,
                     Equals("std::vector<float>"));
    }

}
