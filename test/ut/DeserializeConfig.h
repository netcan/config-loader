//
// Created by netcan on 2021/07/16.
//

#ifndef CONFIG_LOADER_DESERIALIZECONFIG_H
#define CONFIG_LOADER_DESERIALIZECONFIG_H
#include <config-loader/utils/ConfigPath.h>

using CONFIG_LOADER_NS::operator""_path;

namespace xml_config {
constexpr auto POINT_CONFIG_PATH = "configs/xml/Point.xml"_path;
constexpr auto RECT_CONFIG_PATH = "configs/xml/Rect.xml"_path;
constexpr auto SOME_OF_POINTS_CONFIG_PATH = "configs/xml/SomeOfPoints.xml"_path;
constexpr auto STLOBJ_CONFIG_PATH = "configs/xml/STLObj.xml"_path;
constexpr auto TREE_CONFIG_PATH = "configs/xml/Tree.xml"_path;
}

namespace json_config {
constexpr auto POINT_CONFIG_PATH = "configs/json/Point.json"_path;
constexpr auto RECT_CONFIG_PATH = "configs/json/Rect.json"_path;
constexpr auto SOME_OF_POINTS_CONFIG_PATH = "configs/json/SomeOfPoints.json"_path;
constexpr auto STLOBJ_CONFIG_PATH = "configs/json/STLObj.json"_path;
constexpr auto TREE_CONFIG_PATH = "configs/json/Tree.json"_path;
}

namespace yaml_config {
constexpr auto POINT_CONFIG_PATH = "configs/yml/Point.yml"_path;
constexpr auto RECT_CONFIG_PATH = "configs/yml/Rect.yml"_path;
constexpr auto SOME_OF_POINTS_CONFIG_PATH = "configs/yml/SomeOfPoints.yml"_path;
constexpr auto STLOBJ_CONFIG_PATH = "configs/yml/STLObj.yml"_path;
constexpr auto TREE_CONFIG_PATH = "configs/yml/Tree.yml"_path;
}

#endif //CONFIG_LOADER_DESERIALIZECONFIG_H
