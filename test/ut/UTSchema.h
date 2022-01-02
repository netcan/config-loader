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
              (std::map<int, int>) m3,
              (std::optional<Point>) m4,
              (std::optional<int>) m5,
              (std::vector<int>) m6);

DEFINE_SCHEMA(TestVariant,
              (std::variant<Point, int, std::string>) sumType);

DEFINE_SCHEMA(TestTree,
              (std::string) name,
              (std::vector<std::shared_ptr<TestTree>>) children);

#endif //CONFIG_LOADER_UTSCHEMA_H
