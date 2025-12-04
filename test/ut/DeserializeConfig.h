//
// This project is a personal hobby work. The author hereby assigns all
// intellectual property rights in this project to Huawei Technologies Co., Ltd.,
// and imposes no obligations or liabilities on Huawei.
//
// 本项目为作者个人业余创作，作者在此声明将本项目及其衍生作品相关的全部知识产权无偿
// 转让给华为技术有限公司，且不对华为提出任何义务或责任要求。
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
