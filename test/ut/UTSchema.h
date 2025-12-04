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

#ifndef CONFIG_LOADER_UTSCHEMA_H
#define CONFIG_LOADER_UTSCHEMA_H
#include <config-loader/ConfigLoader.h>

// define and reflect a struct

DEFINE_SCHEMA(Point,
              (double) x,
              (double) y);

// nested
DEFINE_SCHEMA(Rect,
              (Point) p1,
              (Point) p2,
              (uint32_t) color);

// vector and string
DEFINE_SCHEMA(SomeOfPoints,
              (std::string) name,
              (std::vector<Point>) points);

DEFINE_SCHEMA(STLObj,
              (std::map<int, int>) m1,
              (std::unordered_map<std::string, Point>) m2,
              (std::optional<std::map<int, int>>) m3,
              (std::optional<Point>) m4,
              (std::optional<int>) m5,
              (std::optional<std::vector<int>>) m6);

DEFINE_SCHEMA(TestVariant,
              (std::variant<Point, int, std::string>) sumType);

DEFINE_SCHEMA(TestTree,
              (std::string) name,
              (std::vector<std::shared_ptr<TestTree>>) children);

#endif //CONFIG_LOADER_UTSCHEMA_H
