//
// Created by netcan on 2021/07/16.
//

#ifndef CONFIG_LOADER_DESERIALIZECONFIG_H
#define CONFIG_LOADER_DESERIALIZECONFIG_H

namespace xml_config {
constexpr auto POINT_CONFIG = R"(
<?xml version="1.0" encoding="UTF-8"?>
<point>
    <x>1.2</x>
    <y>3.4</y>
</point>
)";

constexpr auto RECT_CONFIG = R"(
<?xml version="1.0" encoding="UTF-8"?>
<rect>
    <p1> <x>1.2</x> <y>3.4</y> </p1>
    <p2> <x>5.6</x> <y>7.8</y> </p2>
    <color>0x12345678</color>
</rect>
)";

constexpr auto SOME_OF_POINTS_CONFIG = R"(
<?xml version="1.0" encoding="UTF-8"?>
<some_of_points>
    <name>Some of points</name>
    <points>
        <value> <x>1.2</x> <y>3.4</y> </value>
        <value> <x>5.6</x> <y>7.8</y> </value>
        <value> <x>2.2</x> <y>3.3</y> </value>
    </points>
</some_of_points>
)";
}

namespace json_config {
constexpr std::string_view POINT_CONFIG = R"( { "x": 1.2, "y": 3.4 } )";

constexpr std::string_view RECT_CONFIG = R"(
{
  "p1": { "x": 1.2, "y": 3.4 },
  "p2": { "x": 5.6, "y": 7.8 },
  "color": 12345678
}
)";

constexpr std::string_view SOME_OF_POINTS_CONFIG = R"(
{
  "name": "Some of points",
  "points":[
    { "x": 1.2, "y": 3.4 },
    { "x": 5.6, "y": 7.8 },
    { "x": 2.2, "y": 3.3 }
  ]
}
)";
}

namespace yaml_config {
constexpr std::string_view POINT_CONFIG = R"(
x: 1.2
y: 3.4
)";

constexpr std::string_view RECT_CONFIG = R"(
p1:
  x: 1.2
  y: 3.4
p2:
  x: 5.6
  y: 7.8
color: 0x12345678
)";

constexpr std::string_view SOME_OF_POINTS_CONFIG = R"(
name: Some of points
points:
  - x: 1.2
    y: 3.4
  - x: 5.6
    y: 7.8
  - x: 2.2
    y: 3.3
)";
}

#endif //CONFIG_LOADER_DESERIALIZECONFIG_H
