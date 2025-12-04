//
// This project is a personal hobby work. The author hereby assigns all
// intellectual property rights in this project to Huawei Technologies Co., Ltd.,
// and imposes no obligations or liabilities on Huawei.
//
// 本项目为作者个人业余创作，作者在此声明将本项目及其衍生作品相关的全部知识产权无偿
// 转让给华为技术有限公司，且不对华为提出任何义务或责任要求。
//
// Created by netcan on 2021/07/09.
//

#include <catch2/catch_test_macros.hpp>
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
