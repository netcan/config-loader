//
// Created by netcan on 2021/07/09.
//

#ifndef CONFIG_LOADER_DESERIALIZEJSONCPPCONFIG_H
#define CONFIG_LOADER_DESERIALIZEJSONCPPCONFIG_H

constexpr std::string_view POINT_CONFIG = R"(
{
  "x": 1.2,
  "y": 3.4
}
)";

constexpr std::string_view RECT_CONFIG = R"(
{
  "p1": {
    "x": 1.2,
    "y": 3.4
  },
  "p2": {
    "x": 5.6,
    "y": 7.8
  },
  "color": 12345678
}
)";

constexpr std::string_view SOME_OF_POINTS_CONFIG = R"(
{
  "name": "Some of points",
  "points":[
    {
      "x": 1.2,
      "y": 3.4
    },
    {
      "x": 5.6,
      "y": 7.8
    },
    {
      "x": 2.2,
      "y": 3.3
    }
  ]
}
)";

#endif //CONFIG_LOADER_DESERIALIZEJSONCPPCONFIG_H
