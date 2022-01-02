//
// Created by netcan on 2021/07/16.
//

#ifndef CONFIG_LOADER_DESERIALIZECONFIG_H
#define CONFIG_LOADER_DESERIALIZECONFIG_H

namespace xml_config {
constexpr auto POINT_CONFIG_PATH = "configs/xml/Point.xml";
constexpr auto RECT_CONFIG_PATH = "configs/xml/Rect.xml";
constexpr auto SOME_OF_POINTS_CONFIG_PATH = "configs/xml/SomeOfPoints.xml";
constexpr auto STLOBJ_CONFIG_PATH = "configs/xml/STLObj.xml";
constexpr auto TREE_CONFIG_PATH = "configs/xml/Tree.xml";
}

namespace json_config {
constexpr auto POINT_CONFIG_PATH = "configs/json/Point.json";
constexpr auto RECT_CONFIG_PATH = "configs/json/Rect.json";
constexpr auto SOME_OF_POINTS_CONFIG_PATH = "configs/json/SomeOfPoints.json";
constexpr auto STLOBJ_CONFIG_PATH = "configs/json/STLObj.json";
constexpr auto TREE_CONFIG_PATH = "configs/json/Tree.json";
}

namespace yaml_config {
constexpr auto POINT_CONFIG_PATH = "configs/yml/Point.yml";
constexpr auto RECT_CONFIG_PATH = "configs/yml/Rect.yml";
constexpr auto SOME_OF_POINTS_CONFIG_PATH = "configs/yml/SomeOfPoints.yml";
constexpr auto STLOBJ_CONFIG_PATH = "configs/yml/STLObj.yml";
constexpr auto TREE_CONFIG_PATH = "configs/yml/Tree.yml";
}

#endif //CONFIG_LOADER_DESERIALIZECONFIG_H
