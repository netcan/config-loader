//
// Created by netcan on 2021/08/09.
//

#include <catch2/catch.hpp>
#include <config-loader/serialize/TypeSerializer.h>
using namespace Catch;
using namespace CONFIG_LOADER_NS;

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

        REQUIRE_THAT(TypeSerializer_v<std::vector<std::vector<int>>>,
                     Equals("std::vector<std::vector<int32_t>>"));
    }

    GIVEN("list") {
        REQUIRE_THAT(TypeSerializer_v<std::list<int>>,
                     Equals("std::list<int32_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::list<uint32_t>>,
                     Equals("std::list<uint32_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::list<int8_t>>,
                     Equals("std::list<int8_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::list<uint8_t>>,
                     Equals("std::list<uint8_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::list<short>>,
                     Equals("std::list<int16_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::list<unsigned short>>,
                     Equals("std::list<uint16_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::list<double>>,
                     Equals("std::list<double>"));
        REQUIRE_THAT(TypeSerializer_v<std::list<float>>,
                     Equals("std::list<float>"));

        REQUIRE_THAT(TypeSerializer_v<std::list<std::list<int>>>,
                     Equals("std::list<std::list<int32_t>>"));
    }

    GIVEN("optional") {
        REQUIRE_THAT(TypeSerializer_v<std::optional<int>>,
                     Equals("std::optional<int32_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::optional<uint32_t>>,
                     Equals("std::optional<uint32_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::optional<int8_t>>,
                     Equals("std::optional<int8_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::optional<uint8_t>>,
                     Equals("std::optional<uint8_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::optional<short>>,
                     Equals("std::optional<int16_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::optional<unsigned short>>,
                     Equals("std::optional<uint16_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::optional<double>>,
                     Equals("std::optional<double>"));
        REQUIRE_THAT(TypeSerializer_v<std::optional<float>>,
                     Equals("std::optional<float>"));

        REQUIRE_THAT(TypeSerializer_v<std::optional<std::optional<int>>>,
                     Equals("std::optional<std::optional<int32_t>>"));
    }

    GIVEN("shared_ptr") {
        REQUIRE_THAT(TypeSerializer_v<std::shared_ptr<int>>,
                     Equals("std::shared_ptr<int32_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::shared_ptr<uint32_t>>,
                     Equals("std::shared_ptr<uint32_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::shared_ptr<int8_t>>,
                     Equals("std::shared_ptr<int8_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::shared_ptr<uint8_t>>,
                     Equals("std::shared_ptr<uint8_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::shared_ptr<short>>,
                     Equals("std::shared_ptr<int16_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::shared_ptr<unsigned short>>,
                     Equals("std::shared_ptr<uint16_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::shared_ptr<double>>,
                     Equals("std::shared_ptr<double>"));
        REQUIRE_THAT(TypeSerializer_v<std::shared_ptr<float>>,
                     Equals("std::shared_ptr<float>"));

        REQUIRE_THAT(TypeSerializer_v<std::shared_ptr<std::shared_ptr<int>>>,
                     Equals("std::shared_ptr<std::shared_ptr<int32_t>>"));
    }

    GIVEN("unique_ptr") {
        REQUIRE_THAT(TypeSerializer_v<std::unique_ptr<int>>,
                     Equals("std::unique_ptr<int32_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::unique_ptr<uint32_t>>,
                     Equals("std::unique_ptr<uint32_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::unique_ptr<int8_t>>,
                     Equals("std::unique_ptr<int8_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::unique_ptr<uint8_t>>,
                     Equals("std::unique_ptr<uint8_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::unique_ptr<short>>,
                     Equals("std::unique_ptr<int16_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::unique_ptr<unsigned short>>,
                     Equals("std::unique_ptr<uint16_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::unique_ptr<double>>,
                     Equals("std::unique_ptr<double>"));
        REQUIRE_THAT(TypeSerializer_v<std::unique_ptr<float>>,
                     Equals("std::unique_ptr<float>"));

        REQUIRE_THAT(TypeSerializer_v<std::unique_ptr<std::unique_ptr<int>>>,
                     Equals("std::unique_ptr<std::unique_ptr<int32_t>>"));
    }

    GIVEN("map/unordered_map") {
        REQUIRE_THAT((TypeSerializer_v<std::map<std::string, int>>),
                     Equals("std::map<std::string, int32_t>"));
        REQUIRE_THAT((TypeSerializer_v<std::unordered_map<std::string, int>>),
                     Equals("std::unordered_map<std::string, int32_t>"));
    }

    GIVEN("variant") {
//        REQUIRE_THAT((TypeSerializer_v<std::variant<int8_t, uint8_t, int16_t, uint16_t,
//                    int32_t, uint32_t, int64_t, uint64_t, float, double, std::string>>),
//                     Equals("std::variant<int8_t, uint8_t, int16_t, uint16_t,"
//                            " int32_t, uint32_t, int64_t, uint64_t, float, double, std::string>"));
    }

}
