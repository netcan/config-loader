//
// This project is a personal hobby work. The author hereby assigns all
// intellectual property rights in this project to Huawei Technologies Co., Ltd.,
// and imposes no obligations or liabilities on Huawei.
//
// 本项目为作者个人业余创作，作者在此声明将本项目及其衍生作品相关的全部知识产权无偿
// 转让给华为技术有限公司，且不对华为提出任何义务或责任要求。
//
// Created by netcan on 2021/08/09.
//

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>
#include <config-loader/serialize/TypeSerializer.h>
#include "UTSchema.h"
using namespace Catch;
using namespace Catch::Matchers;
using namespace CONFIG_LOADER_NS;

SCENARIO("test builtin TypeDeserializer") {
    GIVEN("vector") {
        REQUIRE_THAT(TypeSerializer_v<std::vector<int>>,
                     Equals("vector<int32_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::vector<uint32_t>>,
                     Equals("vector<uint32_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::vector<int8_t>>,
                     Equals("vector<int8_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::vector<uint8_t>>,
                     Equals("vector<uint8_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::vector<short>>,
                     Equals("vector<int16_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::vector<unsigned short>>,
                     Equals("vector<uint16_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::vector<double>>,
                     Equals("vector<double>"));
        REQUIRE_THAT(TypeSerializer_v<std::vector<float>>,
                     Equals("vector<float>"));

        REQUIRE_THAT(TypeSerializer_v<std::vector<std::vector<int>>>,
                     Equals("vector<vector<int32_t>>"));
    }

    GIVEN("list") {
        REQUIRE_THAT(TypeSerializer_v<std::list<int>>,
                     Equals("list<int32_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::list<uint32_t>>,
                     Equals("list<uint32_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::list<int8_t>>,
                     Equals("list<int8_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::list<uint8_t>>,
                     Equals("list<uint8_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::list<short>>,
                     Equals("list<int16_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::list<unsigned short>>,
                     Equals("list<uint16_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::list<double>>,
                     Equals("list<double>"));
        REQUIRE_THAT(TypeSerializer_v<std::list<float>>,
                     Equals("list<float>"));

        REQUIRE_THAT(TypeSerializer_v<std::list<std::list<int>>>,
                     Equals("list<list<int32_t>>"));
    }

    GIVEN("optional") {
        REQUIRE_THAT(TypeSerializer_v<std::optional<int>>,
                     Equals("optional<int32_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::optional<uint32_t>>,
                     Equals("optional<uint32_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::optional<int8_t>>,
                     Equals("optional<int8_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::optional<uint8_t>>,
                     Equals("optional<uint8_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::optional<short>>,
                     Equals("optional<int16_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::optional<unsigned short>>,
                     Equals("optional<uint16_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::optional<double>>,
                     Equals("optional<double>"));
        REQUIRE_THAT(TypeSerializer_v<std::optional<float>>,
                     Equals("optional<float>"));

        REQUIRE_THAT(TypeSerializer_v<std::optional<std::optional<int>>>,
                     Equals("optional<optional<int32_t>>"));
    }

    GIVEN("shared_ptr") {
        REQUIRE_THAT(TypeSerializer_v<std::shared_ptr<int>>,
                     Equals("shared_ptr<int32_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::shared_ptr<uint32_t>>,
                     Equals("shared_ptr<uint32_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::shared_ptr<int8_t>>,
                     Equals("shared_ptr<int8_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::shared_ptr<uint8_t>>,
                     Equals("shared_ptr<uint8_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::shared_ptr<short>>,
                     Equals("shared_ptr<int16_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::shared_ptr<unsigned short>>,
                     Equals("shared_ptr<uint16_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::shared_ptr<double>>,
                     Equals("shared_ptr<double>"));
        REQUIRE_THAT(TypeSerializer_v<std::shared_ptr<float>>,
                     Equals("shared_ptr<float>"));

        REQUIRE_THAT(TypeSerializer_v<std::shared_ptr<std::shared_ptr<int>>>,
                     Equals("shared_ptr<shared_ptr<int32_t>>"));
    }

    GIVEN("unique_ptr") {
        REQUIRE_THAT(TypeSerializer_v<std::unique_ptr<int>>,
                     Equals("unique_ptr<int32_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::unique_ptr<uint32_t>>,
                     Equals("unique_ptr<uint32_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::unique_ptr<int8_t>>,
                     Equals("unique_ptr<int8_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::unique_ptr<uint8_t>>,
                     Equals("unique_ptr<uint8_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::unique_ptr<short>>,
                     Equals("unique_ptr<int16_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::unique_ptr<unsigned short>>,
                     Equals("unique_ptr<uint16_t>"));
        REQUIRE_THAT(TypeSerializer_v<std::unique_ptr<double>>,
                     Equals("unique_ptr<double>"));
        REQUIRE_THAT(TypeSerializer_v<std::unique_ptr<float>>,
                     Equals("unique_ptr<float>"));

        REQUIRE_THAT(TypeSerializer_v<std::unique_ptr<std::unique_ptr<int>>>,
                     Equals("unique_ptr<unique_ptr<int32_t>>"));
    }

    GIVEN("map/unordered_map") {
        REQUIRE_THAT((TypeSerializer_v<std::map<std::string, int>>),
                     Equals("map<string, int32_t>"));
        REQUIRE_THAT((TypeSerializer_v<std::unordered_map<std::string, int>>),
                     Equals("unordered_map<string, int32_t>"));
    }

    GIVEN("variant") {
        REQUIRE_THAT((TypeSerializer_v<std::variant<int8_t, uint8_t, int16_t, uint16_t,
                    int32_t, uint32_t, int64_t, uint64_t, float, double, std::string>>),
                     Equals("variant<int8_t, uint8_t, int16_t, uint16_t,"
                            " int32_t, uint32_t, int64_t, uint64_t, float, double, string>"));
    }
}

SCENARIO("test UTSchema TypeDeserializer") {
    REQUIRE_THAT((TypeSerializer_v<Point>),
                 Equals("Point"));
    REQUIRE_THAT((TypeSerializer_v<std::vector<Point>>),
                 Equals("vector<Point>"));
}
