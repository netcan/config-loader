//
// Created by netcan on 2021/07/04.
//

#ifndef CONFIG_LOADER_REFLECTEDSTRUCT_H
#define CONFIG_LOADER_REFLECTEDSTRUCT_H
#include <config-loader/DefineStruct.h>

// define and reflect a struct
DEFINE_STRUCT(Point,
              (double) x,
              (double) y);

// nested
DEFINE_STRUCT(Rect,
              (Point) p1,
              (Point) p2,
              (uint32_t) color);

// vector and string
DEFINE_STRUCT(SomeOfPoints,
              (std::string) name,
              (std::vector<Point>) points);

#endif //CONFIG_LOADER_REFLECTEDSTRUCT_H
